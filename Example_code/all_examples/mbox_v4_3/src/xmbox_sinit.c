/******************************************************************************
*
* Copyright (C) 2007 - 2017 Xilinx, Inc.  All rights reserved.
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
* @file xmbox_sinit.c
* @addtogroup mbox_v4_3
* @{
*
* Implements static initialization
* See xmbox.h for more information about the component.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- ---------------------------------------------------
* 1.00a ecm  06/01/07 Cleanup, new coding standard, check into XCS
* 4.2   ms   08/07/17 Fixed compilation warnings.
*
* </pre>
*
******************************************************************************/

/****************************** Include Files ********************************/
#include "xmbox.h"
#include "xparameters.h"

/*************************** Constant Definitions ****************************/

/***************************** Type Definitions ******************************/

/****************** Macros (Inline Functions) Definitions ********************/

/*************************** Variable Definitions ****************************/

extern XMbox_Config XMbox_ConfigTable[];

/*************************** Function Prototypes *****************************/

/*****************************************************************************
*
* Looks up the device configuration based on the unique device ID. The config
* table contains the configuration info for each device in the system.
*
* @param	DeviceId is the unique device ID to search for in the config
*		table.
*
* @return	A pointer to the configuration that matches the given device ID,
*		or NULL if no match is found.
*
* @note		None.
*
******************************************************************************/
XMbox_Config *XMbox_LookupConfig(u16 DeviceId)
{
	XMbox_Config *CfgPtr = NULL;
	u32 Index;

	for (Index = 0U; Index < XPAR_XMBOX_NUM_INSTANCES; Index++) {
		if (XMbox_ConfigTable[Index].DeviceId == DeviceId) {
			CfgPtr = &XMbox_ConfigTable[Index];
			break;
		}
	}

	return CfgPtr;
}
/** @} */
