/******************************************************************************
*
* Copyright (C) 2016 Xilinx, Inc. All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/
/*****************************************************************************/
/**
*
* @file xcsi2txss_intr_example.c
* @addtogroup csi2txss_v1_0
* @{
*
* This file contains a design example using XCsi2TxSs driver with interrupts.
* It notify which of the following interrupt is generated by a print message
* 	- Incorrect Lane Configuration
* 	- GSP FIFO Full
*	- Ulps State
*	- Line Buffer Full
*	- Unsupported/Reserved Data type
*	- Pixel Data underrun
*
* @note		This example requires an interrupt controller connected to the
*		processor and the MIPI CSI2Tx Subsystem in the system.
*
*		For this example to display output, the user need to implement
*		initialization of the system (Csi2TxSs_PlatformInit) and after
*		MIPI CSI2Tx subsystem start (XCsi2TxSs_Start) is complete,
*		implement configuration of the video stream source in order to
*		provide the MIPI CSI2Tx Subsystem HIP input.
*		The functions Csi2TxSs_PlatformInit and Csi2TxSs_StreamSrc are
*		declared and are left up to the user implement.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver Who Date     Changes
* --- --- -------- ------------------------------------------------------------
* 1.0 sss 08/02/16 Initial release
*     ms  01/23/17 Modified xil_printf statement in main function to
*                  ensure that "Successfully ran" and "Failed" strings are
*                  available in all examples. This is a fix for CR-965028.
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xcsi2txss.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xstatus.h"
#include "xintc.h"

/************************** Constant Definitions *****************************/

/*
* The following constants map to the names of the hardware instances.
* They are only defined here such that a user can easily change all the
* needed device IDs in one place.
*/
#ifdef XPAR_INTC_0_DEVICE_ID
#define XINTC_DEVICE_ID			XPAR_INTC_0_DEVICE_ID
#define XINTC					XIntc
#define XINTC_CSI2TXSS_CSI_INTERRUPT_ID	\
								XPAR_INTC_0_CSI2TXSS_0_VEC_ID
#define XINTC_HANDLER			XIntc_InterruptHandler
#else
#define XINTC_DEVICE_ID			XPAR_SCUGIC_SINGLE_DEVICE_ID
#define XINTC_CSI2TXSS_CSI_INTERRUPT_ID	\
		XPAR_FABRIC_AXI_CSI2TXSS_0_INTERRUPT_INTR
#define XINTC					XScuGic
#define XINTC_HANDLER			XScuGic_InterruptHandler
#endif


/* The unique device ID of the MIPI CSI2Tx Subsystem instance to be used
 */
#define XCSI2TXSS_DEVICE_ID		XPAR_CSI2TXSS_0_DEVICE_ID
#define MAX_INTERRUPT_COUNT		1

/***************** Macros (Inline Functions) Definitions *********************/


/**************************** Type Definitions *******************************/


/************************** Function Prototypes ******************************/

u32 Csi2TxSs_IntrExample(u32 DeviceId);
u32 Csi2TxSs_PlatformInit(void);

/* Interrupt helper functions */
u32 Csi2TxSs_SetupIntrSystem(XINTC *IntcInstPtr);
void Csi2TxSs_WrgLaneEventHandler(void *InstancePtr, u32 Mask);
void Csi2TxSs_GSPFullEventHandler(void *InstancePtr, u32 Mask);
void Csi2TxSs_UlpsEventHandler(void *InstancePtr, u32 Mask);
void Csi2TxSs_LinebufEventHandler(void *InstancePtr, u32 Mask);
void Csi2TxSs_WrgDTypeEventHandler(void *InstancePtr, u32 Mask);
void Csi2TxSs_UrunPixelEventHandler(void *InstancePtr, u32 Mask);

/************************** Variable Definitions *****************************/

XCsi2TxSs Csi2TxSsInst;	/* The MIPI CSI2Tx Subsystem instance.*/

volatile u32 interrupt_counts;

/************************** Function Definitions *****************************/

