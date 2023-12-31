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
* @file xsrio_g.c
* @addtogroup srio_v1_2
* @{
*
* This file contains a configuration table that specifies the configuration of
* SRIO devices in the system. Each SRIO device in the system should have an entry
* in the table.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.0   adk  16/04/14 Initial release
*
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xsrio.h"
#include "xparameters.h"

/************************** Constant Definitions *****************************/

XSrio_Config XSrio_ConfigTable[] =
{
	{
		XPAR_SRIO_0_DEVICE_ID,
		XPAR_SRIO_0_BASEADDR,
		XPAR_SRIO_0_PE_MEMORY,
		XPAR_SRIO_0_PE_PROC,
		XPAR_SRIO_0_PE_BRIDGE
	}
};
/** @} */
