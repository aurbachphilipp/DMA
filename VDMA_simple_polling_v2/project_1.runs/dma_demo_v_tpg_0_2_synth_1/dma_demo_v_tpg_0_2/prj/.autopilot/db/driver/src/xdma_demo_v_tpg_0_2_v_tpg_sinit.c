// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xdma_demo_v_tpg_0_2_v_tpg.h"

extern XDma_demo_v_tpg_0_2_v_tpg_Config XDma_demo_v_tpg_0_2_v_tpg_ConfigTable[];

XDma_demo_v_tpg_0_2_v_tpg_Config *XDma_demo_v_tpg_0_2_v_tpg_LookupConfig(u16 DeviceId) {
	XDma_demo_v_tpg_0_2_v_tpg_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XDMA_DEMO_V_TPG_0_2_V_TPG_NUM_INSTANCES; Index++) {
		if (XDma_demo_v_tpg_0_2_v_tpg_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XDma_demo_v_tpg_0_2_v_tpg_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XDma_demo_v_tpg_0_2_v_tpg_Initialize(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u16 DeviceId) {
	XDma_demo_v_tpg_0_2_v_tpg_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XDma_demo_v_tpg_0_2_v_tpg_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XDma_demo_v_tpg_0_2_v_tpg_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

