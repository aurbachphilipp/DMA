/******************************************************************************
*
* Copyright (C) 2014-2019 Xilinx, Inc.  All rights reserved.
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
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
* 
*
******************************************************************************/
/*****************************************************************************/
/**
*
* @file xqspipsu_options.c
* @addtogroup qspipsu_v1_10
* @{
*
* This file implements functions to configure the QSPIPSU component,
* specifically some optional settings, clock and flash related information.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who Date     Changes
* ----- --- -------- -----------------------------------------------
* 1.0   hk  08/21/14 First release
*       sk  03/13/15 Added IO mode support.
*       sk  04/24/15 Modified the code according to MISRAC-2012.
* 1.1   sk  04/12/16 Added debug message prints.
* 1.2	nsk 07/01/16 Modified XQspiPsu_SetOptions() to support
*		     LQSPI options and updated OptionsTable
*       rk  07/15/16 Added support for TapDelays at different frequencies.
* 1.7	tjs 01/17/18 Added support to toggle the WP pin of flash. (PR#2448)
* 1.7	tjs	03/14/18 Added support in EL1 NS mode. (CR#974882)
* 1.8  tjs 05/02/18 Added support for IS25LP064 and IS25WP064.
* 1.8  tjs 07/26/18 Resolved cppcheck errors. (CR#1006336)
* 1.9	tjs	04/17/18 Updated register addresses as per the latest revision
* 					 of versal (CR#999610)
* 1.9  aru 01/17/19 Fixes violations according to MISRAC-2012
*                  in safety mode and modified the code such as
*                  Added Xil_MemCpy inplace of memcpy,Declared the pointer param
*                  as Pointer to const, declared XQspi_Set_TapDelay() as static.
* 1.9 akm 03/08/19 Set recommended clock and data tap delay values for 40MHZ,
*		   100MHZ and 150MHZ frequencies(CR#1023187)
* 1.10 akm 08/22/19 Set recommended tap delay values for 37.5MHZ, 100MHZ and
*		    150MHZ frequencies in Versal.
*
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xqspipsu.h"
#if defined (__aarch64__)
#include "xil_smc.h"
#endif

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

#if defined (ARMR5) || (__aarch64__)
#define TAPDLY_BYPASS_VALVE_40MHZ 0x01U
#define TAPDLY_BYPASS_VALVE_100MHZ 0x01U
#define USE_DLY_LPBK  0x01U
#define USE_DATA_DLY_ADJ 0x01U
#define DATA_DLY_ADJ_DLY 0X02U
#define LPBK_DLY_ADJ_DLY0 0X02U
#define LPBK_DLY_ADJ_DLY1 0X02U
#endif

/************************** Function Prototypes ******************************/

#if defined (ARMR5) || (__aarch64__)
static s32 XQspi_Set_TapDelay(const XQspiPsu * InstancePtr,u32 TapdelayBypass,
						u32 LPBKDelay,u32 Datadelay);
static s32 XQspipsu_Calculate_Tapdelay(const XQspiPsu *InstancePtr, u8 Prescaler);
#endif

/************************** Variable Definitions *****************************/

/*
 * Create the table of options which are processed to get/set the device
 * options. These options are table driven to allow easy maintenance and
 * expansion of the options.
 */
typedef struct {
	u32 Option;
	u32 Mask;
} OptionsMap;

static OptionsMap OptionsTable[] = {
	{XQSPIPSU_CLK_ACTIVE_LOW_OPTION, XQSPIPSU_CFG_CLK_POL_MASK},
	{XQSPIPSU_CLK_PHASE_1_OPTION, XQSPIPSU_CFG_CLK_PHA_MASK},
	{XQSPIPSU_MANUAL_START_OPTION, XQSPIPSU_CFG_GEN_FIFO_START_MODE_MASK},
	{XQSPIPSU_LQSPI_MODE_OPTION, XQSPIPSU_CFG_WP_HOLD_MASK},
};

#define XQSPIPSU_NUM_OPTIONS	(sizeof(OptionsTable) / sizeof(OptionsMap))

