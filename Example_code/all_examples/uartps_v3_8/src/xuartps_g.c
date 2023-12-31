/******************************************************************************
*
* Copyright (C) 2010 - 2015 Xilinx, Inc.  All rights reserved.
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
/****************************************************************************/
/**
*
* @file xuartps_g.c
* @addtogroup uartps_v3_8
* @{
*
* This file contains a configuration table where each entry is a configuration
* structure for an XUartPs device in the system.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who    Date	Changes
* ----- ------ -------- -----------------------------------------------
* 1.00  drg/jz 05/13/08 First Release
* 2.00  hk     22/01/14 Added check for selecting uart0 instance.
* 3.00  kvn    02/13/15 Modified code for MISRA-C:2012 compliance.
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xparameters.h"
#include "xuartps.h"

/************************** Constant Definitions *****************************/


/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/


/************************** Variable Prototypes ******************************/

/**
 * Each XUartPs device in the system has an entry in this table.
 */
XUartPs_Config XUartPs_ConfigTable[XPAR_XUARTPS_NUM_INSTANCES] = {
	{
		(u16)XPAR_XUARTPS_0_DEVICE_ID,
		(u32)XPAR_XUARTPS_0_BASEADDR,
		(u32)XPAR_XUARTPS_0_UART_CLK_FREQ_HZ,
		(s32)0
	},
#ifdef XPAR_XUARTPS_1_DEVICE_ID
	{
		(u16)XPAR_XUARTPS_1_DEVICE_ID,
		(u32)XPAR_XUARTPS_1_BASEADDR,
		(u32)XPAR_XUARTPS_1_UART_CLK_FREQ_HZ,
		(s32)0
	}
#endif
};
/** @} */
