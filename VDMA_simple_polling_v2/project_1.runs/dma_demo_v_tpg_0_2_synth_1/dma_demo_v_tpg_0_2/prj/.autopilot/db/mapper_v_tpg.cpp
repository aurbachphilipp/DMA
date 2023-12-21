#include <systemc>
#include <vector>
#include <iostream>
#include "hls_stream.h"
#include "ap_int.h"
#include "ap_fixed.h"
using namespace std;
using namespace sc_dt;
class AESL_RUNTIME_BC {
  public:
    AESL_RUNTIME_BC(const char* name) {
      file_token.open( name);
      if (!file_token.good()) {
        cout << "Failed to open tv file " << name << endl;
        exit (1);
      }
      file_token >> mName;//[[[runtime]]]
    }
    ~AESL_RUNTIME_BC() {
      file_token.close();
    }
    int read_size () {
      int size = 0;
      file_token >> mName;//[[transaction]]
      file_token >> mName;//transaction number
      file_token >> mName;//pop_size
      size = atoi(mName.c_str());
      file_token >> mName;//[[/transaction]]
      return size;
    }
  public:
    fstream file_token;
    string mName;
};
unsigned int ap_apatb_m_axis_video_V_cap_bc;
static AESL_RUNTIME_BC __xlx_m_axis_video_V_size_Reader("../tv/stream_size/stream_size_out_m_axis_video_V.dat");
struct __cosim_sC__ { char data[12]; };
extern "C" void v_tpg(volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, volatile void *, __cosim_sC__*, volatile void *);
extern "C" void apatb_v_tpg_hw(volatile void * __xlx_apatb_param_height, volatile void * __xlx_apatb_param_width, volatile void * __xlx_apatb_param_field_id, volatile void * __xlx_apatb_param_fid_in, volatile void * __xlx_apatb_param_bckgndId, volatile void * __xlx_apatb_param_ovrlayId, volatile void * __xlx_apatb_param_maskId, volatile void * __xlx_apatb_param_motionSpeed, volatile void * __xlx_apatb_param_colorFormat, volatile void * __xlx_apatb_param_crossHairX, volatile void * __xlx_apatb_param_crossHairY, volatile void * __xlx_apatb_param_ZplateHorContStart, volatile void * __xlx_apatb_param_ZplateHorContDelta, volatile void * __xlx_apatb_param_ZplateVerContStart, volatile void * __xlx_apatb_param_ZplateVerContDelta, volatile void * __xlx_apatb_param_boxSize, volatile void * __xlx_apatb_param_boxColorR, volatile void * __xlx_apatb_param_boxColorG, volatile void * __xlx_apatb_param_boxColorB, volatile void * __xlx_apatb_param_dpDynamicRange, volatile void * __xlx_apatb_param_dpYUVCoef, volatile void * __xlx_apatb_param_bck_motion_en, volatile void * __xlx_apatb_param_m_axis_video, volatile void * __xlx_apatb_param_fid) {
  //Create input buffer for m_axis_video
  ap_apatb_m_axis_video_V_cap_bc = __xlx_m_axis_video_V_size_Reader.read_size();
  __cosim_sC__* __xlx_m_axis_video_input_buffer= new __cosim_sC__[ap_apatb_m_axis_video_V_cap_bc];
  // DUT call
  v_tpg(__xlx_apatb_param_height, __xlx_apatb_param_width, __xlx_apatb_param_field_id, __xlx_apatb_param_fid_in, __xlx_apatb_param_bckgndId, __xlx_apatb_param_ovrlayId, __xlx_apatb_param_maskId, __xlx_apatb_param_motionSpeed, __xlx_apatb_param_colorFormat, __xlx_apatb_param_crossHairX, __xlx_apatb_param_crossHairY, __xlx_apatb_param_ZplateHorContStart, __xlx_apatb_param_ZplateHorContDelta, __xlx_apatb_param_ZplateVerContStart, __xlx_apatb_param_ZplateVerContDelta, __xlx_apatb_param_boxSize, __xlx_apatb_param_boxColorR, __xlx_apatb_param_boxColorG, __xlx_apatb_param_boxColorB, __xlx_apatb_param_dpDynamicRange, __xlx_apatb_param_dpYUVCoef, __xlx_apatb_param_bck_motion_en, __xlx_m_axis_video_input_buffer, __xlx_apatb_param_fid);
  for (unsigned i = 0; i <ap_apatb_m_axis_video_V_cap_bc; ++i)
    ((hls::stream<__cosim_sC__>*)__xlx_apatb_param_m_axis_video)->write(__xlx_m_axis_video_input_buffer[i]);
}