/*****************************************************************************/
/**
*
* This function sets the options for the QSPIPSU device driver.The options
* control how the device behaves relative to the QSPIPSU bus. The device must be
* idle rather than busy transferring data before setting these device options.
*
* @param	InstancePtr is a pointer to the XQspiPsu instance.
* @param	Options contains the specified options to be set. This is a bit
*		mask where a 1 indicates the option should be turned ON and
*		a 0 indicates no action. One or more bit values may be
*		contained in the mask. See the bit definitions named
*		XQSPIPSU_*_OPTIONS in the file xqspipsu.h.
*
* @return
*		- XST_SUCCESS if options are successfully set.
*		- XST_DEVICE_BUSY if the device is currently transferring data.
*		The transfer must complete or be aborted before setting options.
*
* @note
* This function is not thread-safe.
*
******************************************************************************/
s32 XQspiPsu_SetOptions(XQspiPsu *InstancePtr, u32 Options)
{
	u32 ConfigReg;
	u32 Index;
	u32 QspiPsuOptions;
	s32 Status;
	u32 OptionsVal;
	OptionsVal = Options;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Do not allow to modify the Control Register while a transfer is in
	 * progress. Not thread-safe.
	 */
	if (InstancePtr->IsBusy == TRUE) {
		Status = (s32)XST_DEVICE_BUSY;
	} else {

		ConfigReg = XQspiPsu_ReadReg(InstancePtr->Config.BaseAddress,
					      XQSPIPSU_CFG_OFFSET);
		QspiPsuOptions = OptionsVal & XQSPIPSU_LQSPI_MODE_OPTION;
		OptionsVal &= (~XQSPIPSU_LQSPI_MODE_OPTION);
		/*
		 * Loop through the options table, turning the option on
		 * depending on whether the bit is set in the incoming options flag.
		 */
		for (Index = 0U; Index < XQSPIPSU_NUM_OPTIONS; Index++) {
			if ((OptionsVal & OptionsTable[Index].Option) == OptionsTable[Index].Option) {
				/* Turn it on */
				ConfigReg |= OptionsTable[Index].Mask;
			} else {
                /* Turn it off */
                ConfigReg &= ~(OptionsTable[Index].Mask);
        }

		}
		/*
		 * Now write the control register. Leave it to the upper layers
		 * to restart the device.
		 */
		XQspiPsu_WriteReg(InstancePtr->Config.BaseAddress, XQSPIPSU_CFG_OFFSET,
				 ConfigReg);

		if ((OptionsVal & XQSPIPSU_MANUAL_START_OPTION) != FALSE) {
			InstancePtr->IsManualstart = TRUE;
		}

		if ((QspiPsuOptions & XQSPIPSU_LQSPI_MODE_OPTION) != FALSE) {
			if ((Options & XQSPIPSU_LQSPI_LESS_THEN_SIXTEENMB) != FALSE) {
				XQspiPsu_WriteReg(XQSPIPS_BASEADDR,XQSPIPSU_LQSPI_CR_OFFSET,XQSPIPS_LQSPI_CR_RST_STATE);
			} else {
				XQspiPsu_WriteReg(XQSPIPS_BASEADDR,XQSPIPSU_LQSPI_CR_OFFSET,XQSPIPS_LQSPI_CR_4_BYTE_STATE);
			}
			XQspiPsu_WriteReg(XQSPIPS_BASEADDR,XQSPIPSU_CFG_OFFSET,XQSPIPS_LQSPI_CFG_RST_STATE);
			/* Enable the QSPI controller */
			XQspiPsu_WriteReg(XQSPIPS_BASEADDR,XQSPIPSU_EN_OFFSET,XQSPIPSU_EN_MASK);
		} else {
			/*
			 * Check for the LQSPI configuration options.
			 */
			ConfigReg = XQspiPsu_ReadReg(XQSPIPS_BASEADDR,XQSPIPSU_LQSPI_CR_OFFSET);
			ConfigReg &= ~(XQSPIPSU_LQSPI_CR_LINEAR_MASK);
			XQspiPsu_WriteReg(XQSPIPS_BASEADDR,XQSPIPSU_LQSPI_CR_OFFSET, ConfigReg);
		}

		Status = XST_SUCCESS;
	}

	return Status;
}

