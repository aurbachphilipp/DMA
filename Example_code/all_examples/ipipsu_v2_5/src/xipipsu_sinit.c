/******************************************************************************
*
* Copyright (C) 2015 - 2016 Xilinx, Inc.  All rights reserved.
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
/**
*
* @file xipipsu_sinit.c
* @addtogroup ipipsu_v2_5
* @{
*
* The implementation of the XIpiPsu component's static initialization
* functionality.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who Date     Changes
* ----- --- -------- -----------------------------------------------
* 1.0   mjr  03/15/15 First release
* 2.1   kvn  05/05/16 Modified code for MISRA-C:2012 Compliance
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/
#include "xil_types.h"
#include "xparameters.h"
#include "xipipsu.h"

/************************** Variable Definitions *****************************/
extern XIpiPsu_Config XIpiPsu_ConfigTable[];

/*****************************************************************************/

/**
*
* Looks up the device configuration based on the unique device ID. A table
* contains the configuration info for each device in the system.
*
* @param	DeviceId contains the ID of the device to look up the
*			configuration for.
*
* @return	A pointer to the configuration found or NULL if the specified
*			device ID was not found. See xipipsu.h for the definition of
*			XIpiPsu_Config.
*
* @note		None.
*
******************************************************************************/
XIpiPsu_Config *XIpiPsu_LookupConfig(u32 DeviceId)
{
	XIpiPsu_Config *CfgPtr = NULL;
	u32 Index;

	for (Index = 0U; Index < XPAR_XIPIPSU_NUM_INSTANCES; Index++) {
		if (XIpiPsu_ConfigTable[Index].DeviceId == DeviceId) {
			CfgPtr = &XIpiPsu_ConfigTable[Index];
			break;
		}
	}

	return CfgPtr;
}
/** @} */