/******************************************************************************/
/**
*
* For Microblaze we use an assembly loop that is roughly the same regardless of
* optimization level, although caches and memory access time can make the delay
* vary.  Just keep in mind that after resetting or updating the PHY modes,
* the PHY typically needs time to recover.
*
* @param	Number of seconds to sleep
*
* @return	None
*
* @note		None
*
******************************************************************************/
static void Delay(u32 Seconds)
{
#if defined (__MICROBLAZE__) || defined(__PPC__)
	static s32 WarningFlag = 0;

	/* If MB caches are disabled or do not exist, this delay loop could
	 * take minutes instead of seconds (e.g., 30x longer).  Print a warning
	 * message for the user (once).  If only MB had a built-in timer!
	 */
	if (((mfmsr() & 0x20) == 0) && (!WarningFlag)) {
		WarningFlag = 1;
	}

#define ITERS_PER_SEC   (XPAR_CPU_CORE_CLOCK_FREQ_HZ / 6)
    asm volatile ("\n"
			"1:               \n\t"
			"addik r7, r0, %0 \n\t"
			"2:               \n\t"
			"addik r7, r7, -1 \n\t"
			"bneid  r7, 2b    \n\t"
			"or  r0, r0, r0   \n\t"
			"bneid %1, 1b     \n\t"
			"addik %1, %1, -1 \n\t"
			:: "i"(ITERS_PER_SEC), "d" (Seconds));
#else
    sleep(Seconds);
#endif
}

#ifndef TESTAPP_GEN
/*****************************************************************************/
/**
*
* This is the main function for XCsi2TxSs interrupt example. If the
* Csi2TxSs_IntrExample function which sets up the system succeeds, this function
* will wait for the interrupts. Once a connection event or pulse is detected,
* Csi2TxSs will TX device capabilities and re-start the subsystem.
*
* @param	None.
*
* @return
*		- XST_FAILURE if the interrupt example was unsuccessful.
*		- XST_SUCCESS if the interrupt example was successful.
*
******************************************************************************/
int main()
{
	int Status;

	xil_printf("-------------------------------------------\n\r");
	xil_printf("  MIPI CSI2Tx Subsystem interrupt example\n\r");
	xil_printf("-------------------------------------------\n\r");

	Status = Csi2TxSs_IntrExample(XCSI2TXSS_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		xil_printf("MIPI CSI2Tx Subsystem interrupt example "
				"failed.");
		return XST_FAILURE;
	}

	xil_printf("Successfully ran MIPI CSI2Tx Subsystem interrupt example\n\r");

	return XST_SUCCESS;
}
#endif

