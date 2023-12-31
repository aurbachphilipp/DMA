/******************************************************************************
*
* Copyright (C) 2010 - 2018 Xilinx, Inc.  All rights reserved.
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
* @file xaxicdma_sinit.c
* @addtogroup axicdma_v4_5
* @{
*
* Look up the hardware settings using device ID. The hardware setting is inside
* the configuration table in xaxivdma_g.c, generated automatically by XPS or
* manually by user.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a jz   08/16/10 First release
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xparameters.h"
#include "xaxicdma.h"


/*****************************************************************************/
/**
 * Look up the hardware configuration for a device instance
 *
 * @param	DeviceId is the unique device ID of the device to lookup for
 *
 * @return	The configuration structure for the device. If the device ID
 *		is not found,a NULL pointer is returned.
 *
 * @note	None.
 *
 ******************************************************************************/
XAxiCdma_Config *XAxiCdma_LookupConfig(u32 DeviceId)
{
	extern XAxiCdma_Config XAxiCdma_ConfigTable[];
	XAxiCdma_Config *CfgPtr = NULL;
	int i;

	for (i = 0; i < XPAR_XAXICDMA_NUM_INSTANCES; i++) {

		if (XAxiCdma_ConfigTable[i].DeviceId == DeviceId) {

			CfgPtr = &XAxiCdma_ConfigTable[i];
			break;
		}
	}

	return CfgPtr;
}
/** @} */
