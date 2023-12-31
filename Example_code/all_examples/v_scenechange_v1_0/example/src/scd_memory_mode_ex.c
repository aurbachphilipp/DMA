/******************************************************************************
 *
 * Copyright (C) 2018 Xilinx, Inc.      All rights reserved.
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
 * XILINX BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name of the Xilinx shall not be used
 * in advertising or otherwise to promote the sale, use or other dealings in
 * this Software without prior written authorization from Xilinx.
 *
******************************************************************************/
/*
 * scd_memory_mode_ex.c: scenechange IP in memory mode test application.
 *
 * This application configures SceneChange IP to caluclate SAD values between
 * consecutive streams. The driver accepts the threshold values per stream and
 * calls the registered callback with SAD value and stream id.
 *
 */
#include "xparameters.h"
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xscugic.h"
#include "xil_io.h"
#include "xil_cache.h"
#include "sleep.h"
#include "xvidc.h"
#include "xv_scenechange.h"
#include "xscugic.h"

/*Reset all IPs in pipeline */
#define IP_RESET_MASK		0xF
/************** User Configurable Data for testing*******************************/
#define	SCD_STREAMS_ENABLE	1
/* users is changing the data in Layer 0 */
#define SCD_LAYER_0		0
#define MAX_PATTERNS		8

/* Different patterns to write in the memory location for the streams */
volatile u32 local_mem[8] = {0xFF00FF, 0xFFFF00, 0xFF0000, 0x00FFFF,
	0xFFFF00, 0xFF00FF, 0x00FFFF, 0xFF0000};

/* Different memory location for the streams */
u64 memaddr[8] = {0x10000000, 0x20000000, 0x20400000, 0x20800000,
	0x30000000, 0x30400000, 0x30800000, 0x40000000};

/* below are the configurable parameters: user can give height and width
 * to 4320, 8192 and stride value, histbits, color format, threshold is
 * based on SceneChange IP PG*/
u32 scd_height[XV_SCD_IP_MAX_STREAMS]	= {720, 0, 0, 0, 0, 0, 0, 0};
u32 scd_width[XV_SCD_IP_MAX_STREAMS] 	= {1280, 0, 0, 0, 0, 0, 0, 0};
u32 scd_stride[XV_SCD_IP_MAX_STREAMS]	= {1280, 0, 0, 0, 0, 0, 0, 0};
u32 scd_histbits[XV_SCD_IP_MAX_STREAMS]	= {16, 0, 0, 0, 0, 0, 0, 0};
u32 scd_clrfmt[XV_SCD_IP_MAX_STREAMS]	= {XV_SCD_HAS_Y8, 0, 0, 0, 0, 0, 0, 0};
u32 scd_threshold[XV_SCD_IP_MAX_STREAMS] = {1, 0, 0, 0, 0, 0, 0, 0};

/************************** Variable Definitions *****************************/

volatile u8 is_detected, sc_detected;
XScuGic Intc;
XV_scenechange ScdPtr;

/************************** Function Prototypes ******************************/

void SceneChangeDetectedCallback(void *CallbackRef);

/************************** Function Definitions *****************************/

void ClearScreen(void)
{
	xil_printf("%c\[2J", 27);
	xil_printf("%c\033[0;0H", 27);
}

static int SetupInterruptSystem(void)
{
	int Status;
	XScuGic *IntcInstPtr = &Intc;

	XScuGic_Config *IntcCfgPtr;
	IntcCfgPtr = XScuGic_LookupConfig(XPAR_PSU_ACPU_GIC_DEVICE_ID);
	if (!IntcCfgPtr) {
		xil_printf("ERR:: Interrupt Controller not found");
		return XST_DEVICE_NOT_FOUND;
	}
	Status = XScuGic_CfgInitialize(IntcInstPtr,
			IntcCfgPtr,
			IntcCfgPtr->CpuBaseAddress);

	if (Status != XST_SUCCESS) {
		xil_printf("Intc initialization failed!\r\n");
		return XST_FAILURE;
	}

	Xil_ExceptionInit();

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			(Xil_ExceptionHandler)XScuGic_InterruptHandler,
			(XScuGic *)IntcInstPtr);

	return XST_SUCCESS;
}

void SceneChangeDetectedCallback(void *CallbackRef)
{
	xil_printf("IN CB: Layer:%d SAD:%X\r\n", ScdPtr.scddetlayerid,
			ScdPtr.scdlayerdetSAD);
	is_detected = 1;
}

