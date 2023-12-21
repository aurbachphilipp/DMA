#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

// wrapc file define:
#define AUTOTB_TVIN_height "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_height.dat"
#define AUTOTB_TVOUT_height "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_height.dat"
// wrapc file define:
#define AUTOTB_TVIN_width "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_width.dat"
#define AUTOTB_TVOUT_width "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_width.dat"
// wrapc file define:
#define AUTOTB_TVIN_field_id "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_field_id.dat"
#define AUTOTB_TVOUT_field_id "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_field_id.dat"
// wrapc file define:
#define AUTOTB_TVIN_fid_in "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_fid_in.dat"
#define AUTOTB_TVOUT_fid_in "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_fid_in.dat"
// wrapc file define:
#define AUTOTB_TVIN_bckgndId "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_bckgndId.dat"
#define AUTOTB_TVOUT_bckgndId "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_bckgndId.dat"
// wrapc file define:
#define AUTOTB_TVIN_ovrlayId "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_ovrlayId.dat"
#define AUTOTB_TVOUT_ovrlayId "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_ovrlayId.dat"
// wrapc file define:
#define AUTOTB_TVIN_maskId "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_maskId.dat"
#define AUTOTB_TVOUT_maskId "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_maskId.dat"
// wrapc file define:
#define AUTOTB_TVIN_motionSpeed "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_motionSpeed.dat"
#define AUTOTB_TVOUT_motionSpeed "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_motionSpeed.dat"
// wrapc file define:
#define AUTOTB_TVIN_colorFormat "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_colorFormat.dat"
#define AUTOTB_TVOUT_colorFormat "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_colorFormat.dat"
// wrapc file define:
#define AUTOTB_TVIN_crossHairX "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_crossHairX.dat"
#define AUTOTB_TVOUT_crossHairX "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_crossHairX.dat"
// wrapc file define:
#define AUTOTB_TVIN_crossHairY "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_crossHairY.dat"
#define AUTOTB_TVOUT_crossHairY "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_crossHairY.dat"
// wrapc file define:
#define AUTOTB_TVIN_ZplateHorContStart "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_ZplateHorContStart.dat"
#define AUTOTB_TVOUT_ZplateHorContStart "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_ZplateHorContStart.dat"
// wrapc file define:
#define AUTOTB_TVIN_ZplateHorContDelta "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_ZplateHorContDelta.dat"
#define AUTOTB_TVOUT_ZplateHorContDelta "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_ZplateHorContDelta.dat"
// wrapc file define:
#define AUTOTB_TVIN_ZplateVerContStart "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_ZplateVerContStart.dat"
#define AUTOTB_TVOUT_ZplateVerContStart "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_ZplateVerContStart.dat"
// wrapc file define:
#define AUTOTB_TVIN_ZplateVerContDelta "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_ZplateVerContDelta.dat"
#define AUTOTB_TVOUT_ZplateVerContDelta "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_ZplateVerContDelta.dat"
// wrapc file define:
#define AUTOTB_TVIN_boxSize "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_boxSize.dat"
#define AUTOTB_TVOUT_boxSize "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_boxSize.dat"
// wrapc file define:
#define AUTOTB_TVIN_boxColorR "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_boxColorR.dat"
#define AUTOTB_TVOUT_boxColorR "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_boxColorR.dat"
// wrapc file define:
#define AUTOTB_TVIN_boxColorG "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_boxColorG.dat"
#define AUTOTB_TVOUT_boxColorG "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_boxColorG.dat"
// wrapc file define:
#define AUTOTB_TVIN_boxColorB "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_boxColorB.dat"
#define AUTOTB_TVOUT_boxColorB "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_boxColorB.dat"
// wrapc file define:
#define AUTOTB_TVIN_dpDynamicRange "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_dpDynamicRange.dat"
#define AUTOTB_TVOUT_dpDynamicRange "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_dpDynamicRange.dat"
// wrapc file define:
#define AUTOTB_TVIN_dpYUVCoef "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_dpYUVCoef.dat"
#define AUTOTB_TVOUT_dpYUVCoef "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_dpYUVCoef.dat"
// wrapc file define:
#define AUTOTB_TVIN_bck_motion_en "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_bck_motion_en.dat"
#define AUTOTB_TVOUT_bck_motion_en "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_bck_motion_en.dat"
// wrapc file define:
#define AUTOTB_TVIN_m_axis_video_V_data_V "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_m_axis_video_V_data_V.dat"
#define AUTOTB_TVOUT_m_axis_video_V_data_V "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_m_axis_video_V_data_V.dat"
#define AUTOTB_TVIN_m_axis_video_V_keep_V "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_m_axis_video_V_keep_V.dat"
#define AUTOTB_TVOUT_m_axis_video_V_keep_V "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_m_axis_video_V_keep_V.dat"
#define AUTOTB_TVIN_m_axis_video_V_strb_V "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_m_axis_video_V_strb_V.dat"
#define AUTOTB_TVOUT_m_axis_video_V_strb_V "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_m_axis_video_V_strb_V.dat"
#define AUTOTB_TVIN_m_axis_video_V_user_V "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_m_axis_video_V_user_V.dat"
#define AUTOTB_TVOUT_m_axis_video_V_user_V "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_m_axis_video_V_user_V.dat"
#define AUTOTB_TVIN_m_axis_video_V_last_V "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_m_axis_video_V_last_V.dat"
#define AUTOTB_TVOUT_m_axis_video_V_last_V "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_m_axis_video_V_last_V.dat"
#define AUTOTB_TVIN_m_axis_video_V_id_V "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_m_axis_video_V_id_V.dat"
#define AUTOTB_TVOUT_m_axis_video_V_id_V "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_m_axis_video_V_id_V.dat"
#define AUTOTB_TVIN_m_axis_video_V_dest_V "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_m_axis_video_V_dest_V.dat"
#define AUTOTB_TVOUT_m_axis_video_V_dest_V "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_m_axis_video_V_dest_V.dat"
#define WRAPC_STREAM_SIZE_OUT_m_axis_video_V_data_V "../tv/stream_size/stream_size_out_m_axis_video_V_data_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_m_axis_video_V_data_V "../tv/stream_size/stream_egress_status_m_axis_video_V_data_V.dat"
#define WRAPC_STREAM_SIZE_OUT_m_axis_video_V_keep_V "../tv/stream_size/stream_size_out_m_axis_video_V_keep_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_m_axis_video_V_keep_V "../tv/stream_size/stream_egress_status_m_axis_video_V_keep_V.dat"
#define WRAPC_STREAM_SIZE_OUT_m_axis_video_V_strb_V "../tv/stream_size/stream_size_out_m_axis_video_V_strb_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_m_axis_video_V_strb_V "../tv/stream_size/stream_egress_status_m_axis_video_V_strb_V.dat"
#define WRAPC_STREAM_SIZE_OUT_m_axis_video_V_user_V "../tv/stream_size/stream_size_out_m_axis_video_V_user_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_m_axis_video_V_user_V "../tv/stream_size/stream_egress_status_m_axis_video_V_user_V.dat"
#define WRAPC_STREAM_SIZE_OUT_m_axis_video_V_last_V "../tv/stream_size/stream_size_out_m_axis_video_V_last_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_m_axis_video_V_last_V "../tv/stream_size/stream_egress_status_m_axis_video_V_last_V.dat"
#define WRAPC_STREAM_SIZE_OUT_m_axis_video_V_id_V "../tv/stream_size/stream_size_out_m_axis_video_V_id_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_m_axis_video_V_id_V "../tv/stream_size/stream_egress_status_m_axis_video_V_id_V.dat"
#define WRAPC_STREAM_SIZE_OUT_m_axis_video_V_dest_V "../tv/stream_size/stream_size_out_m_axis_video_V_dest_V.dat"
#define WRAPC_STREAM_EGRESS_STATUS_m_axis_video_V_dest_V "../tv/stream_size/stream_egress_status_m_axis_video_V_dest_V.dat"
// wrapc file define:
#define AUTOTB_TVIN_fid "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvin_fid.dat"
#define AUTOTB_TVOUT_fid "../tv/cdatafile/c.dma_demo_v_tpg_0_2_v_tpg.autotvout_fid.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_height "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_height.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_width "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_width.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_field_id "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_field_id.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_fid_in "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_fid_in.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_bckgndId "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_bckgndId.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_ovrlayId "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_ovrlayId.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_maskId "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_maskId.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_motionSpeed "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_motionSpeed.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_colorFormat "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_colorFormat.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_crossHairX "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_crossHairX.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_crossHairY "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_crossHairY.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_ZplateHorContStart "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_ZplateHorContStart.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_ZplateHorContDelta "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_ZplateHorContDelta.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_ZplateVerContStart "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_ZplateVerContStart.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_ZplateVerContDelta "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_ZplateVerContDelta.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_boxSize "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_boxSize.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_boxColorR "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_boxColorR.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_boxColorG "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_boxColorG.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_boxColorB "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_boxColorB.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_dpDynamicRange "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_dpDynamicRange.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_dpYUVCoef "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_dpYUVCoef.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_bck_motion_en "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_bck_motion_en.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_m_axis_video_V_data_V "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_m_axis_video_V_data_V.dat"
#define AUTOTB_TVOUT_PC_m_axis_video_V_keep_V "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_m_axis_video_V_keep_V.dat"
#define AUTOTB_TVOUT_PC_m_axis_video_V_strb_V "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_m_axis_video_V_strb_V.dat"
#define AUTOTB_TVOUT_PC_m_axis_video_V_user_V "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_m_axis_video_V_user_V.dat"
#define AUTOTB_TVOUT_PC_m_axis_video_V_last_V "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_m_axis_video_V_last_V.dat"
#define AUTOTB_TVOUT_PC_m_axis_video_V_id_V "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_m_axis_video_V_id_V.dat"
#define AUTOTB_TVOUT_PC_m_axis_video_V_dest_V "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_m_axis_video_V_dest_V.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_fid "../tv/rtldatafile/rtl.dma_demo_v_tpg_0_2_v_tpg.autotvout_fid.dat"

