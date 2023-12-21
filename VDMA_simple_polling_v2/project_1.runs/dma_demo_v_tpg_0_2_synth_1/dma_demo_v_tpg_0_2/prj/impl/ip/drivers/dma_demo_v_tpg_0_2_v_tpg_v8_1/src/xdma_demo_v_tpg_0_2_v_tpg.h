// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XDMA_DEMO_V_TPG_0_2_V_TPG_H
#define XDMA_DEMO_V_TPG_0_2_V_TPG_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xdma_demo_v_tpg_0_2_v_tpg_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Dma_demo_v_tpg_0_2_ctrl_BaseAddress;
} XDma_demo_v_tpg_0_2_v_tpg_Config;
#endif

typedef struct {
    u64 Dma_demo_v_tpg_0_2_ctrl_BaseAddress;
    u32 IsReady;
} XDma_demo_v_tpg_0_2_v_tpg;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XDma_demo_v_tpg_0_2_v_tpg_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XDma_demo_v_tpg_0_2_v_tpg_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XDma_demo_v_tpg_0_2_v_tpg_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XDma_demo_v_tpg_0_2_v_tpg_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XDma_demo_v_tpg_0_2_v_tpg_Initialize(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u16 DeviceId);
XDma_demo_v_tpg_0_2_v_tpg_Config* XDma_demo_v_tpg_0_2_v_tpg_LookupConfig(u16 DeviceId);
int XDma_demo_v_tpg_0_2_v_tpg_CfgInitialize(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, XDma_demo_v_tpg_0_2_v_tpg_Config *ConfigPtr);
#else
int XDma_demo_v_tpg_0_2_v_tpg_Initialize(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, const char* InstanceName);
int XDma_demo_v_tpg_0_2_v_tpg_Release(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
#endif

void XDma_demo_v_tpg_0_2_v_tpg_Start(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
u32 XDma_demo_v_tpg_0_2_v_tpg_IsDone(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
u32 XDma_demo_v_tpg_0_2_v_tpg_IsIdle(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
u32 XDma_demo_v_tpg_0_2_v_tpg_IsReady(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_EnableAutoRestart(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_DisableAutoRestart(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);

void XDma_demo_v_tpg_0_2_v_tpg_Set_height(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_height(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_width(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_width(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_bckgndId(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_bckgndId(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_ovrlayId(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_ovrlayId(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_maskId(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_maskId(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_motionSpeed(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_motionSpeed(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_colorFormat(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_colorFormat(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_crossHairX(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_crossHairX(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_crossHairY(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_crossHairY(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_ZplateHorContStart(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_ZplateHorContStart(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_ZplateHorContDelta(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_ZplateHorContDelta(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_ZplateVerContStart(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_ZplateVerContStart(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_ZplateVerContDelta(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_ZplateVerContDelta(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_boxSize(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_boxSize(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_boxColorR(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_boxColorR(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_boxColorG(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_boxColorG(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_boxColorB(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_boxColorB(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_dpDynamicRange(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_dpDynamicRange(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_dpYUVCoef(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_dpYUVCoef(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_field_id(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_field_id(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_Set_bck_motion_en(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data);
u32 XDma_demo_v_tpg_0_2_v_tpg_Get_bck_motion_en(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);

void XDma_demo_v_tpg_0_2_v_tpg_InterruptGlobalEnable(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_InterruptGlobalDisable(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
void XDma_demo_v_tpg_0_2_v_tpg_InterruptEnable(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Mask);
void XDma_demo_v_tpg_0_2_v_tpg_InterruptDisable(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Mask);
void XDma_demo_v_tpg_0_2_v_tpg_InterruptClear(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Mask);
u32 XDma_demo_v_tpg_0_2_v_tpg_InterruptGetEnabled(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);
u32 XDma_demo_v_tpg_0_2_v_tpg_InterruptGetStatus(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
