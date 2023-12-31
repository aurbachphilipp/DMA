/******************************************************************************
*
* Copyright (C) 2015 Xilinx, Inc.  All rights reserved.
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
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
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
* @file xhdcp_example.h
*
* This file provides the interface of the HDCP example
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who    Date     Changes
* ----- ------ -------- --------------------------------------------------
* 1.00         07/16/15 Initial release.
* </pre>
*
******************************************************************************/
#ifndef XHDCP1X_EXAMPLE_H
/**< Prevent circular inclusions by using protection macros */
#define XHDCP1X_EXAMPLE_H

#ifdef __cplusplus
extern "C" {
#endif


/***************************** Include Files *********************************/
#include "xparameters.h"
#if (XPAR_XHDCP_NUM_INSTANCES > 0)
#include "xhdcp1x.h"
#include "xil_types.h"

/************************** Constant Definitions *****************************/


/***************** Macros (Inline Functions) Definitions *********************/


/**************************** Type Definitions *******************************/


/****************************** Local Globals ********************************/


/************************** Function Prototypes ******************************/

int XHdcp1xExample_Init(void);
int XHdcp1xExample_Enable(void);
void XHdcp1xExample_Poll(void);
int XHdcp1xExample_TxEncrypt(void);
int XHdcp1xExample_TxAuthenticate(void);
int XHdcp1xExample_TxIsCapable(void);
int XHdcp1xExample_TxEncryptIfRxIsUp(void);
int XHdcp1xExample_TxIsAuthenticated(void);

XHdcp1x* XHdcp1xExample_Get(u16 DeviceId);

#ifdef __cplusplus
}
#endif

#endif

#endif  /* XHDCP1X_EXAMPLE_H */