int XV_SceneChange_init(u16 DeviceId)
{

	XV_scenechange_Config *scd_config;
	int Status;
	u32 streams = 0;

	scd_config = XV_scenechange_LookupConfig(DeviceId);
	if (scd_config == NULL)
		return XST_FAILURE;

	/* Initialize top level and all included sub-cores */
	Status = XV_scenechange_Initialize(&ScdPtr, DeviceId);
	if (Status != XST_SUCCESS)
		return XST_FAILURE;

	XV_scenechange_Layer_stream_enable(&ScdPtr, SCD_STREAMS_ENABLE);

	for (streams = 0; streams < ScdPtr.scd_config->num_streams; streams++) {
		if (SCD_STREAMS_ENABLE & (1 << streams)) {
			xil_printf("(%d) stream configuring...\r\n", streams);
			ScdPtr.glconfig[streams].height		= scd_height[streams];
			ScdPtr.glconfig[streams].width		= scd_width[streams];
			ScdPtr.glconfig[streams].stride		= scd_stride[streams];
			ScdPtr.glconfig[streams].video_format	= scd_clrfmt[streams];
			ScdPtr.glconfig[streams].subsample	= scd_histbits[streams];
			ScdPtr.glconfig[streams].buffer		= memaddr[streams];
			ScdPtr.glconfig[streams].threshold	= scd_threshold[streams];
			Status = XV_scenechange_Layer_config(&ScdPtr, streams);
			if(Status == XST_FAILURE) {
				xil_printf("ERR:: Unable to configure SD Layer\r\n");
				return XST_FAILURE;
			}
			memset((char *)memaddr[streams], local_mem[streams],
					scd_height[streams] * scd_width[streams]);
		}
	}

	XV_scenechange_SetCallback(&ScdPtr, SceneChangeDetectedCallback,
			(void *) &ScdPtr);

	Status |= XScuGic_Connect(&Intc,
			XPAR_FABRIC_V_SCENECHANGE_0_VEC_ID,
			(XInterruptHandler)XV_scenechange_InterruptHandler,
			(void *)&ScdPtr);
	if (Status == XST_SUCCESS) {
		XScuGic_Enable(&Intc, XPAR_FABRIC_V_SCENECHANGE_0_VEC_ID);
	} else {
		xil_printf("ERR:: Unable to register SD interrupt handler");
		return XST_FAILURE;
	}

	XV_scenechange_InterruptGlobalEnable(&ScdPtr);
	XV_scenechange_EnableInterrupts(&ScdPtr);
	XV_scenechange_EnableAutoRestart(&ScdPtr);
	XV_scenechange_Start(&ScdPtr);

	return XST_SUCCESS;
}

void reset_pipe(void)
{
	Xil_Out32(0xFF0A0018, 0xFFFF0000);
	Xil_Out32(0xFF0A02C4, 0xFFFFFFFF);
	Xil_Out32(0xFF0A02C8, 0xFFFFFFFF);
	Xil_Out32(0xFF0A004C, IP_RESET_MASK);
	Xil_Out32(0xFF0A004C, 0x00000000);
	Xil_Out32(0xFF0A004C, IP_RESET_MASK);

	xil_printf("Reset SCD - Done.\r\n");
}

int main()
{
	u8 state;

	ClearScreen();

	xil_printf("-----------------------------------------\r\n");
	xil_printf("---   SceneChange IP Application --------\r\n");
	xil_printf("---     (c) 2018 by Xilinx, Inc.     ----\r\n");
	xil_printf("----------------------------------------\r\n");
	xil_printf("      Build %s - %s \r\n", __DATE__, __TIME__);
	xil_printf("-----------------------------------------\r\n");

	Xil_DCacheDisable();
	Xil_ExceptionDisable();
	init_platform();

	state = SetupInterruptSystem();
	if (state != XST_SUCCESS) {
		xil_printf("SetupInterrupt() is Failed.\r\n");
		return XST_FAILURE;
	}

	reset_pipe();

	xil_printf("SceneChange initialization - Started\r\n");

	state = XV_SceneChange_init(XPAR_XV_SCENECHANGE_0_DEVICE_ID);
	if (state != XST_SUCCESS) {
		xil_printf("SceneChange_init Failed.\n");
		return XST_FAILURE;
	}
	Xil_ExceptionEnable();

	do {
		if(is_detected) {
			is_detected = 0;
			sc_detected++;
		}

		if(++state >= MAX_PATTERNS) {
			if(sc_detected)
				goto SCD_DONE;
			else
				goto SCD_FAILED;
		}

		/* pattern is changing on Layer-0 to test - used can configure*/
		memset((char *)memaddr[SCD_LAYER_0], local_mem[state],
				scd_height[SCD_LAYER_0] * scd_width[SCD_LAYER_0]);
		sleep(1);
	} while(1);

SCD_DONE:
	XV_scenechange_Stop(&ScdPtr);
	xil_printf("SceneChange test : PASSED\r\n");
	return XST_SUCCESS;

SCD_FAILED:
	XV_scenechange_Stop(&ScdPtr);
	xil_printf("SceneChange test : FAILURE\r\n");
	return  XST_FAILURE;
}