/*****************************************************************************/
/**
*
* This function resets the options for the QSPIPSU device driver.The options
* control how the device behaves relative to the QSPIPSU bus. The device must be
* idle rather than busy transferring data before setting these device options.
*
* @param	InstancePtr is a pointer to the XQspiPsu instance.
* @param	Options contains the specified options to be set. This is a bit
*		mask where a 1 indicates the option should be turned OFF and
*		a 0 indicates no action. One or more bit values may be
*		contained in the mask. See the bit definitions named
*		XQSPIPSU_*_OPTIONS in the file xqspipsu.h.
*
* @return
*		- XST_SUCCESS if options are successfully set.
*		- XST_DEVICE_BUSY if the device is currently transferring data.
*		The transfer must complete or be aborted before setting options.
*
* @note
* This function is not thread-safe.
*
******************************************************************************/
s32 XQspiPsu_ClearOptions(XQspiPsu *InstancePtr, u32 Options)
{
	u32 ConfigReg;
	u32 Index;
	s32 Status;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Do not allow to modify the Control Register while a transfer is in
	 * progress. Not thread-safe.
	 */
	if (InstancePtr->IsBusy == TRUE) {
		Status = (s32)XST_DEVICE_BUSY;
	} else {

		ConfigReg = XQspiPsu_ReadReg(InstancePtr->Config.BaseAddress,
					      XQSPIPSU_CFG_OFFSET);

		/*
		 * Loop through the options table, turning the option on
		 * depending on whether the bit is set in the incoming options flag.
		 */
		for (Index = 0U; Index < XQSPIPSU_NUM_OPTIONS; Index++) {
			if ((Options & OptionsTable[Index].Option) != FALSE) {
				/* Turn it off */
				ConfigReg &= ~OptionsTable[Index].Mask;
			}
		}

		/*
		 * Now write the control register. Leave it to the upper layers
		 * to restart the device.
		 */
		XQspiPsu_WriteReg(InstancePtr->Config.BaseAddress, XQSPIPSU_CFG_OFFSET,
				 ConfigReg);

		if ((Options & XQSPIPSU_MANUAL_START_OPTION) != FALSE) {
			InstancePtr->IsManualstart = FALSE;
		}

		Status = XST_SUCCESS;
	}

	return Status;
}

/*****************************************************************************/
/**
*
* This function gets the options for the QSPIPSU device. The options control how
* the device behaves relative to the QSPIPSU bus.
*
* @param	InstancePtr is a pointer to the XQspiPsu instance.
*
* @return
*
* Options contains the specified options currently set. This is a bit value
* where a 1 means the option is on, and a 0 means the option is off.
* See the bit definitions named XQSPIPSU_*_OPTIONS in file xqspipsu.h.
*
* @note		None.
*
******************************************************************************/
u32 XQspiPsu_GetOptions(const XQspiPsu *InstancePtr)
{
	u32 OptionsFlag = 0;
	u32 ConfigReg;
	u32 Index;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/* Loop through the options table to grab options */
	for (Index = 0U; Index < XQSPIPSU_NUM_OPTIONS; Index++) {
		/*
		 * Get the current options from QSPIPSU configuration register.
		 */
		ConfigReg = XQspiPsu_ReadReg(InstancePtr->Config.BaseAddress,
						      XQSPIPSU_CFG_OFFSET);
		if ((ConfigReg & OptionsTable[Index].Mask) != FALSE) {
			OptionsFlag |= OptionsTable[Index].Option;
		}
	}

	return OptionsFlag;
}

