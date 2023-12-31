/******************************************************************************
*
* Copyright (C) 2015 - 2016 Xilinx, Inc. All rights reserved.
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
* @file xhdcp1x_port_intr.c
* @addtogroup hdcp1x_v4_2
* @{
*
* This contains the interrupt related functions of the Xilinx HDCP port driver
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who    Date     Changes
* ----- ------ -------- --------------------------------------------------
* 1.00  fidus  07/16/15 Initial release.
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xhdcp1x_port.h"
#include "xil_assert.h"
#include "xil_types.h"
#include "xparameters.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Definitions *****************************/

/*****************************************************************************/
/**
* This function installs an asynchronous callback function for the given
* HandlerType:
*
* <pre>
* HandlerType                           Callback Function Type
* ------------------------------------  -------------------------------------
* (XHDCP1X_PORT_HANDLER_AUTHENTICATE)   AuthCallback
* </pre>
*
* @param	InstancePtr is a pointer to the HDCP port instance.
* @param	HandlerType specifies the type of handler.
* @param	CallbackFunc is the address of the callback function.
* @param	CallbackRef is a user data item that will be passed to the
*		callback function when it is invoked.
*
* @return
*		- XST_SUCCESS if callback function installed successfully.
*		- XST_INVALID_PARAM when HandlerType is invalid.
*
* @note		Invoking this function for a handler that already has been
*		installed replaces it with the new handler.
*
******************************************************************************/
int XHdcp1x_PortSetCallback(XHdcp1x *InstancePtr, u32 HandlerType,
                XHdcp1x_Callback CallbackFunc, void *CallbackRef)
{
	u32 Status = XST_SUCCESS;

	/* Verify arguments. */
	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(HandlerType >= (XHDCP1X_PORT_HANDLER_AUTHENTICATE));
	Xil_AssertNonvoid(CallbackFunc != NULL);
	Xil_AssertNonvoid(CallbackRef != NULL);

	/* Check for handler type */
	switch (HandlerType) {
		/* Authentication Callback */
		case (XHDCP1X_PORT_HANDLER_AUTHENTICATE):
			InstancePtr->Port.AuthCallback = CallbackFunc;
			InstancePtr->Port.AuthRef = CallbackRef;
			InstancePtr->Port.IsAuthCallbackSet = (TRUE);
			break;

		default:
			Status = (XST_INVALID_PARAM);
			break;
	}

	return (Status);
}

/*****************************************************************************/
/**
* This handles an interrupt generated by a HDCP port device.
*
* @param	InstancePtr is the device to write to.
* @param	IntCause is the interrupt cause bit map.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void XHdcp1x_PortHandleInterrupt(XHdcp1x *InstancePtr, u32 IntCause)
{
	const XHdcp1x_PortPhyIfAdaptor *Adaptor = NULL;

	/* Verify arguments. */
	Xil_AssertVoid(InstancePtr != NULL);

	/* Determine Adaptor */
	Adaptor = InstancePtr->Port.Adaptor;

	/* Check for adaptor function and invoke if present */
	if ((Adaptor != NULL) && (Adaptor->IntrHandler != NULL)) {
		InstancePtr->Port.Stats.IntCount++;
		(*(Adaptor->IntrHandler))(InstancePtr, IntCause);
	}
}
/** @} */
