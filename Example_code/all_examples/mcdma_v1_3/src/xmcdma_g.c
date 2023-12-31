/*******************************************************************
* Copyright (C) 2010 - 2019 Xilinx, Inc. All rights reserved.
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

*******************************************************************************/*


#include "xparameters.h"
#include "xmcdma.h"

/*
* The configuration table for devices
*/

XMcdma_Config XMcdma_ConfigTable[] =
{
	{
		XPAR_AXI_MCDMA_0_DEVICE_ID,
		XPAR_AXI_MCDMA_0_BASEADDR,
		XPAR_AXI_MCDMA_0_ADDR_WIDTH,
		XPAR_AXI_MCDMA_0_ENABLE_SINGLE_INTR,
		XPAR_AXI_MCDMA_0_INCLUDE_MM2S,
		XPAR_AXI_MCDMA_0_INCLUDE_MM2S_DRE,
		XPAR_AXI_MCDMA_0_NUM_MM2S_CHANNELS,
		XPAR_AXI_MCDMA_0_INCLUDE_S2MM,
		XPAR_AXI_MCDMA_0_INCLUDE_S2MM_DRE,
		XPAR_AXI_MCDMA_0_NUM_S2MM_CHANNELS,
		XPAR_AXI_MCDMA_0_M_AXI_MM2S_DATA_WIDTH,
		XPAR_AXI_MCDMA_0_M_AXI_S2MM_DATA_WIDTH,
		XPAR_AXI_MCDMA_0_SG_LENGTH_WIDTH,
		XPAR_AXI_MCDMA_0_SG_INCLUDE_STSCNTRL_STRM
	}
};
