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
* @file xdsitxss_selftest_example.c
*
* This file contains a design example using the XDsiTxSs driver. It performs a
* self test on the MIPI DSI Tx Subsystem that will test its sub-cores
* self test functions.
*
* @note		None.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver Who Date    Changes
* --- --- ------- -------------------------------------------------------
* 1.0 ram 11/2/16 Initial Release for MIPI DSI TX subsystem
* 1.1 ms  01/23/17 Modified xil_printf statement in main function to
*                  ensure that "Successfully ran" and "Failed" strings
*                  are available in all examples. This is a fix for
*                  CR-965028.
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xdsitxss.h"
#include "xil_printf.h"
#include "xil_types.h"
#include "xstatus.h"

/************************** Constant Definitions *****************************/

/* The unique device ID of the MIPI DSI Rx Subsystem instance
 * to be used
 */
#define XDSITXSS_DEVICE_ID		XPAR_DSITXSS_0_DEVICE_ID

/***************** Macros (Inline Functions) Definitions *********************/


/**************************** Type Definitions *******************************/


/************************** Function Prototypes ******************************/

u32 DsiTxSs_SelfTestExample(u32 DeviceId);

/************************** Variable Definitions *****************************/

XDsiTxSs DsiTxSsInst;	/* The DSI TX Subsystem instance.*/

/************************** Function Definitions *****************************/

/*****************************************************************************/
/**
*
* This is the main function for XDsiTxSs self test example.
*
* @param	None.
*
* @return
*		- XST_SUCCESS if the self test example passed.
*		- XST_FAILURE if the self test example was unsuccessful.
*
* @note		None.
*
******************************************************************************/
#ifndef TESTAPP_GEN
s32 main()
{
	u32 Status;

	xil_printf("---------------------------------------\n\r");
	xil_printf("MIPI DSI TX Subsystem self test example\n\r");
	xil_printf("---------------------------------------\n\r\n\r");

	Status = DsiTxSs_SelfTestExample(XDSITXSS_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		xil_printf("MIPI DSI TX Subsystem self test example failed\n\r");
		return XST_FAILURE;
	}

	xil_printf("Successfully ran MIPI DSI TX Subsystem self test example\n\r");

	return XST_SUCCESS;
}
#endif

/*****************************************************************************/
/**
*
* This function is the main entry point for the self test example using the
* XDsiTxSs driver. This function check whether or not its sub-core drivers
* self test functions are in working state.
*
* @param	DeviceId is the unique device ID of the MIPI DSI TX
*.		Subsystem core.
*
* @return
*		- XST_FAILURE if any of MIPI DSI RX Subsystem sub-core self
*		test failed.
*		- XST_SUCCESS, if all of MIPI DSI RX Subsystem sub-core self
*		test passed.
*
* @note		None.
*
******************************************************************************/
u32 DsiTxSs_SelfTestExample(u32 DeviceId)
{
	u32 Status;
	XDsiTxSs_Config *ConfigPtr;

	/* Obtain the device configuration for the MIPI DSI TX Subsystem */
	ConfigPtr = XDsiTxSs_LookupConfig(DeviceId);
	if (!ConfigPtr) {
		return XST_FAILURE;
	}

	/* Copy the device configuration into the DsiTxSsInst's Config
	 * structure.
	 */
	Status = XDsiTxSs_CfgInitialize(&DsiTxSsInst, ConfigPtr,
					ConfigPtr->BaseAddr);
	if (Status != XST_SUCCESS) {
		xil_printf("MIPI DSI TX SS config initialization failed.\n\r");
		return XST_FAILURE;
	}

	/* Run the self test. */
	Status = XDsiTxSs_SelfTest(&DsiTxSsInst);

	return Status;
}
