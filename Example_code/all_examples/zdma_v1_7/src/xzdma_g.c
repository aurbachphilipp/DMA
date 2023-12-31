/*******************************************************************
*
* Copyright (C) 2010-2019 Xilinx, Inc. All rights reserved.
*
*Permission is hereby granted, free of charge, to any person obtaining a copy
*of this software and associated documentation files (the "Software"), to deal
*in the Software without restriction, including without limitation the rights
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*copies of the Software, and to permit persons to whom the Software is
*furnished to do so, subject to the following conditions:
*
*The above copyright notice and this permission notice shall be included in
*all copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
*THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMANGES OR OTHER
*LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*SOFTWARE.
*
*
*
*******************************************************************/

#include "xparameters.h"
#include "xzdma.h"

/*
* The configuration table for devices
*/

XZDma_Config XZDma_ConfigTable[] =
{
	{
		XPAR_PSU_ADMA_CH0_DEVICE_ID,
		XPAR_PSU_ADMA_CH0_BASEADDR,
		XPAR_PSU_ADMA_CH0_DMA_MODE
	},
	{
		XPAR_PSU_ADMA_CH1_DEVICE_ID,
		XPAR_PSU_ADMA_CH1_BASEADDR,
		XPAR_PSU_ADMA_CH1_DMA_MODE
	},
	{
		XPAR_PSU_ADMA_CH2_DEVICE_ID,
		XPAR_PSU_ADMA_CH2_BASEADDR,
		XPAR_PSU_ADMA_CH2_DMA_MODE
	},
	{
		XPAR_PSU_ADMA_CH3_DEVICE_ID,
		XPAR_PSU_ADMA_CH3_BASEADDR,
		XPAR_PSU_ADMA_CH3_DMA_MODE
	},
	{
		XPAR_PSU_ADMA_CH4_DEVICE_ID,
		XPAR_PSU_ADMA_CH4_BASEADDR,
		XPAR_PSU_ADMA_CH4_DMA_MODE
	},
	{
		XPAR_PSU_ADMA_CH5_DEVICE_ID,
		XPAR_PSU_ADMA_CH5_BASEADDR,
		XPAR_PSU_ADMA_CH5_DMA_MODE
	},
	{
		XPAR_PSU_ADMA_CH6_DEVICE_ID,
		XPAR_PSU_ADMA_CH6_BASEADDR,
		XPAR_PSU_ADMA_CH6_DMA_MODE
	},
	{
		XPAR_PSU_ADMA_CH7_DEVICE_ID,
		XPAR_PSU_ADMA_CH7_BASEADDR,
		XPAR_PSU_ADMA_CH7_DMA_MODE
	},
	{
		XPAR_PSU_GDMA_CH0_DEVICE_ID,
		XPAR_PSU_GDMA_CH0_BASEADDR,
		XPAR_PSU_GDMA_CH0_DMA_MODE
	},
	{
		XPAR_PSU_GDMA_CH1_DEVICE_ID,
		XPAR_PSU_GDMA_CH1_BASEADDR,
		XPAR_PSU_GDMA_CH1_DMA_MODE
	},
	{
		XPAR_PSU_GDMA_CH2_DEVICE_ID,
		XPAR_PSU_GDMA_CH2_BASEADDR,
		XPAR_PSU_GDMA_CH2_DMA_MODE
	},
	{
		XPAR_PSU_GDMA_CH3_DEVICE_ID,
		XPAR_PSU_GDMA_CH3_BASEADDR,
		XPAR_PSU_GDMA_CH3_DMA_MODE
	},
	{
		XPAR_PSU_GDMA_CH4_DEVICE_ID,
		XPAR_PSU_GDMA_CH4_BASEADDR,
		XPAR_PSU_GDMA_CH4_DMA_MODE
	},
	{
		XPAR_PSU_GDMA_CH5_DEVICE_ID,
		XPAR_PSU_GDMA_CH5_BASEADDR,
		XPAR_PSU_GDMA_CH5_DMA_MODE
	},
	{
		XPAR_PSU_GDMA_CH6_DEVICE_ID,
		XPAR_PSU_GDMA_CH6_BASEADDR,
		XPAR_PSU_GDMA_CH6_DMA_MODE
	},
	{
		XPAR_PSU_GDMA_CH7_DEVICE_ID,
		XPAR_PSU_GDMA_CH7_BASEADDR,
		XPAR_PSU_GDMA_CH7_DMA_MODE
	}
};
