/******************************************************************************
*
* Copyright (C) 2016 - 2018 Xilinx, Inc.  All rights reserved.
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
* @file xsysmonpsu_sinit.c
* @addtogroup sysmonpsu_v2_5
*
* This file contains the implementation of the XSysMonPsu driver's static
* initialization functionality.
*
* @note		None.
*
* <pre>
*
* MODIFICATION HISTORY:
*
* Ver   Who    Date	    Changes
* ----- -----  -------- -----------------------------------------------
* 1.0   kvn    12/15/15 First release.
*
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xsysmonpsu.h"
#include "xparameters.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

extern XSysMonPsu_Config XSysMonPsu_ConfigTable[XPAR_XSYSMONPSU_NUM_INSTANCES];

/*****************************************************************************/
/**
*
* This function looks for the device configuration based on the unique device
* ID. The table XSysmonPsu_ConfigTable[] contains the configuration information
* for each device in the system.
*
* @param	DeviceId is the unique device ID of the device being looked up.
*
* @return	A pointer to the configuration table entry corresponding to the
*		given device ID, or NULL if no match is found.
*
* @note		None.
*
******************************************************************************/
XSysMonPsu_Config *XSysMonPsu_LookupConfig(u16 DeviceId)
{
	XSysMonPsu_Config *CfgPtr = NULL;
	u32 Index;

	for (Index = 0U; Index < (u32)XPAR_XSYSMONPSU_NUM_INSTANCES; Index++) {
		if (XSysMonPsu_ConfigTable[Index].DeviceId == DeviceId) {
			CfgPtr = &XSysMonPsu_ConfigTable[Index];
			break;
		}
	}

	return CfgPtr;
}
