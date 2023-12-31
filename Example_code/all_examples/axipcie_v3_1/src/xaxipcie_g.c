/******************************************************************************
*
* Copyright (C) 2011 - 2014 Xilinx, Inc.  All rights reserved.
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
* @file xaxipcie_g.c
* @addtogroup axipcie_v3_1
* @{
*
* This file contains a configuration table that specifies the configuration
* of AXI PCIe devices in the system.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- ---------------------------------------------------
* 1.00a rkv  03/03/11 Original code.
* 2.00a rkv  07/19/11  Added support of pcie root complex functionality.
*
* </pre>
*
* @note
*
* None.
*
*****************************************************************************/

/***************************** Include Files ********************************/
#include "xparameters.h"
#include "xaxipcie.h"

/************************** Constant Definitions ****************************/


/**************************** Type Definitions ******************************/


/***************** Macros (Inline Functions) Definitions ********************/


/************************** Function Prototypes *****************************/


/************************** Variable Prototypes *****************************/

XAxiPcie_Config XAxiPcie_ConfigTable[] = {
	{
	 XPAR_AXIPCIE_0_DEVICE_ID,
	 XPAR_AXIPCIE_0_BASEADDR,
	 XPAR_AXIPCIE_0_AXI_BAR_NUM,
	 XPAR_AXIPCIE_0_INCLUDE_BAROFFSET_REG,
	 XPAR_AXI_PCIE_0_INCLUDE_RC
	}
};

/** @} */
