// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xdma_demo_v_tpg_0_2_v_tpg.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XDma_demo_v_tpg_0_2_v_tpg_CfgInitialize(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, XDma_demo_v_tpg_0_2_v_tpg_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress = ConfigPtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XDma_demo_v_tpg_0_2_v_tpg_Start(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_AP_CTRL) & 0x80;
    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_IsDone(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XDma_demo_v_tpg_0_2_v_tpg_IsIdle(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XDma_demo_v_tpg_0_2_v_tpg_IsReady(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XDma_demo_v_tpg_0_2_v_tpg_EnableAutoRestart(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_AP_CTRL, 0x80);
}

void XDma_demo_v_tpg_0_2_v_tpg_DisableAutoRestart(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_AP_CTRL, 0);
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_height(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_HEIGHT_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_height(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_HEIGHT_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_width(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_WIDTH_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_width(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_WIDTH_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_bckgndId(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_BCKGNDID_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_bckgndId(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_BCKGNDID_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_ovrlayId(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_OVRLAYID_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_ovrlayId(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_OVRLAYID_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_maskId(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_MASKID_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_maskId(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_MASKID_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_motionSpeed(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_MOTIONSPEED_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_motionSpeed(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_MOTIONSPEED_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_colorFormat(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_COLORFORMAT_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_colorFormat(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_COLORFORMAT_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_crossHairX(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_CROSSHAIRX_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_crossHairX(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_CROSSHAIRX_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_crossHairY(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_CROSSHAIRY_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_crossHairY(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_CROSSHAIRY_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_ZplateHorContStart(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_ZPLATEHORCONTSTART_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_ZplateHorContStart(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_ZPLATEHORCONTSTART_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_ZplateHorContDelta(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_ZPLATEHORCONTDELTA_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_ZplateHorContDelta(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_ZPLATEHORCONTDELTA_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_ZplateVerContStart(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_ZPLATEVERCONTSTART_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_ZplateVerContStart(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_ZPLATEVERCONTSTART_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_ZplateVerContDelta(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_ZPLATEVERCONTDELTA_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_ZplateVerContDelta(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_ZPLATEVERCONTDELTA_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_boxSize(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_BOXSIZE_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_boxSize(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_BOXSIZE_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_boxColorR(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_BOXCOLORR_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_boxColorR(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_BOXCOLORR_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_boxColorG(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_BOXCOLORG_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_boxColorG(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_BOXCOLORG_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_boxColorB(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_BOXCOLORB_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_boxColorB(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_BOXCOLORB_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_dpDynamicRange(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_DPDYNAMICRANGE_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_dpDynamicRange(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_DPDYNAMICRANGE_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_dpYUVCoef(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_DPYUVCOEF_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_dpYUVCoef(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_DPYUVCOEF_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_field_id(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_FIELD_ID_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_field_id(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_FIELD_ID_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_Set_bck_motion_en(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_BCK_MOTION_EN_DATA, Data);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_Get_bck_motion_en(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_BCK_MOTION_EN_DATA);
    return Data;
}

void XDma_demo_v_tpg_0_2_v_tpg_InterruptGlobalEnable(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_GIE, 1);
}

void XDma_demo_v_tpg_0_2_v_tpg_InterruptGlobalDisable(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_GIE, 0);
}

void XDma_demo_v_tpg_0_2_v_tpg_InterruptEnable(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_IER);
    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_IER, Register | Mask);
}

void XDma_demo_v_tpg_0_2_v_tpg_InterruptDisable(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_IER);
    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_IER, Register & (~Mask));
}

void XDma_demo_v_tpg_0_2_v_tpg_InterruptClear(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XDma_demo_v_tpg_0_2_v_tpg_WriteReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_ISR, Mask);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_InterruptGetEnabled(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_IER);
}

u32 XDma_demo_v_tpg_0_2_v_tpg_InterruptGetStatus(XDma_demo_v_tpg_0_2_v_tpg *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XDma_demo_v_tpg_0_2_v_tpg_ReadReg(InstancePtr->Dma_demo_v_tpg_0_2_ctrl_BaseAddress, XDMA_DEMO_V_TPG_0_2_V_TPG_DMA_DEMO_V_TPG_0_2_CTRL_ADDR_ISR);
}