#if defined (ARMR5) || (__aarch64__)
/*****************************************************************************/
/**
*
* This function sets the Tapdelay values for the QSPIPSU device driver.The device
* must be idle rather than busy transferring data before setting Tapdelay.
*
* @param	InstancePtr is a pointer to the XQspiPsu instance.
* @param	TapdelayBypss contains the IOU_TAPDLY_BYPASS register value.
* @param	LPBKDelay contains the GQSPI_LPBK_DLY_ADJ register value.
* @param	Datadelay contains the QSPI_DATA_DLY_ADJ register value.
*
* @return
*		- XST_SUCCESS if options are successfully set.
*		- XST_DEVICE_BUSY if the device is currently transferring data.
*		The transfer must complete or be aborted before setting TapDelay.
*
* @note
* This function is not thread-safe.
*
******************************************************************************/
static s32 XQspi_Set_TapDelay(const XQspiPsu * InstancePtr,u32 TapdelayBypass,
						u32 LPBKDelay,u32 Datadelay)
{
	s32 Status;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Do not allow to modify the Control Register while a transfer is in
	 * progress. Not thread-safe.
	 */
	if (InstancePtr->IsBusy == TRUE) {
		Status = XST_DEVICE_BUSY;
	} else {
#if EL1_NONSECURE && defined (__aarch64__) && !defined (versal)
		Xil_Smc(MMIO_WRITE_SMC_FID, (u64)(XPS_SYS_CTRL_BASEADDR +
				IOU_TAPDLY_BYPASS_OFFSET) |
				((u64)(0x4) << 32),
				(u64)TapdelayBypass, 0, 0, 0, 0, 0);
#elif defined (versal)
		XQspiPsu_WriteReg(XQSPIPS_BASEADDR,IOU_TAPDLY_BYPASS_OFFSET,
				TapdelayBypass);
#else
		XQspiPsu_WriteReg(XPS_SYS_CTRL_BASEADDR,IOU_TAPDLY_BYPASS_OFFSET,
				TapdelayBypass);
#endif
		XQspiPsu_WriteReg(InstancePtr->Config.BaseAddress,
				XQSPIPSU_LPBK_DLY_ADJ_OFFSET,LPBKDelay);
		XQspiPsu_WriteReg(InstancePtr->Config.BaseAddress,
				XQSPIPSU_DATA_DLY_ADJ_OFFSET,Datadelay);
		Status = XST_SUCCESS;
	}
	return Status;
}