/*****************************************************************************/
/**
*
* This function is the main entry point for the interrupt example using the
* XCsi2TxSs driver. This function will set up the system with interrupts
* handlers.
*
* @param	DeviceId is the unique device ID of the MIPI CSI2Tx
*		Subsystem core.
*
* @return
*		- XST_FAILURE if the system setup failed.
*		- XST_SUCCESS should never return since this function, if setup
*		  was successful, is blocking.
*
* @note		If system setup was successful, this function is blocking in
*		order to illustrate interrupt handling.
*
******************************************************************************/
u32 Csi2TxSs_IntrExample(u32 DeviceId)
{
	u32 Status;
	static XINTC IntcInst;
	XCsi2TxSs_Config *ConfigPtr;
	u8 ActiveLanes;
	u32 IntrRequest = XCSI2TXSS_ISR_ALLINTR_MASK;
	u8 Exit_Count = 0;

	/* Do platform initialization in this function. This is hardware
	 * system specific. It is up to the user to implement this function.
	 */
	xil_printf("PlatformInit\n\r");
	Status = Csi2TxSs_PlatformInit();
	if (Status != XST_SUCCESS) {
		xil_printf("Platform init failed!\n\r");
	}
	xil_printf("Platform initialization done.\n\r");

	/* Obtain the device configuration for the MIPI CSI2Tx Subsystem */
	ConfigPtr = XCsi2TxSs_LookupConfig(DeviceId);
	if (!ConfigPtr) {
		return XST_FAILURE;
	}
	/* Copy the device configuration into the Csi2TxSsInst's Config
	 * structure. */
	Status = XCsi2TxSs_CfgInitialize(&Csi2TxSsInst, ConfigPtr,
					ConfigPtr->BaseAddr);
	if (Status != XST_SUCCESS) {
		xil_printf("CSI2TXSS config initialization "
		"failed.\n\r");
		return XST_FAILURE;
	}
	/* Dump the configuration */
	XCsi2TxSs_ReportCoreInfo(&Csi2TxSsInst);

	/* Reset the subsystem */
	XCsi2TxSs_Reset(&Csi2TxSsInst);

	/* Disable the subsystem till the camera
	 * and interrupts are configured
	 */
	XCsi2TxSs_Activate(&Csi2TxSsInst, XCSI2TX_DISABLE);

	/* Configure the subsystem for ActiveLanes and Interrupts
	 * The minimum value of ActiveLanes is 0 and max value is
	 * maximum lanes set in the design (max 3).
	 * The interrupt mask can be selected from the bitmasks in
	 * xcsi2txss_hw.h
	 */
	ActiveLanes = 1;
	IntrRequest = XCSI2TXSS_ISR_ALLINTR_MASK;

	Status = XCsi2TxSs_Configure(&Csi2TxSsInst, ActiveLanes, IntrRequest);
	if (Status == XST_FAILURE) {
		xil_printf("CSI2TXSS Configure failed. \n\r");
		return XST_FAILURE;
	}

	/* Setup the interrupts and call back handlers */
	Status = Csi2TxSs_SetupIntrSystem(&IntcInst);
	if (Status != XST_SUCCESS) {
		xil_printf("ERR: Interrupt system "
		"setup failed.\n\r");
		return XST_FAILURE;
	}

	/* Enable the cores */
	XCsi2TxSs_Activate(&Csi2TxSsInst, XCSI2TX_ENABLE);

	/* Wait up to MAX_INTERRUPT_COUNT */
	do {
		Delay(1);
		Exit_Count++;
		if(Exit_Count > 3) {
			xil_printf("CSI2TXSS Interrupt "
			" test failed, Please check design\n\r");
			return XST_FAILURE;
		}

	}
	while (interrupt_counts < MAX_INTERRUPT_COUNT);

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function initialize required platform-specifc peripherals.
*
* @param	None.
*
* @return
*		- XST_SUCCESS if required peripherals are initialized and
*		configured successfully.
*		- XST_FAILURE, otherwise.
*
* @note		None.
*
******************************************************************************/
u32 Csi2TxSs_PlatformInit(void)
{
	/* User is responsible to setup platform specific initialization */

	return XST_SUCCESS;
}

/*****************************************************************************/

/*****************************************************************************/
/**
*
* This function sets up the interrupt system so interrupts can occur for the
* MIPI CSI2Tx Subsystem core. The function is application-specific since
* the actual system may or may not have an interrupt controller. The MIPI CSI
* Subsystem core could be directly connected to a processor without an
* interrupt controller. The user should modify this function to fit the
* application.
*
* @param	IntcInstPtr is a pointer to interrupt controller
*
* @return
*		- XST_SUCCESS if interrupt setup was successful.
*		- A specific error code defined in "xstatus.h" if an error
*		occurs.
*
* @note		None.
*
******************************************************************************/
u32 Csi2TxSs_SetupIntrSystem(XINTC *IntcInstPtr)
{
	u32 Status;

	/* Set the interrupt handlers. */
	XCsi2TxSs_SetCallBack(&Csi2TxSsInst, XCSI2TXSS_HANDLER_WRG_LANE,
				Csi2TxSs_WrgLaneEventHandler, &Csi2TxSsInst);
	XCsi2TxSs_SetCallBack(&Csi2TxSsInst, XCSI2TXSS_HANDLER_GSPFIFO_FULL,
				Csi2TxSs_GSPFullEventHandler, &Csi2TxSsInst);
	XCsi2TxSs_SetCallBack(&Csi2TxSsInst, XCSI2TXSS_HANDLER_ULPS,
				Csi2TxSs_UlpsEventHandler, &Csi2TxSsInst);
	XCsi2TxSs_SetCallBack(&Csi2TxSsInst, XCSI2TXSS_HANDLER_LINEBUF_FULL,
				Csi2TxSs_LinebufEventHandler, &Csi2TxSsInst);
	XCsi2TxSs_SetCallBack(&Csi2TxSsInst, XCSI2TXSS_HANDLER_WRG_DATATYPE,
				Csi2TxSs_WrgDTypeEventHandler, &Csi2TxSsInst);
	XCsi2TxSs_SetCallBack(&Csi2TxSsInst, XCSI2TXSS_HANDLER_UNDERRUN_PIXEL,
				Csi2TxSs_UrunPixelEventHandler, &Csi2TxSsInst);

#ifdef XPAR_INTC_0_DEVICE_ID
	/* Initialize the interrupt controller driver so that it's ready to
	 * use, specify the device ID that was generated in xparameters.h
	 */
	Status = XIntc_Initialize(IntcInstPtr, XINTC_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		xil_printf("Intc initialization failed\n\r");
		return XST_FAILURE;
	}

	/* Hook up interrupt service routine */
	Status = XIntc_Connect(IntcInstPtr, XINTC_CSI2TXSS_CSI_INTERRUPT_ID,
			(XInterruptHandler)XCsi2TxSs_IntrHandler,
				&Csi2TxSsInst);
	if (Status != XST_SUCCESS) {
		xil_printf("ERR: MIPI CSI2TX SS"
		"interrupt connect  failed!\n\r");
		return XST_FAILURE;
	}

	/* Enable the interrupt vector at the interrupt controller */
	XIntc_Enable(IntcInstPtr, XINTC_CSI2TXSS_CSI_INTERRUPT_ID);

	/* Start the interrupt controller such that interrupts are recognized
	 * and handled by the processor
	 */
	Status = XIntc_Start(IntcInstPtr, XIN_REAL_MODE);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/* Initialize the exception table. */
	Xil_ExceptionInit();

	/* Register the interrupt controller handler with the exception
	 * table.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			(Xil_ExceptionHandler)XINTC_HANDLER, IntcInstPtr);

	/* Enable exceptions. */
	Xil_ExceptionEnable();
#else
	XScuGic_Config *IntcConfig;

	/*
	 * Initialize the interrupt controller driver so that it is ready to
	 * use.
	 */
	IntcConfig = XScuGic_LookupConfig(XINTC_DEVICE_ID);
	if (NULL == IntcConfig) {
		return XST_FAILURE;
	}

	Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig,
					IntcConfig->CpuBaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XScuGic_SetPriorityTriggerType(IntcInstancePtr,
			XINTC_CSI2TXSS_CSI_INTERRUPT_ID, 0xA0, 0x3);
	/*
	 * Connect the device driver handler that will be called when an
	 * interrupt for the device occurs, the handler defined above performs
	 * the specific interrupt processing for the device.
	 */
	Status = XScuGic_Connect(IntcInstancePtr,
				XINTC_CSI2TXSS_CSI_INTERRUPT_ID,
				(Xil_InterruptHandler)XCsi2TxSs_IntrHandler,
				Csi2TxSsInst);
	if (Status != XST_SUCCESS) {
		xil_printf("ERR: MIPI CSI2TX SS interrupt connect failed!\n\r");
		return XST_FAILURE;
	}

	/*
	 * Enable the interrupt for the DMA device.
	 */
	XScuGic_Enable(IntcInstancePtr, XINTC_CSI2TXSS_CSI_INTERRUPT_ID);

	Xil_ExceptionInit();

	/*
	 * Connect the interrupt controller interrupt handler to the hardware
	 * interrupt handling logic in the processor.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
				(Xil_ExceptionHandler)XINTC_HANDLER,
				IntcInstPtr);
	/*
	 * Enable interrupts in the Processor.
	 */
	Xil_ExceptionEnable();
#endif
	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function is called when Wrong number of lanes are configured
* by the MIPI CSI2Tx Subsystem core.
*
* @param	InstancePtr is a pointer to the XCsi2TxSs instance.
* @param	Mask of interrupt which caused this event
*
* @return	None.
*
* @note		Use the XCsi2TxSs_SetCallback driver function to set this
*		function as the handler for wrong lane configuration event.
*
******************************************************************************/
void Csi2TxSs_WrgLaneEventHandler(void *InstancePtr, u32 Mask)
{
	xil_printf("Incorrect lane configuration detected\n\r");
	interrupt_counts++;

}

/*****************************************************************************/
/**
*
* This function is called when Genric Short Packet FIFO is found full by
* the MIPI CSI2Tx Subsystem core.
*
* @param	InstancePtr is a pointer to the XCsi2TxSs instance.
* @param	Mask of interrupt which caused this event
*
* @return	None.
*
* @note		Use the XCsi2TxSs_SetCallback driver function to set this
*		function as the handler for Packet level error event.
*
******************************************************************************/
void Csi2TxSs_GSPFullEventHandler(void *InstancePtr, u32 Mask)
{
	xil_printf("+===> Generic Short Packet FIFO Full detected\n\r");
	interrupt_counts++;
}

/*****************************************************************************/
/**
*
* This function is called when  there is a change in ULPS state of D-PHY Lanes.
*
* @param	InstancePtr is a pointer to the XCsi2TxSs instance.
* @param	Mask of interrupt which caused this event
*
* @return	None.
*
* @note		Use the XCsi2TxSs_SetCallback driver function to set this
*		function as the handler for ULPS mode detection event.
*
******************************************************************************/
void Csi2TxSs_UlpsEventHandler(void *InstancePtr, u32 Mask)
{
	xil_printf("+===> ULPS state change detected.\n\r");
	interrupt_counts++;

	if (Mask) {
		xil_printf("DPHY Lanes are in ULPS Mode\n\r");
	} else {
		xil_printf("DPHY lanes exited from ULPS Mode\n\r");
	}

}

/*****************************************************************************/
/**
*
* This function is called when a Line buffer is full event recieved by
* MIPI CSI2Tx Subsystem core.
*
* @param	InstancePtr is a pointer to the XCsi2TxSs instance.
* @param	Mask of interrupt which caused this event
*
* @return	None.
*
* @note		Use the XCsi2TxSs_SetCallback driver function to set this
*		function as the handler for Line buffer full event.
*
******************************************************************************/
void Csi2TxSs_LinebufEventHandler(void *InstancePtr, u32 Mask)
{
	xil_printf("+===> Line buffer full detected.\n\r");
	interrupt_counts++;

}

/*****************************************************************************/
/**
*
* This function is called when a event generated by unspported data type in
* GSP request to the MIPI CSI2Tx Subsystem core.
*
* @param	InstancePtr is a pointer to the XCsi2TxSs instance.
*
* @param	Mask of interrupt which caused this event
*
* @return	None.
*
* @note		Use the XCsi2TxSs_SetCallback driver function to set this
*		function as the handler for Short Packet FIFO error event.
*
******************************************************************************/
void Csi2TxSs_WrgDTypeEventHandler(void *InstancePtr, u32 Mask)
{
	xil_printf("+===> Wrong data type in GSP request detected.\n\r");
	interrupt_counts++;

}

/*****************************************************************************/
/**
*
* This function is called when during packet transmission, byte stream FIFO is
* found to be starves for pixel by the MIPI CSI2Tx Subsystem core.
*
* @param	InstancePtr is a pointer to the XCsi2TxSs instance.
*
* @param	Mask of interrupt which caused this event
*
* @return	None.
*
* @note		Use the XCsi2TxSs_SetCallback driver function to set this
*		function as the handler for Byte stream FIFO starve event.
*
******************************************************************************/
void Csi2TxSs_UrunPixelEventHandler(void *InstancePtr, u32 Mask)
{
	xil_printf("+=> Byte stream FIFO starves for Pixel"
				"during packet transmission.\n\r");
	interrupt_counts++;
}
/** @} */