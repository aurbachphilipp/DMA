/******************************************************************************
*
* Copyright (C) 2014 - 2015 Xilinx, Inc.  All rights reserved.
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
* @file keymgmt_loader.h
*
* This file contains the interface for the key management loader module.
*
******************************************************************************/


#ifndef KEYMGMT_LOADER_H
#define KEYMGMT_LOADER_H


/* Include Files */
#include "keymgmt.h"
#include <stdint.h>


/* Constant Definitions */


/* Type Definitions */


/* Function Prototypes */
KEYMGMT_tError
KEYMGMTLDR_Init(void);


void
KEYMGMTLDR_Poll(uint32_t theUpTime);


int
KEYMGMTLDR_Debug(int argc, const char* argv[]);


#endif /* KEYMGMT_LOADER_H */