class INTER_TCL_FILE {
  public:
INTER_TCL_FILE(const char* name) {
  mName = name; 
  height_depth = 0;
  width_depth = 0;
  field_id_depth = 0;
  fid_in_depth = 0;
  bckgndId_depth = 0;
  ovrlayId_depth = 0;
  maskId_depth = 0;
  motionSpeed_depth = 0;
  colorFormat_depth = 0;
  crossHairX_depth = 0;
  crossHairY_depth = 0;
  ZplateHorContStart_depth = 0;
  ZplateHorContDelta_depth = 0;
  ZplateVerContStart_depth = 0;
  ZplateVerContDelta_depth = 0;
  boxSize_depth = 0;
  boxColorR_depth = 0;
  boxColorG_depth = 0;
  boxColorB_depth = 0;
  dpDynamicRange_depth = 0;
  dpYUVCoef_depth = 0;
  bck_motion_en_depth = 0;
  m_axis_video_V_data_V_depth = 0;
  m_axis_video_V_keep_V_depth = 0;
  m_axis_video_V_strb_V_depth = 0;
  m_axis_video_V_user_V_depth = 0;
  m_axis_video_V_last_V_depth = 0;
  m_axis_video_V_id_V_depth = 0;
  m_axis_video_V_dest_V_depth = 0;
  fid_depth = 0;
  trans_num =0;
}
~INTER_TCL_FILE() {
  mFile.open(mName);
  if (!mFile.good()) {
    cout << "Failed to open file ref.tcl" << endl;
    exit (1); 
  }
  string total_list = get_depth_list();
  mFile << "set depth_list {\n";
  mFile << total_list;
  mFile << "}\n";
  mFile << "set trans_num "<<trans_num<<endl;
  mFile.close();
}
string get_depth_list () {
  stringstream total_list;
  total_list << "{height " << height_depth << "}\n";
  total_list << "{width " << width_depth << "}\n";
  total_list << "{field_id " << field_id_depth << "}\n";
  total_list << "{fid_in " << fid_in_depth << "}\n";
  total_list << "{bckgndId " << bckgndId_depth << "}\n";
  total_list << "{ovrlayId " << ovrlayId_depth << "}\n";
  total_list << "{maskId " << maskId_depth << "}\n";
  total_list << "{motionSpeed " << motionSpeed_depth << "}\n";
  total_list << "{colorFormat " << colorFormat_depth << "}\n";
  total_list << "{crossHairX " << crossHairX_depth << "}\n";
  total_list << "{crossHairY " << crossHairY_depth << "}\n";
  total_list << "{ZplateHorContStart " << ZplateHorContStart_depth << "}\n";
  total_list << "{ZplateHorContDelta " << ZplateHorContDelta_depth << "}\n";
  total_list << "{ZplateVerContStart " << ZplateVerContStart_depth << "}\n";
  total_list << "{ZplateVerContDelta " << ZplateVerContDelta_depth << "}\n";
  total_list << "{boxSize " << boxSize_depth << "}\n";
  total_list << "{boxColorR " << boxColorR_depth << "}\n";
  total_list << "{boxColorG " << boxColorG_depth << "}\n";
  total_list << "{boxColorB " << boxColorB_depth << "}\n";
  total_list << "{dpDynamicRange " << dpDynamicRange_depth << "}\n";
  total_list << "{dpYUVCoef " << dpYUVCoef_depth << "}\n";
  total_list << "{bck_motion_en " << bck_motion_en_depth << "}\n";
  total_list << "{m_axis_video_V_data_V " << m_axis_video_V_data_V_depth << "}\n";
  total_list << "{m_axis_video_V_keep_V " << m_axis_video_V_keep_V_depth << "}\n";
  total_list << "{m_axis_video_V_strb_V " << m_axis_video_V_strb_V_depth << "}\n";
  total_list << "{m_axis_video_V_user_V " << m_axis_video_V_user_V_depth << "}\n";
  total_list << "{m_axis_video_V_last_V " << m_axis_video_V_last_V_depth << "}\n";
  total_list << "{m_axis_video_V_id_V " << m_axis_video_V_id_V_depth << "}\n";
  total_list << "{m_axis_video_V_dest_V " << m_axis_video_V_dest_V_depth << "}\n";
  total_list << "{fid " << fid_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int height_depth;
    int width_depth;
    int field_id_depth;
    int fid_in_depth;
    int bckgndId_depth;
    int ovrlayId_depth;
    int maskId_depth;
    int motionSpeed_depth;
    int colorFormat_depth;
    int crossHairX_depth;
    int crossHairY_depth;
    int ZplateHorContStart_depth;
    int ZplateHorContDelta_depth;
    int ZplateVerContStart_depth;
    int ZplateVerContDelta_depth;
    int boxSize_depth;
    int boxColorR_depth;
    int boxColorG_depth;
    int boxColorB_depth;
    int dpDynamicRange_depth;
    int dpYUVCoef_depth;
    int bck_motion_en_depth;
    int m_axis_video_V_data_V_depth;
    int m_axis_video_V_keep_V_depth;
    int m_axis_video_V_strb_V_depth;
    int m_axis_video_V_user_V_depth;
    int m_axis_video_V_last_V_depth;
    int m_axis_video_V_id_V_depth;
    int m_axis_video_V_dest_V_depth;
    int fid_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};

static void RTLOutputCheckAndReplacement(std::string &AESL_token, std::string PortName) {
  bool no_x = false;
  bool err = false;

  no_x = false;
  // search and replace 'X' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('X', 0);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
  no_x = false;
  // search and replace 'x' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('x', 2);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
}
struct __cosim_sC__ { char data[12]; };
extern "C" void v_tpg_hw_stub_wrapper(volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *);

extern "C" void apatb_v_tpg_hw(volatile void * __xlx_apatb_param_height, volatile void * __xlx_apatb_param_width, volatile void * __xlx_apatb_param_field_id, volatile void * __xlx_apatb_param_fid_in, volatile void * __xlx_apatb_param_bckgndId, volatile void * __xlx_apatb_param_ovrlayId, volatile void * __xlx_apatb_param_maskId, volatile void * __xlx_apatb_param_motionSpeed, volatile void * __xlx_apatb_param_colorFormat, volatile void * __xlx_apatb_param_crossHairX, volatile void * __xlx_apatb_param_crossHairY, volatile void * __xlx_apatb_param_ZplateHorContStart, volatile void * __xlx_apatb_param_ZplateHorContDelta, volatile void * __xlx_apatb_param_ZplateVerContStart, volatile void * __xlx_apatb_param_ZplateVerContDelta, volatile void * __xlx_apatb_param_boxSize, volatile void * __xlx_apatb_param_boxColorR, volatile void * __xlx_apatb_param_boxColorG, volatile void * __xlx_apatb_param_boxColorB, volatile void * __xlx_apatb_param_dpDynamicRange, volatile void * __xlx_apatb_param_dpYUVCoef, volatile void * __xlx_apatb_param_bck_motion_en, volatile void * __xlx_apatb_param_m_axis_video, volatile void * __xlx_apatb_param_fid) {
  refine_signal_handler();
  fstream wrapc_switch_file_token;
  wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
  int AESL_i;
  if (wrapc_switch_file_token.good())
  {

    CodeState = ENTER_WRAPC_PC;
    static unsigned AESL_transaction_pc = 0;
    string AESL_token;
    string AESL_num;{sc_bv<96> xlx_stream_m_axis_video_pc_buffer;
unsigned xlx_stream_m_axis_video_size = 0;

          std::vector<sc_bv<24> > m_axis_video_V_data_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_m_axis_video_V_data_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<24> > m_axis_video_V_data_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "m_axis_video");
  
            // push token into output port buffer
            if (AESL_token != "") {
              m_axis_video_V_data_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_m_axis_video_size=m_axis_video_V_data_V_pc_buffer.size();
m_axis_video_V_data_V_pc_buffer_Copy=m_axis_video_V_data_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<24> > m_axis_video_V_keep_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_m_axis_video_V_keep_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<24> > m_axis_video_V_keep_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "m_axis_video");
  
            // push token into output port buffer
            if (AESL_token != "") {
              m_axis_video_V_keep_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_m_axis_video_size=m_axis_video_V_keep_V_pc_buffer.size();
m_axis_video_V_keep_V_pc_buffer_Copy=m_axis_video_V_keep_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<24> > m_axis_video_V_strb_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_m_axis_video_V_strb_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<24> > m_axis_video_V_strb_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "m_axis_video");
  
            // push token into output port buffer
            if (AESL_token != "") {
              m_axis_video_V_strb_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_m_axis_video_size=m_axis_video_V_strb_V_pc_buffer.size();
m_axis_video_V_strb_V_pc_buffer_Copy=m_axis_video_V_strb_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<24> > m_axis_video_V_user_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_m_axis_video_V_user_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<24> > m_axis_video_V_user_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "m_axis_video");
  
            // push token into output port buffer
            if (AESL_token != "") {
              m_axis_video_V_user_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_m_axis_video_size=m_axis_video_V_user_V_pc_buffer.size();
m_axis_video_V_user_V_pc_buffer_Copy=m_axis_video_V_user_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<24> > m_axis_video_V_last_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_m_axis_video_V_last_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<24> > m_axis_video_V_last_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "m_axis_video");
  
            // push token into output port buffer
            if (AESL_token != "") {
              m_axis_video_V_last_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_m_axis_video_size=m_axis_video_V_last_V_pc_buffer.size();
m_axis_video_V_last_V_pc_buffer_Copy=m_axis_video_V_last_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<24> > m_axis_video_V_id_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_m_axis_video_V_id_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<24> > m_axis_video_V_id_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "m_axis_video");
  
            // push token into output port buffer
            if (AESL_token != "") {
              m_axis_video_V_id_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_m_axis_video_size=m_axis_video_V_id_V_pc_buffer.size();
m_axis_video_V_id_V_pc_buffer_Copy=m_axis_video_V_id_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
          std::vector<sc_bv<24> > m_axis_video_V_dest_V_pc_buffer_Copy;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_m_axis_video_V_dest_V);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<24> > m_axis_video_V_dest_V_pc_buffer;
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "m_axis_video");
  
            // push token into output port buffer
            if (AESL_token != "") {
              m_axis_video_V_dest_V_pc_buffer.push_back(AESL_token.c_str());
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {xlx_stream_m_axis_video_size=m_axis_video_V_dest_V_pc_buffer.size();
m_axis_video_V_dest_V_pc_buffer_Copy=m_axis_video_V_dest_V_pc_buffer;
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  for (int j = 0, e = xlx_stream_m_axis_video_size; j != e; ++j) {
xlx_stream_m_axis_video_pc_buffer.range(31, 0) = m_axis_video_V_data_V_pc_buffer_Copy[j];
xlx_stream_m_axis_video_pc_buffer.range(39, 32) = m_axis_video_V_keep_V_pc_buffer_Copy[j];
xlx_stream_m_axis_video_pc_buffer.range(47, 40) = m_axis_video_V_strb_V_pc_buffer_Copy[j];
xlx_stream_m_axis_video_pc_buffer.range(55, 48) = m_axis_video_V_user_V_pc_buffer_Copy[j];
xlx_stream_m_axis_video_pc_buffer.range(63, 56) = m_axis_video_V_last_V_pc_buffer_Copy[j];
xlx_stream_m_axis_video_pc_buffer.range(71, 64) = m_axis_video_V_id_V_pc_buffer_Copy[j];
xlx_stream_m_axis_video_pc_buffer.range(95, 72) = m_axis_video_V_dest_V_pc_buffer_Copy[j];
__cosim_sC__ xlx_stream_elt;
((long long*)&xlx_stream_elt)[0*1+0] = xlx_stream_m_axis_video_pc_buffer.range(63,0).to_int64();
((long long*)&xlx_stream_elt)[0*1+1] = xlx_stream_m_axis_video_pc_buffer.range(95,64).to_int64();
((hls::stream<__cosim_sC__>*)__xlx_apatb_param_m_axis_video)->write(xlx_stream_elt);
}}{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_fid);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<1> > fid_pc_buffer(1);
          int i = 0;

          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            RTLOutputCheckAndReplacement(AESL_token, "fid");
  
            // push token into output port buffer
            if (AESL_token != "") {
              fid_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (i > 0) {
            ((char*)__xlx_apatb_param_fid)[0] = fid_pc_buffer[0].to_uint64();
          }
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
    AESL_transaction_pc++;
    return ;
  }
static unsigned AESL_transaction;
static AESL_FILE_HANDLER aesl_fh;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
//height
aesl_fh.touch(AUTOTB_TVIN_height);
aesl_fh.touch(AUTOTB_TVOUT_height);
//width
aesl_fh.touch(AUTOTB_TVIN_width);
aesl_fh.touch(AUTOTB_TVOUT_width);
//field_id
aesl_fh.touch(AUTOTB_TVIN_field_id);
aesl_fh.touch(AUTOTB_TVOUT_field_id);
//fid_in
aesl_fh.touch(AUTOTB_TVIN_fid_in);
aesl_fh.touch(AUTOTB_TVOUT_fid_in);
//bckgndId
aesl_fh.touch(AUTOTB_TVIN_bckgndId);
aesl_fh.touch(AUTOTB_TVOUT_bckgndId);
//ovrlayId
aesl_fh.touch(AUTOTB_TVIN_ovrlayId);
aesl_fh.touch(AUTOTB_TVOUT_ovrlayId);
//maskId
aesl_fh.touch(AUTOTB_TVIN_maskId);
aesl_fh.touch(AUTOTB_TVOUT_maskId);
//motionSpeed
aesl_fh.touch(AUTOTB_TVIN_motionSpeed);
aesl_fh.touch(AUTOTB_TVOUT_motionSpeed);
//colorFormat
aesl_fh.touch(AUTOTB_TVIN_colorFormat);
aesl_fh.touch(AUTOTB_TVOUT_colorFormat);
//crossHairX
aesl_fh.touch(AUTOTB_TVIN_crossHairX);
aesl_fh.touch(AUTOTB_TVOUT_crossHairX);
//crossHairY
aesl_fh.touch(AUTOTB_TVIN_crossHairY);
aesl_fh.touch(AUTOTB_TVOUT_crossHairY);
//ZplateHorContStart
aesl_fh.touch(AUTOTB_TVIN_ZplateHorContStart);
aesl_fh.touch(AUTOTB_TVOUT_ZplateHorContStart);
//ZplateHorContDelta
aesl_fh.touch(AUTOTB_TVIN_ZplateHorContDelta);
aesl_fh.touch(AUTOTB_TVOUT_ZplateHorContDelta);
//ZplateVerContStart
aesl_fh.touch(AUTOTB_TVIN_ZplateVerContStart);
aesl_fh.touch(AUTOTB_TVOUT_ZplateVerContStart);
//ZplateVerContDelta
aesl_fh.touch(AUTOTB_TVIN_ZplateVerContDelta);
aesl_fh.touch(AUTOTB_TVOUT_ZplateVerContDelta);
//boxSize
aesl_fh.touch(AUTOTB_TVIN_boxSize);
aesl_fh.touch(AUTOTB_TVOUT_boxSize);
//boxColorR
aesl_fh.touch(AUTOTB_TVIN_boxColorR);
aesl_fh.touch(AUTOTB_TVOUT_boxColorR);
//boxColorG
aesl_fh.touch(AUTOTB_TVIN_boxColorG);
aesl_fh.touch(AUTOTB_TVOUT_boxColorG);
//boxColorB
aesl_fh.touch(AUTOTB_TVIN_boxColorB);
aesl_fh.touch(AUTOTB_TVOUT_boxColorB);
//dpDynamicRange
aesl_fh.touch(AUTOTB_TVIN_dpDynamicRange);
aesl_fh.touch(AUTOTB_TVOUT_dpDynamicRange);
//dpYUVCoef
aesl_fh.touch(AUTOTB_TVIN_dpYUVCoef);
aesl_fh.touch(AUTOTB_TVOUT_dpYUVCoef);
//bck_motion_en
aesl_fh.touch(AUTOTB_TVIN_bck_motion_en);
aesl_fh.touch(AUTOTB_TVOUT_bck_motion_en);
//m_axis_video
aesl_fh.touch(AUTOTB_TVIN_m_axis_video_V_data_V);
aesl_fh.touch(AUTOTB_TVOUT_m_axis_video_V_data_V);
aesl_fh.touch(AUTOTB_TVIN_m_axis_video_V_keep_V);
aesl_fh.touch(AUTOTB_TVOUT_m_axis_video_V_keep_V);
aesl_fh.touch(AUTOTB_TVIN_m_axis_video_V_strb_V);
aesl_fh.touch(AUTOTB_TVOUT_m_axis_video_V_strb_V);
aesl_fh.touch(AUTOTB_TVIN_m_axis_video_V_user_V);
aesl_fh.touch(AUTOTB_TVOUT_m_axis_video_V_user_V);
aesl_fh.touch(AUTOTB_TVIN_m_axis_video_V_last_V);
aesl_fh.touch(AUTOTB_TVOUT_m_axis_video_V_last_V);
aesl_fh.touch(AUTOTB_TVIN_m_axis_video_V_id_V);
aesl_fh.touch(AUTOTB_TVOUT_m_axis_video_V_id_V);
aesl_fh.touch(AUTOTB_TVIN_m_axis_video_V_dest_V);
aesl_fh.touch(AUTOTB_TVOUT_m_axis_video_V_dest_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_data_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_m_axis_video_V_data_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_keep_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_m_axis_video_V_keep_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_strb_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_m_axis_video_V_strb_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_user_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_m_axis_video_V_user_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_last_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_m_axis_video_V_last_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_id_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_m_axis_video_V_id_V);
aesl_fh.touch(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_dest_V);
aesl_fh.touch(WRAPC_STREAM_EGRESS_STATUS_m_axis_video_V_dest_V);
//fid
aesl_fh.touch(AUTOTB_TVIN_fid);
aesl_fh.touch(AUTOTB_TVOUT_fid);
CodeState = DUMP_INPUTS;
// print height Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_height, __xlx_sprintf_buffer.data());
  {
    sc_bv<16> __xlx_tmp_lv = *((short*)__xlx_apatb_param_height);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_height, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.height_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_height, __xlx_sprintf_buffer.data());
}
// print width Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_width, __xlx_sprintf_buffer.data());
  {
    sc_bv<16> __xlx_tmp_lv = *((short*)__xlx_apatb_param_width);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_width, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.width_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_width, __xlx_sprintf_buffer.data());
}
// print field_id Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_field_id, __xlx_sprintf_buffer.data());
  {
    sc_bv<16> __xlx_tmp_lv = *((short*)__xlx_apatb_param_field_id);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_field_id, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.field_id_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_field_id, __xlx_sprintf_buffer.data());
}
// print fid_in Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_fid_in, __xlx_sprintf_buffer.data());
  {
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_fid_in);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_fid_in, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.fid_in_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_fid_in, __xlx_sprintf_buffer.data());
}
// print bckgndId Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_bckgndId, __xlx_sprintf_buffer.data());
  {
    sc_bv<8> __xlx_tmp_lv = *((char*)__xlx_apatb_param_bckgndId);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_bckgndId, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.bckgndId_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_bckgndId, __xlx_sprintf_buffer.data());
}
// print ovrlayId Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_ovrlayId, __xlx_sprintf_buffer.data());
  {
    sc_bv<8> __xlx_tmp_lv = *((char*)__xlx_apatb_param_ovrlayId);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_ovrlayId, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.ovrlayId_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_ovrlayId, __xlx_sprintf_buffer.data());
}
// print maskId Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_maskId, __xlx_sprintf_buffer.data());
  {
    sc_bv<8> __xlx_tmp_lv = *((char*)__xlx_apatb_param_maskId);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_maskId, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.maskId_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_maskId, __xlx_sprintf_buffer.data());
}
// print motionSpeed Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_motionSpeed, __xlx_sprintf_buffer.data());
  {
    sc_bv<8> __xlx_tmp_lv = *((char*)__xlx_apatb_param_motionSpeed);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_motionSpeed, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.motionSpeed_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_motionSpeed, __xlx_sprintf_buffer.data());
}
// print colorFormat Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_colorFormat, __xlx_sprintf_buffer.data());
  {
    sc_bv<8> __xlx_tmp_lv = *((char*)__xlx_apatb_param_colorFormat);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_colorFormat, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.colorFormat_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_colorFormat, __xlx_sprintf_buffer.data());
}
// print crossHairX Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_crossHairX, __xlx_sprintf_buffer.data());
  {
    sc_bv<16> __xlx_tmp_lv = *((short*)__xlx_apatb_param_crossHairX);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_crossHairX, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.crossHairX_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_crossHairX, __xlx_sprintf_buffer.data());
}
// print crossHairY Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_crossHairY, __xlx_sprintf_buffer.data());
  {
    sc_bv<16> __xlx_tmp_lv = *((short*)__xlx_apatb_param_crossHairY);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_crossHairY, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.crossHairY_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_crossHairY, __xlx_sprintf_buffer.data());
}
// print ZplateHorContStart Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_ZplateHorContStart, __xlx_sprintf_buffer.data());
  {
    sc_bv<16> __xlx_tmp_lv = *((short*)__xlx_apatb_param_ZplateHorContStart);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_ZplateHorContStart, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.ZplateHorContStart_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_ZplateHorContStart, __xlx_sprintf_buffer.data());
}
// print ZplateHorContDelta Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_ZplateHorContDelta, __xlx_sprintf_buffer.data());
  {
    sc_bv<16> __xlx_tmp_lv = *((short*)__xlx_apatb_param_ZplateHorContDelta);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_ZplateHorContDelta, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.ZplateHorContDelta_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_ZplateHorContDelta, __xlx_sprintf_buffer.data());
}
// print ZplateVerContStart Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_ZplateVerContStart, __xlx_sprintf_buffer.data());
  {
    sc_bv<16> __xlx_tmp_lv = *((short*)__xlx_apatb_param_ZplateVerContStart);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_ZplateVerContStart, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.ZplateVerContStart_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_ZplateVerContStart, __xlx_sprintf_buffer.data());
}
// print ZplateVerContDelta Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_ZplateVerContDelta, __xlx_sprintf_buffer.data());
  {
    sc_bv<16> __xlx_tmp_lv = *((short*)__xlx_apatb_param_ZplateVerContDelta);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_ZplateVerContDelta, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.ZplateVerContDelta_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_ZplateVerContDelta, __xlx_sprintf_buffer.data());
}
// print boxSize Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_boxSize, __xlx_sprintf_buffer.data());
  {
    sc_bv<16> __xlx_tmp_lv = *((short*)__xlx_apatb_param_boxSize);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_boxSize, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.boxSize_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_boxSize, __xlx_sprintf_buffer.data());
}
// print boxColorR Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_boxColorR, __xlx_sprintf_buffer.data());
  {
    sc_bv<16> __xlx_tmp_lv = *((short*)__xlx_apatb_param_boxColorR);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_boxColorR, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.boxColorR_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_boxColorR, __xlx_sprintf_buffer.data());
}
// print boxColorG Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_boxColorG, __xlx_sprintf_buffer.data());
  {
    sc_bv<16> __xlx_tmp_lv = *((short*)__xlx_apatb_param_boxColorG);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_boxColorG, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.boxColorG_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_boxColorG, __xlx_sprintf_buffer.data());
}
// print boxColorB Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_boxColorB, __xlx_sprintf_buffer.data());
  {
    sc_bv<16> __xlx_tmp_lv = *((short*)__xlx_apatb_param_boxColorB);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_boxColorB, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.boxColorB_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_boxColorB, __xlx_sprintf_buffer.data());
}
// print dpDynamicRange Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_dpDynamicRange, __xlx_sprintf_buffer.data());
  {
    sc_bv<8> __xlx_tmp_lv = *((char*)__xlx_apatb_param_dpDynamicRange);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_dpDynamicRange, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.dpDynamicRange_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_dpDynamicRange, __xlx_sprintf_buffer.data());
}
// print dpYUVCoef Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_dpYUVCoef, __xlx_sprintf_buffer.data());
  {
    sc_bv<8> __xlx_tmp_lv = *((char*)__xlx_apatb_param_dpYUVCoef);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_dpYUVCoef, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.dpYUVCoef_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_dpYUVCoef, __xlx_sprintf_buffer.data());
}
// print bck_motion_en Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_bck_motion_en, __xlx_sprintf_buffer.data());
  {
    sc_bv<16> __xlx_tmp_lv = *((short*)__xlx_apatb_param_bck_motion_en);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_bck_motion_en, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.bck_motion_en_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_bck_motion_en, __xlx_sprintf_buffer.data());
}
std::vector<__cosim_sC__> __xlx_apatb_param_m_axis_video_stream_buf;
long __xlx_apatb_param_m_axis_video_stream_buf_size = ((hls::stream<__cosim_sC__>*)__xlx_apatb_param_m_axis_video)->size();
// print fid Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_fid, __xlx_sprintf_buffer.data());
  {
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_fid);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_fid, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.fid_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_fid, __xlx_sprintf_buffer.data());
}
CodeState = CALL_C_DUT;
v_tpg_hw_stub_wrapper(__xlx_apatb_param_height, __xlx_apatb_param_width, __xlx_apatb_param_field_id, __xlx_apatb_param_fid_in, __xlx_apatb_param_bckgndId, __xlx_apatb_param_ovrlayId, __xlx_apatb_param_maskId, __xlx_apatb_param_motionSpeed, __xlx_apatb_param_colorFormat, __xlx_apatb_param_crossHairX, __xlx_apatb_param_crossHairY, __xlx_apatb_param_ZplateHorContStart, __xlx_apatb_param_ZplateHorContDelta, __xlx_apatb_param_ZplateVerContStart, __xlx_apatb_param_ZplateVerContDelta, __xlx_apatb_param_boxSize, __xlx_apatb_param_boxColorR, __xlx_apatb_param_boxColorG, __xlx_apatb_param_boxColorB, __xlx_apatb_param_dpDynamicRange, __xlx_apatb_param_dpYUVCoef, __xlx_apatb_param_bck_motion_en, __xlx_apatb_param_m_axis_video, __xlx_apatb_param_fid);
CodeState = DUMP_OUTPUTS;