/*****************************************************************************/
/**
*
* Configures the clock according to the prescaler passed.
*
*
* @param	InstancePtr is a pointer to the XQspiPsu instance.
* @param	Prescaler - clock prescaler.
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_DEVICE_BUSY if the device is currently transferring data.
*		The transfer must complete or be aborted before setting Tapdelay.
*
* @note		None.
*
******************************************************************************/
static s32 XQspipsu_Calculate_Tapdelay(const XQspiPsu *InstancePtr, u8 Prescaler)
{
	u32 FreqDiv, Divider;
	u32 Tapdelay = 0;
	u32 LBkModeReg = 0;
	u32 delayReg = 0;
	s32 Status;
#if defined (versal)
	u32 IsVersal = 1;
#else
	u32 IsVersal = 0;
#endif

	Divider = (1U << (Prescaler+1U));

	FreqDiv = (InstancePtr->Config.InputClockHz)/Divider;

#if defined (versal)
	if(FreqDiv <= XQSPIPSU_FREQ_37_5MHZ){
#else
	if(FreqDiv <= XQSPIPSU_FREQ_40MHZ){
#endif
		Tapdelay |= (TAPDLY_BYPASS_VALVE_40MHZ <<
			     IOU_TAPDLY_BYPASS_LQSPI_RX_SHIFT);
	} else if (FreqDiv <= XQSPIPSU_FREQ_100MHZ) {
		Tapdelay |= (TAPDLY_BYPASS_VALVE_100MHZ <<
			     IOU_TAPDLY_BYPASS_LQSPI_RX_SHIFT);
		LBkModeReg |= (USE_DLY_LPBK <<
			       XQSPIPSU_LPBK_DLY_ADJ_USE_LPBK_SHIFT);
		delayReg |= (IsVersal != 0) ?
			    (USE_DATA_DLY_ADJ  <<
                             XQSPIPSU_DATA_DLY_ADJ_USE_DATA_DLY_SHIFT) :
			    ((USE_DATA_DLY_ADJ  <<
			      XQSPIPSU_DATA_DLY_ADJ_USE_DATA_DLY_SHIFT) |
			     (DATA_DLY_ADJ_DLY  <<
			      XQSPIPSU_DATA_DLY_ADJ_DLY_SHIFT));
	} else if (FreqDiv <= XQSPIPSU_FREQ_150MHZ) {
		LBkModeReg |= (IsVersal != 0) ?
			      ((USE_DLY_LPBK  <<
			        XQSPIPSU_LPBK_DLY_ADJ_USE_LPBK_SHIFT) |
			       (LPBK_DLY_ADJ_DLY1 <<
			        XQSPIPSU_LPBK_DLY_ADJ_DLY1_SHIFT)) :
			      (USE_DLY_LPBK  <<
			       XQSPIPSU_LPBK_DLY_ADJ_USE_LPBK_SHIFT);
	} else {
		Status = XST_FAILURE;
		goto END;
	}
	Status = XQspi_Set_TapDelay(InstancePtr, Tapdelay, LBkModeReg, delayReg);


	END:
	return Status;
}
#endif

/*****************************************************************************/
/**
*
* Configures the clock according to the prescaler passed.
*
*
* @param	InstancePtr is a pointer to the XQspiPsu instance.
* @param	Prescaler - clock prescaler to be set.
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_DEVICE_IS_STARTED if the device is already started.
*		- XST_DEVICE_BUSY if the device is currently transferring data.
*		It must be stopped to re-initialize.
*
* @note		None.
*
******************************************************************************/
s32 XQspiPsu_SetClkPrescaler(const XQspiPsu *InstancePtr, u8 Prescaler)
{
	u32 ConfigReg;
	s32 Status;

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	Xil_AssertNonvoid(Prescaler <= XQSPIPSU_CR_PRESC_MAXIMUM);

	/*
	 * Do not allow the slave select to change while a transfer is in
	 * progress. Not thread-safe.
	 */
	if (InstancePtr->IsBusy == TRUE) {
		Status = (s32)XST_DEVICE_BUSY;
	} else {

		/*
		 * Read the configuration register, mask out the relevant bits, and set
		 * them with the shifted value passed into the function. Write the
		 * results back to the configuration register.
		 */
		ConfigReg = XQspiPsu_ReadReg(InstancePtr->Config.BaseAddress,
					      XQSPIPSU_CFG_OFFSET);

		ConfigReg &= (u32)(~XQSPIPSU_CFG_BAUD_RATE_DIV_MASK);
		ConfigReg |= (u32) ((u32)Prescaler & (u32)XQSPIPSU_CR_PRESC_MAXIMUM) <<
				    XQSPIPSU_CFG_BAUD_RATE_DIV_SHIFT;

		XQspiPsu_WriteReg(InstancePtr->Config.BaseAddress,
				  XQSPIPSU_CFG_OFFSET, ConfigReg);

#if defined (ARMR5) || (__aarch64__)
		Status = XQspipsu_Calculate_Tapdelay(InstancePtr,Prescaler);
#else
		Status = XST_SUCCESS;
#endif
	}

	return Status;
}

/*****************************************************************************/
/**
*
* This function should be used to tell the QSPIPSU driver the HW flash
* configuration being used. This API should be called at least once in the
* application. If desired, it can be called multiple times when switching
* between communicating to different flahs devices/using different configs.
*
* @param	InstancePtr is a pointer to the XQspiPsu instance.
* @param	FlashCS - Flash Chip Select.
* @param	FlashBus - Flash Bus (Upper, Lower or Both).
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_DEVICE_IS_STARTED if the device is already started.
*		It must be stopped to re-initialize.
*
* @note		If this function is not called at least once in the application,
*		the driver assumes there is a single flash connected to the
*		lower bus and CS line.
*
******************************************************************************/
void XQspiPsu_SelectFlash(XQspiPsu *InstancePtr, u8 FlashCS, u8 FlashBus)
{
	Xil_AssertVoid(InstancePtr != NULL);

#ifdef DEBUG
	xil_printf("\nXQspiPsu_SelectFlash\r\n");
#endif

	/*
	 * Bus and CS lines selected here will be updated in the instance and
	 * used for subsequent GENFIFO entries during transfer.
	 */

	/* Choose slave select line */
	switch (FlashCS) {
		case XQSPIPSU_SELECT_FLASH_CS_BOTH:
			InstancePtr->GenFifoCS = (u32)XQSPIPSU_GENFIFO_CS_LOWER |
						(u32)XQSPIPSU_GENFIFO_CS_UPPER;
			break;
		case XQSPIPSU_SELECT_FLASH_CS_UPPER:
			InstancePtr->GenFifoCS = XQSPIPSU_GENFIFO_CS_UPPER;
			break;
		case XQSPIPSU_SELECT_FLASH_CS_LOWER:
			InstancePtr->GenFifoCS = XQSPIPSU_GENFIFO_CS_LOWER;
			break;
		default:
			InstancePtr->GenFifoCS = XQSPIPSU_GENFIFO_CS_LOWER;
			break;
	}

	/* Choose bus */
	switch (FlashBus) {
		case XQSPIPSU_SELECT_FLASH_BUS_BOTH:
			InstancePtr->GenFifoBus = (u32)XQSPIPSU_GENFIFO_BUS_LOWER |
						(u32)XQSPIPSU_GENFIFO_BUS_UPPER;
			break;
		case XQSPIPSU_SELECT_FLASH_BUS_UPPER:
			InstancePtr->GenFifoBus = XQSPIPSU_GENFIFO_BUS_UPPER;
			break;
		case XQSPIPSU_SELECT_FLASH_BUS_LOWER:
			InstancePtr->GenFifoBus = XQSPIPSU_GENFIFO_BUS_LOWER;
			break;
		default:
			InstancePtr->GenFifoBus = XQSPIPSU_GENFIFO_BUS_LOWER;
			break;
	}
#ifdef DEBUG
	xil_printf("\nGenFifoCS is %08x and GenFifoBus is %08x\r\n",
				InstancePtr->GenFifoCS, InstancePtr->GenFifoBus);
#endif

}

/*****************************************************************************/
/**
*
* This function sets the Read mode for the QSPIPSU device driver.The device
* must be idle rather than busy transferring data before setting Read mode
* options.
*
* @param	InstancePtr is a pointer to the XQspiPsu instance.
* @param	Mode contains the specified Mode to be set. See the
* 		bit definitions named XQSPIPSU_READMODE_* in the file xqspipsu.h.
*
* @return
*		- XST_SUCCESS if options are successfully set.
*		- XST_DEVICE_BUSY if the device is currently transferring data.
*		The transfer must complete or be aborted before setting Mode.
*
* @note
* This function is not thread-safe.
*
******************************************************************************/
s32 XQspiPsu_SetReadMode(XQspiPsu *InstancePtr, u32 Mode)
{
	u32 ConfigReg;
	s32 Status;

#ifdef DEBUG
	xil_printf("\nXQspiPsu_SetReadMode\r\n");
#endif

	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	/*
	 * Do not allow to modify the Control Register while a transfer is in
	 * progress. Not thread-safe.
	 */
	if (InstancePtr->IsBusy == TRUE) {
		Status = (s32)XST_DEVICE_BUSY;
	} else {

		InstancePtr->ReadMode = Mode;

		ConfigReg = XQspiPsu_ReadReg(InstancePtr->Config.BaseAddress,
					      XQSPIPSU_CFG_OFFSET);

		if (Mode == XQSPIPSU_READMODE_DMA) {
			ConfigReg &= ~XQSPIPSU_CFG_MODE_EN_MASK;
			ConfigReg |= XQSPIPSU_CFG_MODE_EN_DMA_MASK;
		} else {
			ConfigReg &= ~XQSPIPSU_CFG_MODE_EN_MASK;
		}

		XQspiPsu_WriteReg(InstancePtr->Config.BaseAddress, XQSPIPSU_CFG_OFFSET,
				 ConfigReg);

		Status = XST_SUCCESS;
	}
#ifdef DEBUG
	xil_printf("\nRead Mode is %08x\r\n", InstancePtr->ReadMode);
#endif
	return Status;
}

/*****************************************************************************/
/**
*
* This function sets the Write Protect and Hold options for the QSPIPSU device
* driver.The device must be idle rather than busy transferring data before
* setting Write Protect and Hold options.
*
* @param	InstancePtr is a pointer to the XQspiPsu instance.
* @param	Value of the WP_HOLD bit in configuration register
*
* @return	None
*
* @note
* This function is not thread-safe. This function can only be used with single
* flash configuration and x1/x2 data mode. This function cannot be used with
* x4 data mode and dual parallel and stacked flash configuration.
*
******************************************************************************/
void XQspiPsu_SetWP(const XQspiPsu *InstancePtr, u8 Value)
{
	u32 ConfigReg;

	ConfigReg = XQspiPsu_ReadReg(InstancePtr->Config.BaseAddress,
			XQSPIPSU_CFG_OFFSET);
	ConfigReg |= (u32)((u32)Value << XQSPIPSU_CFG_WP_HOLD_SHIFT);
	XQspiPsu_WriteReg(InstancePtr->Config.BaseAddress, XQSPIPSU_CFG_OFFSET,
					 ConfigReg);
}
/** @} */
