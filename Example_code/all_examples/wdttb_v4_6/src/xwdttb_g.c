/*******************************************************************
* 
* Copyright (C) 2010 - 2020 Xilinx, Inc. All rights reserved.
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
*******************************************************************/
/******************************************************************/
/**
*
* @file xwdttb_g.c
* @addtogroup wdttb_v4_6
* @{
*
* Contains the required functions of the XWdtTb driver. See xwdttb.h for a
* description of the driver.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- ---------------------------------------------------------
* 1.00a ecm  08/16/01 First release
* 4.3   srm  01/30/18 Added doxygen tags
* 4.4   sne  03/04/19 Added support for versal
* 4.5	sne  09/27/19 Added common configuration structure for
*		      AXI Timebase WDT and WWWDT.
*
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/
#include "xparameters.h"
#include "xwdttb.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/
/*
* The configuration table for devices
*/

XWdtTb_Config XWdtTb_ConfigTable[] =
{
	{
		XPAR_WDTTB_0_DEVICE_ID,
		XPAR_WDTTB_0_BASEADDR,
		XPAR_WDTTB_0_ENABLE_WINDOW_WDT,
		XPAR_WDTTB_0_MAX_COUNT_WIDTH,
		XPAR_WDTTB_0_SST_COUNT_WIDTH,
		XPAR_WDTTB_0_IS_PL
	}
};
/** @} */