//********************** dump C output stream *******************
long __xlx_apatb_param_m_axis_video_stream_buf_final_size = ((hls::stream<__cosim_sC__>*)__xlx_apatb_param_m_axis_video)->size() - __xlx_apatb_param_m_axis_video_stream_buf_size;
{
  while (!((hls::stream<__cosim_sC__>*)__xlx_apatb_param_m_axis_video)->empty())
    __xlx_apatb_param_m_axis_video_stream_buf.push_back(((hls::stream<__cosim_sC__>*)__xlx_apatb_param_m_axis_video)->read());
  for (int i = 0; i < __xlx_apatb_param_m_axis_video_stream_buf.size(); ++i)
    ((hls::stream<__cosim_sC__>*)__xlx_apatb_param_m_axis_video)->write(__xlx_apatb_param_m_axis_video_stream_buf[i]);
  }

  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_data_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_keep_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_strb_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_user_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_last_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_id_V, __xlx_sprintf_buffer.data());
  
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_dest_V, __xlx_sprintf_buffer.data());
  for (int j = 0, e = __xlx_apatb_param_m_axis_video_stream_buf_final_size; j != e; ++j) {
sc_bv<96> __xlx_tmp_lv;
__xlx_tmp_lv.range(63,0) = ((long long*)&__xlx_apatb_param_m_axis_video_stream_buf[__xlx_apatb_param_m_axis_video_stream_buf_size+j])[0*1+0];
__xlx_tmp_lv.range(95,64) = ((long long*)&__xlx_apatb_param_m_axis_video_stream_buf[__xlx_apatb_param_m_axis_video_stream_buf_size+j])[0*1+1];
sc_bv<24> __xlx_tmp_0_lv = __xlx_tmp_lv.range(23, 0);
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_0_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_data_V, __xlx_sprintf_buffer.data());
sc_bv<8> __xlx_tmp_1_lv = __xlx_tmp_lv.range(39, 32);
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_1_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_keep_V, __xlx_sprintf_buffer.data());
sc_bv<8> __xlx_tmp_2_lv = __xlx_tmp_lv.range(47, 40);
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_2_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_strb_V, __xlx_sprintf_buffer.data());
sc_bv<8> __xlx_tmp_3_lv = __xlx_tmp_lv.range(55, 48);
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_3_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_user_V, __xlx_sprintf_buffer.data());
sc_bv<8> __xlx_tmp_4_lv = __xlx_tmp_lv.range(63, 56);
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_4_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_last_V, __xlx_sprintf_buffer.data());
sc_bv<8> __xlx_tmp_5_lv = __xlx_tmp_lv.range(71, 64);
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_5_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_id_V, __xlx_sprintf_buffer.data());
sc_bv<8> __xlx_tmp_6_lv = __xlx_tmp_lv.range(79, 72);
sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_6_lv.to_string(SC_HEX).c_str());
aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_dest_V, __xlx_sprintf_buffer.data());
}
tcl_file.set_num(__xlx_apatb_param_m_axis_video_stream_buf_final_size, &tcl_file.m_axis_video_V_data_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_data_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_m_axis_video_stream_buf_final_size, &tcl_file.m_axis_video_V_keep_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_keep_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_m_axis_video_stream_buf_final_size, &tcl_file.m_axis_video_V_strb_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_strb_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_m_axis_video_stream_buf_final_size, &tcl_file.m_axis_video_V_user_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_user_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_m_axis_video_stream_buf_final_size, &tcl_file.m_axis_video_V_last_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_last_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_m_axis_video_stream_buf_final_size, &tcl_file.m_axis_video_V_id_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_id_V, __xlx_sprintf_buffer.data());
tcl_file.set_num(__xlx_apatb_param_m_axis_video_stream_buf_final_size, &tcl_file.m_axis_video_V_dest_V_depth);

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_m_axis_video_V_dest_V, __xlx_sprintf_buffer.data());
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_data_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_m_axis_video_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_data_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_data_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_keep_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_m_axis_video_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_keep_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_keep_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_strb_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_m_axis_video_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_strb_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_strb_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_user_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_m_axis_video_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_user_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_user_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_last_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_m_axis_video_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_last_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_last_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_id_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_m_axis_video_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_id_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_id_V, __xlx_sprintf_buffer.data());
}{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_dest_V, __xlx_sprintf_buffer.data());
  sprintf(__xlx_sprintf_buffer.data(), "%d\n", __xlx_apatb_param_m_axis_video_stream_buf_final_size);
 aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_dest_V, __xlx_sprintf_buffer.data());

  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(WRAPC_STREAM_SIZE_OUT_m_axis_video_V_dest_V, __xlx_sprintf_buffer.data());
}// print fid Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVOUT_fid, __xlx_sprintf_buffer.data());
  {
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_fid);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVOUT_fid, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.fid_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVOUT_fid, __xlx_sprintf_buffer.data());
}
CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
