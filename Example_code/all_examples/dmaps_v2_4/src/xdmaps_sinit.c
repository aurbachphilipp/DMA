/******************************************************************************
*
* Copyright (C) 2009 - 2018 Xilinx, Inc.  All rights reserved.
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
* @file xdmaps_sinit.c
* @addtogroup dmaps_v2_4
* @{
*
* The implementation of the XDmaPs driver's static initialzation
* functionality.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -----------------------------------------------
* 1.00  hbm  08/13/10 First Release
* </pre>
*
*****************************************************************************/

/***************************** Include Files ********************************/

#include "xstatus.h"
#include "xparameters.h"
#include "xdmaps.h"

/************************** Constant Definitions ****************************/

/**************************** Type Definitions ******************************/


/***************** Macros (Inline Functions) Definitions ********************/


/************************** Variable Definitions ****************************/
extern XDmaPs_Config XDmaPs_ConfigTable[];

/************************** Function Prototypes *****************************/

/****************************************************************************/
/**
*
* Looks up the device configuration based on the unique device ID. The table
* contains the configuration info for each device in the system.
*
* @param DeviceId contains the ID of the device
*
* @return
*
* A pointer to the configuration structure or NULL if the specified device
* is not in the system.
*
* @note
*
* None.
*
******************************************************************************/
XDmaPs_Config *XDmaPs_LookupConfig(u16 DeviceId)
{
	XDmaPs_Config *CfgPtr = NULL;

	int i;

	for (i = 0; i < XPAR_XDMAPS_NUM_INSTANCES; i++) {
		if (XDmaPs_ConfigTable[i].DeviceId == DeviceId) {
			CfgPtr = &XDmaPs_ConfigTable[i];
			break;
		}
	}

	return CfgPtr;
}
/** @} */
