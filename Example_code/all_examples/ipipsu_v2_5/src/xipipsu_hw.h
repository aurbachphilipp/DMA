/******************************************************************************
*
* Copyright (C) 2015 - 2018 Xilinx, Inc.  All rights reserved.
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
* @file xipipsu_hw.h
* @addtogroup ipipsu_v2_5
* @{
*
* This file contains macro definitions for low level HW related params
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who Date     Changes
* ----- --- -------- -----------------------------------------------.
* 1.0   mjr  03/15/15 First release
* 2.1   kvn  05/05/16 Modified code for MISRA-C:2012 Compliance
 * 2.5  sdd 12/17/18  Add the cpp extern macro.
*
* </pre>
*
******************************************************************************/
#ifndef XIPIPSU_HW_H_	/* prevent circular inclusions */
#define XIPIPSU_HW_H_	/* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/************************** Constant Definitions *****************************/
/* Message RAM related params */
#if defined (versal)
#define XIPIPSU_MSG_RAM_BASE 0xFF3F0000U
#else
#define XIPIPSU_MSG_RAM_BASE 0xFF990000U
#endif
#define XIPIPSU_MSG_BUF_SIZE 8U	/* Size in Words */
#define XIPIPSU_MAX_BUFF_INDEX	7U

/* EIGHT pairs of TWO buffers(msg+resp) of THIRTY TWO bytes each */
#define XIPIPSU_BUFFER_OFFSET_GROUP	(8U * 2U * 32U)
#define XIPIPSU_BUFFER_OFFSET_TARGET (32U * 2U)
#define XIPIPSU_BUFFER_OFFSET_RESPONSE		(32U)

/* Number of IPI slots enabled on the device */
#define XIPIPSU_MAX_TARGETS	XPAR_XIPIPSU_NUM_TARGETS

/* Register Offsets for each member  of IPI Register Set */
#define XIPIPSU_TRIG_OFFSET 0x00U
#define XIPIPSU_OBS_OFFSET 0x04U
#define XIPIPSU_ISR_OFFSET 0x10U
#define XIPIPSU_IMR_OFFSET 0x14U
#define XIPIPSU_IER_OFFSET 0x18U
#define XIPIPSU_IDR_OFFSET 0x1CU

/* MASK of all valid IPI bits in above registers */
#if defined (versal)
#define XIPIPSU_ALL_MASK	0x000003FFU
#else
#define XIPIPSU_ALL_MASK	0x0F0F0301U
#endif

#ifdef __cplusplus
}
#endif

#endif /* XIPIPSU_HW_H_ */
/** @} */
