#ifndef __SYNTHESIS__
#include <stdio.h>
#endif
#include <assert.h>
#include <ap_int.h>
#include "v_tpg_config.h"
#include "v_tpg.h"
#include "v_tpg_zoneplate.h"
#include <utils/x_hls_utils.h>

const U8 rgb = 0;
const U8 yuv444 = 1;
const U8 yuv422 = 2;
const U8 yuv420 = 3;

#define MAX(a,b)	(((a)>(b)) ? (a) : (b))
#define MIN(a,b)	(((a)>(b)) ? (b) : (a))

static void tpgBackground(
#if (ENABLE_AXI4S_SLAVE==1)
                          HSC_STREAM_MULTIPIX& srcImg,
#endif
                          U16 &height,
                          U16 &width,
                          U16 &bck_motion_en,
#if (ENABLE_AXI4S_SLAVE==1)
                          U16 &passthruStartX,
                          U16 &passthruStartY,
                          U16 &passthruEndX,
                          U16 &passthruEndY,
						  U8  &enableInput,
#endif
                          U8  &filterId,
                          U16 &ZplateHorContStart,
                          U16 &ZplateHorContDelta,
                          U16 &ZplateVerContStart,
                          U16 &ZplateVerContDelta,
						  U8  &dpDynamicRange,
						  U8  &dpYUVCoef,
                          U8 &motionSpeed,
                          U8  &colorFormat,
                          HSC_STREAM_MULTIPIX& outImg);

static void tpgForeground(HSC_STREAM_MULTIPIX& srcImg,
                          U16 &height,
                          U16 &width,
                          U8  &filterId,
                          U8  &maskId,
                          U8  &colorFormat,
                          U16 &crossHairX,
                          U16 &crossHairY,
                          U16 &boxSize,
                          U16 &boxColorR,
                          U16 &boxColorG,
                          U16 &boxColorB,
                          U8  &motionSpeed,
                          HSC_STREAM_MULTIPIX& outImg);

static int AXIvideo2MultiPixStream(HSC_AXI_STREAM_IN& AXI_video_strm,
                                   HSC_STREAM_MULTIPIX& img,
								   U8 &enableInput,
                                   U16 &height,
                                   U16 &width,
                                   U8  &colorFormat);

static int MultiPixStream2AXIvideo(HSC_STREAM_MULTIPIX& strm2Pix,
                                   HSC_AXI_STREAM_OUT& AXI_video_strm,
                                   U16 &height,
                                   U16 &width,
                                   U8  &colorFormat,
								   bool &fid_in,
								   bool& fid,
								   U16 &field_id);

#if ((ENABLE_422 == 1) || (ENABLE_420 == 1))
static void v_hcresampler_core(HSC_STREAM_MULTIPIX& srcImg,
                               U16 &height,
                               U16 &width,
                               U8 colorFormat,
                               bool bPassThru,
							   HSC_STREAM_MULTIPIX& outImg);
#endif
#if (ENABLE_420 == 1)
static void v_vcresampler_core(HSC_STREAM_MULTIPIX& srcImg,
                               U16 &height,
                               U16 &width,
                               U8 colorFormat,
                               bool bPassThru,
							   HSC_STREAM_MULTIPIX& outImg);
#endif


YUV_MULTI_PIXEL tpgPatternHorizontalRamp( U16 y, U16 x, U16 rampStart, U8 color);
YUV_MULTI_PIXEL tpgPatternVerticalRamp( U16 y, U16 x, U16 rampStart, U8 color);
YUV_MULTI_PIXEL tpgPatternTemporalRamp( U16 y, U16 x, U16 rampStart, U8 color);
YUV_MULTI_PIXEL tpgPatternSolidRed(U16 x, U8 colorFormat);
YUV_MULTI_PIXEL tpgPatternSolidBlue(U16 x, U8 colorFormat);
YUV_MULTI_PIXEL tpgPatternSolidGreen(U16 x, U8 colorFormat);
YUV_MULTI_PIXEL tpgPatternSolidWhite(U16 x, U8 colorFormat);
YUV_MULTI_PIXEL tpgPatternSolidBlack(U16 x, U8 colorFormat);
YUV_MULTI_PIXEL tpgPatternColorBars(U16 y, U16 x, U16 width, U8 colorFormat, U16 height, U16 bck_motion_en);
YUV_MULTI_PIXEL tpgPatternZonePlate( U16 y, U16 x, U16 rampStart, U16 ZplateHorContStart, U16 ZplateHorContDelta, U16 ZplateVerContStart, U16 ZplateVerContDelta, U8 color);
YUV_MULTI_PIXEL tpgPatternRainbow(U16 y, U16 x, U16 rampStart, U8 colorFormat);
YUV_MULTI_PIXEL tpgPatternTartanColorBars(U16 y, U16 x, U16 width, U16 height, U8 color);
YUV_MULTI_PIXEL tpgPatternCrossHatch(U16 y, U16 x, U16 width, U16 height, U8 color);
YUV_MULTI_PIXEL tpgPatternVerticalHorizontalRamp(U16 y, U16 x, U16 rampStart, U8 color);
YUV_MULTI_PIXEL tpgPatternCheckerBoard(U16 y, U16 x, U16 width, U16 height, U8 color);
YUV_MULTI_PIXEL tpgPRBS(U16 x, U8 color);
YUV_MULTI_PIXEL tpgPatternCrossHair(YUV_MULTI_PIXEL pixIn, U16 y, U16 x, U16 crossHairX, U16 crossHairY, U8 color);
YUV_MULTI_PIXEL tpgPatternBox(YUV_MULTI_PIXEL pixIn, U16 y, U16 x, U16 width, U16 height, U16 boxSize, U16 boxColorR, U16 boxColorG, U16 boxColorB, U16 motionSpeed, U8 color);
YUV_MULTI_PIXEL tpgPatternMask(YUV_MULTI_PIXEL pix,U8 maskId, U8 color);
YUV_MULTI_PIXEL tpgPatternDPColorRamp(U16 y, U16 x, U16 width, U16 height, U8 color, U8 dpDynamicRange, U8 dpYUVCoef);
YUV_MULTI_PIXEL tpgPatternDPBlackWhiteVerticalLine(U16 y, U16 x, U16 width, U16 height, U8 color);
YUV_MULTI_PIXEL tpgPatternDPColorSquare(U16 y, U16 x, U16 width, U16 height, U8 color, U8 dpDynamicRange, U8 dpYUVCoef);

YUV3 tpgBarSelYuv[] = {
    {255<<(BITS_PER_COMPONENT-8), 128<<(BITS_PER_COMPONENT-8), 128<<(BITS_PER_COMPONENT-8)}, // White
    {225<<(BITS_PER_COMPONENT-8),   0<<(BITS_PER_COMPONENT-8), 148<<(BITS_PER_COMPONENT-8)}, // Yellow
    {178<<(BITS_PER_COMPONENT-8), 170<<(BITS_PER_COMPONENT-8),   0<<(BITS_PER_COMPONENT-8)}, // Cyan
    {149<<(BITS_PER_COMPONENT-8),  43<<(BITS_PER_COMPONENT-8),  21<<(BITS_PER_COMPONENT-8)}, // Green
    {105<<(BITS_PER_COMPONENT-8), 212<<(BITS_PER_COMPONENT-8), 234<<(BITS_PER_COMPONENT-8)}, // Magenta
    { 76<<(BITS_PER_COMPONENT-8),  85<<(BITS_PER_COMPONENT-8), 255<<(BITS_PER_COMPONENT-8)}, // Red
    { 29<<(BITS_PER_COMPONENT-8), 255<<(BITS_PER_COMPONENT-8), 107<<(BITS_PER_COMPONENT-8)}, // Blue
    {  0<<(BITS_PER_COMPONENT-8), 128<<(BITS_PER_COMPONENT-8), 128<<(BITS_PER_COMPONENT-8)}  // Black
};

RGB3 tpgBarSelRgb[] = {
    {0xFFFF, 0xFFFF, 0xFFFF}, // White
    {0xFFFF, 0xFFFF, 0x0000}, // Yellow
    {0x0000, 0xFFFF, 0xFFFF}, // Cyan
    {0x0000, 0xFFFF, 0x0000}, // Green
    {0xFFFF, 0x0000, 0xFFFF}, // Magenta
    {0xFFFF, 0x0000, 0x0000}, // Red
    {0x0000, 0x0000, 0xFFFF}, // Blue
    {0x0000, 0x0000, 0x0000}  // Black
};

U8 tpgTartanBarArray[] = {4,2,6,0,7,1,5,3, 2,7,3,1,6,4,0,5, 6,3,0,2,5,7,4,1, 0,1,2,3,4,5,6,7, 7,6,5,4,3,2,1,0, 1,4,7,5,2,0,3,6, 5,0,4,6,1,3,7,2, 3,5,1,7,0,6,2,4};

U8 tpgCheckerBoardArray[] = {0,7,0,7,0,7,0,7,0,7,0,7,0,7,0,7,7,0,7,0,7,0,7,0,7,0,7,0,7,0,7,0};

RGB3 DPtpgBarSelRgb_VESA[] = {
	{0xFFFF, 0xFFFF, 0xFFFF}, // White
	{0xFFFF, 0xFFFF, 0x0000}, // Yellow
	{0x0000, 0xFFFF, 0xFFFF}, // Cyan
	{0x0000, 0xFFFF, 0x0000}, // Green
	{0xFFFF, 0x0000, 0xFFFF}, // Magenta
	{0xFFFF, 0x0000, 0x0000}, // Red
	{0x0000, 0x0000, 0xFFFF}, // Blue
	{0x0000, 0x0000, 0x0000}  // Black
};

RGB3 DPtpgBarSelRgb_CEA[] = {
    {235<<(BITS_PER_COMPONENT-8), 235<<(BITS_PER_COMPONENT-8), 235<<(BITS_PER_COMPONENT-8)}, // White
    {235<<(BITS_PER_COMPONENT-8), 235<<(BITS_PER_COMPONENT-8),  16<<(BITS_PER_COMPONENT-8)}, // Yellow
    { 16<<(BITS_PER_COMPONENT-8), 235<<(BITS_PER_COMPONENT-8), 235<<(BITS_PER_COMPONENT-8)}, // Cyan
    { 16<<(BITS_PER_COMPONENT-8), 235<<(BITS_PER_COMPONENT-8),  16<<(BITS_PER_COMPONENT-8)}, // Green
    {235<<(BITS_PER_COMPONENT-8),  16<<(BITS_PER_COMPONENT-8), 235<<(BITS_PER_COMPONENT-8)}, // Magenta
    {235<<(BITS_PER_COMPONENT-8),  16<<(BITS_PER_COMPONENT-8),  16<<(BITS_PER_COMPONENT-8)}, // Red
    { 16<<(BITS_PER_COMPONENT-8),  16<<(BITS_PER_COMPONENT-8), 235<<(BITS_PER_COMPONENT-8)}, // Blue
    { 16<<(BITS_PER_COMPONENT-8),  16<<(BITS_PER_COMPONENT-8),  16<<(BITS_PER_COMPONENT-8)}  // Black
};

U8 DPtpgBarArray[] = {0,1,2,3,4,5,6,7, 6,5,4,3,2,1,0,7};

#if BITS_PER_COMPONENT==8
YUV3 DPtpgBarSelYuv_601[] = {
    {235, 128, 128}, // White
    {210,  16, 146}, // Yellow
    {170, 166,  16}, // Cyan
    {145,  54,  34}, // Green
    {106, 202, 222}, // Magenta
    { 81,  90, 240}, // Red
    { 41, 240, 110}, // Blue
    { 16, 128, 128}  // Black
};

YUV3 DPtpgBarSelYuv_709[] = {
    {235, 128, 128}, // White
    {219,  16, 138}, // Yellow
    {188, 154,  16}, // Cyan
    {173,  42,  26}, // Green
    { 78, 214, 230}, // Magenta
    { 63, 102, 240}, // Red
    { 32, 240, 118}, // Blue
    { 16, 128, 128}  // Black
};
#endif

#if BITS_PER_COMPONENT==10
YUV3 DPtpgBarSelYuv_601[] = {
    {940, 512, 512}, // White
    {840,  64, 585}, // Yellow
    {678, 663,  64}, // Cyan
    {578, 215, 137}, // Green
    {426, 809, 887}, // Magenta
    {326, 361, 960}, // Red
    {164, 960, 439}, // Blue
    { 64, 512, 512}  // Black
};

YUV3 DPtpgBarSelYuv_709[] = {
    {940, 512, 512}, // White
    {877,  64, 553}, // Yellow
    {753, 614,  64}, // Cyan
    {690, 167, 106}, // Green
    {314, 857, 918}, // Magenta
    {251, 410, 960}, // Red
    {127, 960, 471}, // Blue
    { 64, 512, 512}  // Black
};
#endif

#if BITS_PER_COMPONENT==12
YUV3 DPtpgBarSelYuv_601[] = {
    {3760, 2048, 2048}, // White
    {3360,  256, 2340}, // Yellow
    {2712, 2652,  256}, // Cyan
    {2312,  860,  548}, // Green
    {1704, 3236, 3548}, // Magenta
    {1304, 1444, 3840}, // Red
    { 656, 3840, 1756}, // Blue
    { 256, 2048, 2048}  // Black
};

YUV3 DPtpgBarSelYuv_709[] = {
    {3760, 2048, 2048}, // White
    {3508,  257, 2213}, // Yellow
    {3014, 2458,  257}, // Cyan
    {2761,  667,  422}, // Green
    {1255, 3429, 3674}, // Magenta
    {1002, 1638, 3839}, // Red
    { 508, 3839, 1883}, // Blue
    { 256, 2048, 2048}  // Black
};
#endif

#if BITS_PER_COMPONENT==16
YUV3 DPtpgBarSelYuv_601[] = {
    {60160, 32768, 32768}, // White
    {53769,  4119, 37421}, // Yellow
    {43397, 42411,  4119}, // Cyan
    {37006, 13762,  8773}, // Green
    {27250, 51774, 56763}, // Magenta
    {20859, 23125, 61417}, // Red
    {10487, 61417, 28115}, // Blue
    { 4096, 32768, 32768}  // Black
};

YUV3 DPtpgBarSelYuv_709[] = {
    {60160, 32768, 32768}, // White
    {56123,  4119, 35403}, // Yellow
    {48218, 39327,  4119}, // Cyan
    {44182, 10679,  6754}, // Green
    {20074, 54857, 58782}, // Magenta
    {16038, 26209, 61417}, // Red
    { 8133, 61417, 30133}, // Blue
    { 4096, 32768, 32768}  // Black
};
#endif

/*********************************************************************************
* Function:    hscalar2x
* Parameters:  Stream of input/output pixels, image resolution
* Return:
* Description: Entry point for H Scalar IP
**********************************************************************************/
void v_tpg(
#if (ENABLE_AXI4S_SLAVE==1)
         HSC_AXI_STREAM_IN& s_axis_video,
#endif
         U16 &height,
         U16 &width,
		 U16 &field_id,
		 bool &fid_in,
#if (ENABLE_AXI4S_SLAVE==1)
         U16 &passthruStartX,
         U16 &passthruStartY,
         U16 &passthruEndX,
         U16 &passthruEndY,
		 U8  &enableInput,
#endif
         U8  &bckgndId,
         U8  &ovrlayId,
         U8  &maskId,
         U8  &motionSpeed,
         U8  &colorFormat,
         U16 &crossHairX,
         U16 &crossHairY,
         U16 &ZplateHorContStart,
         U16 &ZplateHorContDelta,
         U16 &ZplateVerContStart,
         U16 &ZplateVerContDelta,
         U16 &boxSize,
         U16 &boxColorR,
         U16 &boxColorG,
         U16 &boxColorB,
		 U8  &dpDynamicRange,
		 U8  &dpYUVCoef,
		 U16 &bck_motion_en,
         HSC_AXI_STREAM_OUT& m_axis_video,
		 bool& fid
         )
{
//#pragma HLS license key=v_tpg
    //Create AXI Streaming Interfaces for the core
__xilinx_ip_top(0);
#if (ENABLE_AXI4S_SLAVE==1)
#pragma HLS INTERFACE axis port=&s_axis_video register
#endif

#pragma HLS INTERFACE axis port=&m_axis_video register

#pragma HLS INTERFACE s_axilite port=&height bundle=CTRL offset=0x10
#pragma HLS INTERFACE s_axilite port=&width bundle=CTRL  offset=0x18

#if (ENABLE_AXI4S_SLAVE==1)
#pragma HLS INTERFACE s_axilite port=&passthruStartX bundle=CTRL offset=0xa0
#pragma HLS INTERFACE s_axilite port=&passthruStartY bundle=CTRL offset=0xa8
#pragma HLS INTERFACE s_axilite port=&passthruEndX bundle=CTRL offset=0xb0
#pragma HLS INTERFACE s_axilite port=&passthruEndY bundle=CTRL offset=0xb8
#pragma HLS INTERFACE s_axilite port=&enableInput bundle=CTRL offset=0x98
#endif

#pragma HLS INTERFACE s_axilite port=&bckgndId bundle=CTRL offset=0x20
#pragma HLS INTERFACE s_axilite port=&ovrlayId bundle=CTRL offset=0x28
#pragma HLS INTERFACE s_axilite port=&maskId bundle=CTRL offset=0x30
#pragma HLS INTERFACE s_axilite port=&motionSpeed bundle=CTRL offset=0x38
#pragma HLS INTERFACE s_axilite port=&colorFormat bundle=CTRL offset=0x40
#pragma HLS INTERFACE s_axilite port=&crossHairX bundle=CTRL offset=0x48
#pragma HLS INTERFACE s_axilite port=&crossHairY bundle=CTRL offset=0x50
#pragma HLS INTERFACE s_axilite port=&ZplateHorContStart bundle=CTRL offset=0x58
#pragma HLS INTERFACE s_axilite port=&ZplateHorContDelta bundle=CTRL offset=0x60
#pragma HLS INTERFACE s_axilite port=&ZplateVerContStart bundle=CTRL offset=0x68
#pragma HLS INTERFACE s_axilite port=&ZplateVerContDelta bundle=CTRL offset=0x70
#pragma HLS INTERFACE s_axilite port=&boxSize bundle=CTRL offset=0x78
#pragma HLS INTERFACE s_axilite port=&boxColorR bundle=CTRL offset=0x80
#pragma HLS INTERFACE s_axilite port=&boxColorG bundle=CTRL offset=0x88
#pragma HLS INTERFACE s_axilite port=&boxColorB bundle=CTRL offset=0x90
#pragma HLS INTERFACE s_axilite port=&dpDynamicRange bundle=CTRL offset=0xc0
#pragma HLS INTERFACE s_axilite port=&dpYUVCoef bundle=CTRL offset=0xc8
#pragma HLS INTERFACE s_axilite port=&field_id bundle=CTRL offset=0xd0
#pragma HLS INTERFACE s_axilite port=&bck_motion_en bundle=CTRL offset=0xd8
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL

#pragma HLS INTERFACE ap_stable port=width
#pragma HLS INTERFACE ap_stable port=height
#pragma HLS INTERFACE ap_stable port=field_id
#pragma HLS INTERFACE ap_stable port=bck_motion_en
#pragma HLS INTERFACE ap_stable port=fid
#pragma HLS INTERFACE ap_stable port=fid_in

#if (ENABLE_AXI4S_SLAVE==1)
#pragma HLS INTERFACE ap_stable port=passthruStartX
#pragma HLS INTERFACE ap_stable port=passthruStartY
#pragma HLS INTERFACE ap_stable port=passthruEndX
#pragma HLS INTERFACE ap_stable port=passthruEndY
#pragma HLS INTERFACE ap_stable port=enableInput
#endif
#pragma HLS INTERFACE ap_stable port=bckgndId
#pragma HLS INTERFACE ap_stable port=ovrlayId
#pragma HLS INTERFACE ap_stable port=maskId
#pragma HLS INTERFACE ap_stable port=motionSpeed
#pragma HLS INTERFACE ap_stable port=colorFormat
#pragma HLS INTERFACE ap_stable port=crossHairX
#pragma HLS INTERFACE ap_stable port=crossHairY
#pragma HLS INTERFACE ap_stable port=ZplateHorContStart
#pragma HLS INTERFACE ap_stable port=ZplateHorContDelta
#pragma HLS INTERFACE ap_stable port=ZplateVerContStart
#pragma HLS INTERFACE ap_stable port=ZplateVerContDelta
#pragma HLS INTERFACE ap_stable port=boxSize
#pragma HLS INTERFACE ap_stable port=boxColorR
#pragma HLS INTERFACE ap_stable port=boxColorG
#pragma HLS INTERFACE ap_stable port=boxColorB

#pragma HLS INTERFACE ap_stable port=dpDynamicRange
#pragma HLS INTERFACE ap_stable port=dpYUVCoef


bool bPassThru = true;


    //assert((height>=10)  && (width>=50));
    //assert((height<=HSC_MAX_HEIGHT) && (width<=HSC_MAX_WIDTH));

    //create local image buffers
#if (ENABLE_AXI4S_SLAVE==1)
    HSC_STREAM_MULTIPIX   srcYUV;
#endif
    HSC_STREAM_MULTIPIX   bckgndYUV;
    HSC_STREAM_MULTIPIX   ovrlayYUV;

    HSC_STREAM_MULTIPIX   stream_out_vresampled, stream_in_vresampled;
    HSC_STREAM_MULTIPIX   stream_out_hresampled, stream_in_hresampled;

    HSC_STREAM_MULTIPIX STRM_V, STRM_H, STRM_UP, STRM_OUT;


#pragma HLS DATAFLOW

#pragma HLS stream variable=bckgndYUV depth=16
#pragma HLS stream variable=ovrlayYUV depth=16

#if (ENABLE_AXI4S_SLAVE==1)
#pragma HLS stream variable=srcYUV depth=16
#endif

#if (ENABLE_AXI4S_SLAVE==1)
    AXIvideo2MultiPixStream(s_axis_video, srcYUV, enableInput, height, width, colorFormat);
#endif

    tpgBackground(
#if (ENABLE_AXI4S_SLAVE==1)
        srcYUV,
#endif
        height,
        width,
		bck_motion_en,
#if (ENABLE_AXI4S_SLAVE==1)
        passthruStartX,
        passthruStartY,
        passthruEndX,
        passthruEndY,
		enableInput,
#endif
        bckgndId,
        ZplateHorContStart,
        ZplateHorContDelta,
        ZplateVerContStart,
        ZplateVerContDelta,
		dpDynamicRange,
		dpYUVCoef,
        motionSpeed,
		colorFormat,
#if ENABLE_FOREGROUND
        bckgndYUV);

    tpgForeground(bckgndYUV,
        height,
        width,
        ovrlayId,
        maskId,
        colorFormat,
        crossHairX,
        crossHairY,
        boxSize,
        boxColorR,
        boxColorG,
        boxColorB,
        motionSpeed,
#endif
        ovrlayYUV);

#if (ENABLE_AXI4S_SLAVE==0)

#if ((ENABLE_422 == 1) || (ENABLE_420 == 1))
    bPassThru = ((colorFormat==color422) || (colorFormat==color420)) ? false : true;
    v_hcresampler_core(ovrlayYUV, height, width, color444, bPassThru, stream_out_hresampled);
#define STRM_H stream_out_hresampled
#else
#define STRM_H ovrlayYUV
#endif

#if (ENABLE_420==1)
    bPassThru = (colorFormat==color420) ? false : true;
    v_vcresampler_core(STRM_H, height, width, color422, bPassThru, stream_out_vresampled);
#define STRM_OUT stream_out_vresampled
#else
  #define STRM_OUT STRM_H
#endif

#endif

#if (ENABLE_AXI4S_SLAVE==1)
#define STRM_OUT ovrlayYUV
#endif

    //convert image to stream
    MultiPixStream2AXIvideo(STRM_OUT, m_axis_video, height, width, colorFormat, fid_in, fid, field_id);

}

/*********************************************************************************
* Function:    hscalar_core
* Parameters:  Stream of input/output pixels, image resolution
* Return:
* Description: Fixed 2x H Scalar
**********************************************************************************/
static void tpgBackground(
#if (ENABLE_AXI4S_SLAVE==1)
                          HSC_STREAM_MULTIPIX& srcImg,
#endif
                          U16 &height,
                          U16 &width,
                          U16 &bck_motion_en,
#if (ENABLE_AXI4S_SLAVE==1)
                          U16 &passthruStartX,
                          U16 &passthruStartY,
                          U16 &passthruEndX,
                          U16 &passthruEndY,
						  U8 &enableInput,
#endif
                          U8  &patternId,
                          U16 &ZplateHorContStart,
                          U16 &ZplateHorContDelta,
                          U16 &ZplateVerContStart,
                          U16 &ZplateVerContDelta,
						  U8  &dpDynamicRange,
						  U8  &dpYUVCoef,
                          U8 &motionSpeed,
                          U8  &colorFormat,
                          HSC_STREAM_MULTIPIX& outImg)
{
    U16 y,x,dy,dx,k,i;
    U16 loopHeight = height;
    U16 loopWidth  = width;
    YUV_MULTI_PIXEL outpix;
    YUV_MULTI_PIXEL pix;

//    colorFormat = 1;

    static U16 rampStart = 0;
    U8 s = 0;

    for(y=0; y<loopHeight; ++y)
    {
             for(x=0; x<loopWidth; x+=SAMPLES_PER_CLOCK)
        {


#pragma HLS LOOP_FLATTEN OFF
#pragma HLS PIPELINE II=1
#if (ENABLE_AXI4S_SLAVE==1)
        	if(enableInput!=0)
        		srcImg >> pix;
#endif
            switch(patternId)
            {
#if (ENABLE_AXI4S_SLAVE==1)
            case 0x0:
                // Passthrough
            	//assert(enableInput!=0);
                outpix = pix;
                break;
#endif
            case 0x1:
                // Horizontal ramp
#if ENABLE_RAMP
                outpix = tpgPatternHorizontalRamp(y, x, rampStart, colorFormat);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            case 0x2:
                // Vertical ramp
#if ENABLE_RAMP
                outpix = tpgPatternVerticalRamp(y, x, rampStart, colorFormat);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            case 0x3:
                // Temporal ramp
#if ENABLE_RAMP
                outpix = tpgPatternTemporalRamp(y, x, rampStart, colorFormat);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            case 0x4:
                // Red
#if ENABLE_SOLID_COLOR
                outpix = tpgPatternSolidRed(x, colorFormat);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            case 0x5:
                // Green
#if ENABLE_SOLID_COLOR
                outpix = tpgPatternSolidGreen(x, colorFormat);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            case 0x6:
                // Blue
#if ENABLE_SOLID_COLOR
                outpix = tpgPatternSolidBlue(x, colorFormat);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            case 0x7:
                // Black
#if ENABLE_SOLID_COLOR
                outpix = tpgPatternSolidBlack(x, colorFormat);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            case 0x8:
                // White
#if ENABLE_SOLID_COLOR
                outpix = tpgPatternSolidWhite(x, colorFormat);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            case 0x9:
                // Color bars
#if ENABLE_COLOR_BAR
                outpix = tpgPatternColorBars(y, x, width, colorFormat, height, bck_motion_en);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            case 0xA:
                // Zone plate
#if ENABLE_ZONE_PLATE
                outpix = tpgPatternZonePlate(y, x, rampStart, ZplateHorContStart, ZplateHorContDelta, ZplateVerContStart, ZplateVerContDelta, colorFormat);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            case 0xB:
                // Tartan color bars
#if ENABLE_COLOR_BAR
                outpix = tpgPatternTartanColorBars(y, x, width, height, colorFormat);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            case 0xC:
                // Cross hatch
#if ENABLE_COLOR_BAR
                outpix = tpgPatternCrossHatch(y, x, width, height, colorFormat);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            case 0xD:
                // ColorSweep
#if ENABLE_COLOR_SWEEP
                outpix = tpgPatternRainbow(y, x, rampStart, colorFormat);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            case 0xE:
                // Vertical and horizontal ramp
#if ENABLE_RAMP
                outpix = tpgPatternVerticalHorizontalRamp(y, x, rampStart, colorFormat);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            case 0xF:
                // Checker board
#if ENABLE_COLOR_BAR
                outpix = tpgPatternCheckerBoard(y, x, width, height, colorFormat);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            case 0x10:
            	outpix = tpgPRBS(x, colorFormat);
            	break;
            case 0x11:
#if ENABLE_DISPLAY_PORT
            	outpix = tpgPatternDPColorRamp(y, x, width, height, colorFormat, dpDynamicRange, dpYUVCoef);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
            	break;
            case 0x12:
#if ENABLE_DISPLAY_PORT
                outpix = tpgPatternDPBlackWhiteVerticalLine(y, x, width, height, colorFormat);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            case 0x13:
#if ENABLE_DISPLAY_PORT
                outpix = tpgPatternDPColorSquare(y, x, width, height, colorFormat, dpDynamicRange, dpYUVCoef);
#else
				outpix = tpgPatternSolidBlack(x, colorFormat);
#endif
                break;
            default:
                //outpix = pix;
            	break;
            }
#if (ENABLE_AXI4S_SLAVE==1)
            // Passthrough window, only valid in case of slave interface
            if(enableInput != 0)
			{
				for (int k = 0; k < SAMPLES_PER_CLOCK; k++){
					if ((x+k)>=passthruStartX && y>=passthruStartY && (x+k)<passthruEndX && y<passthruEndY)
					{
						outpix.val[0+k*NR_COMPONENTS] = pix.val[0+k*NR_COMPONENTS];
						outpix.val[1+k*NR_COMPONENTS] = pix.val[1+k*NR_COMPONENTS];
						if (NR_COMPONENTS==3) outpix.val[2+k*NR_COMPONENTS] = pix.val[2+k*NR_COMPONENTS];
					}
				}
			}
#endif
            outImg << outpix;
        }
    }
    rampStart = (rampStart + motionSpeed) & ((1 << BITS_PER_COMPONENT) -1);
}

/*********************************************************************************
* Function:    hscalar_core
* Parameters:  Stream of input/output pixels, image resolution
* Return:
* Description: Fixed 2x H Scalar
**********************************************************************************/
static void tpgForeground(HSC_STREAM_MULTIPIX& srcImg,
                          U16 &height,
                          U16 &width,
                          U8  &patternId,
                          U8  &maskId,
                          U8  &colorFormat,
                          U16 &crossHairX,
                          U16 &crossHairY,
                          U16 &boxSize,
                          U16 &boxColorR,
                          U16 &boxColorG,
                          U16 &boxColorB,
                          U8  &motionSpeed,
                          HSC_STREAM_MULTIPIX& outImg)
{
    U16 y,x,dy,dx,k,i;
    U16 loopHeight = height;
    U16 loopWidth  = width;
    static U16 rampStart = 0;

    YUV_MULTI_PIXEL outpix;
	YUV_MULTI_PIXEL intpix;
    YUV_MULTI_PIXEL pix;

    for(y=0; y<loopHeight; ++y)
    {
        for(x=0; x<loopWidth; x+=SAMPLES_PER_CLOCK)
        {
#pragma HLS LOOP_FLATTEN OFF
#pragma HLS PIPELINE II=1
            srcImg >> pix;

            switch(patternId)
            {
            case 0x0:
                // Passthrough
                intpix = pix;
                break;
            case 0x1:
                // Box
                intpix = tpgPatternBox(pix, y, x, width, height, boxSize, boxColorR, boxColorG, boxColorB, motionSpeed, colorFormat);
                break;
            case 0x2:
                // Crosshair
                intpix = tpgPatternCrossHair(pix, y, x, crossHairX, crossHairY, colorFormat);
                break;
            default:
				// Passthrough
				intpix = pix;
				break;
            }

            if (maskId)
            {
            	outpix = tpgPatternMask(intpix,maskId,colorFormat);
            }
			else
				outpix = intpix;

            outImg << outpix;
        }
    }
}

/*********************************************************************************
* Function:    AXIvideo2MultiPixStream
* Parameters:  Double Pixel AXI Stream, User Stream, Image Resolution
* Return:      None
* Description: Read data from 2pixel/clk AXI stream into user defined stream
*              (temporary function until official hls:video library is updated
*               to provide the required functionality)
**********************************************************************************/
int AXIvideo2MultiPixStream(HSC_AXI_STREAM_IN& AXI_video_strm,
                            HSC_STREAM_MULTIPIX& img,
							U8 &enableInput,
                            U16 &Height,
                            U16 &WidthIn,
                            U8  &colorFormat
                            )
{
    int res = 0;
    ap_axiu<BITS_PER_CLOCK, 1, 1, 1> axi;
    YUV_MULTI_PIXEL pix;
    int rows         = reg(Height);
    int cols         = reg(WidthIn);
    assert(rows <= MAX_HEIGHT);
    assert(cols <= MAX_WIDTH);
    int depth = BITS_PER_COMPONENT;
    bool sof = 0;

	if(enableInput != 0)
	{
loop_wait_for_start:
		while (!sof)
		{
#pragma HLS pipeline II=1
#pragma HLS loop_tripcount avg=0 max=0
			AXI_video_strm >> axi;
			sof = axi.user.to_int();
		}
	loop_height:
		for (int i = 0; i < rows; i++)
		{

			bool eol = 0;
	loop_width:
			for (int j = 0; j < cols/SAMPLES_PER_CLOCK; j++)
			{
#pragma HLS loop_flatten off
#pragma HLS pipeline II=1
				if (sof || eol)
				{
					sof = 0;
					eol = axi.last.to_int();
				}
				else
				{
					AXI_video_strm >> axi;
					eol = axi.last.to_int();
				}
				if (eol && (j != (cols/SAMPLES_PER_CLOCK)-1))
				{
					// will work only for integral values of image width to samplesperclk
					res |= ERROR_IO_EOL_EARLY;
				}
				for (int l = 0; l < SAMPLES_PER_CLOCK; l++)
				{
					for (int k = 0; k < NR_COMPONENTS; k++)
					{
						ap_uint<BITS_PER_COMPONENT> pix_rgb, pix_444, pix_422;
						const int map[3] = {2, 0, 1};
#pragma HLS ARRAY_PARTITION variable=&map complete dim=0
						hls::AXIGetBitFields(axi, (map[k] + l * 3) * depth, depth, pix_rgb);
						hls::AXIGetBitFields(axi, (k + l * 3) * depth, depth, pix_444);
						hls::AXIGetBitFields(axi, (k + l * 2) * depth, depth, pix_422);
						switch(colorFormat)
						{
						case 0:
							pix.val[k + l * NR_COMPONENTS] = pix_rgb;
							break;
						case 1:
							pix.val[k + l * NR_COMPONENTS] = pix_444;
							break;
						default:
							pix.val[k + l * NR_COMPONENTS] = pix_422;
							break;
						}
					}
				}
				img << pix;
			}
	loop_wait_for_eol:
			while (!eol)
			{
#pragma HLS pipeline II=1
#pragma HLS loop_tripcount avg=0 max=0
				// Keep reading until we get to EOL
				AXI_video_strm >> axi;
				eol = axi.last.to_int();
				res |= ERROR_IO_EOL_LATE;
			}
		}
	}
    return res;
}

/*********************************************************************************
* Function:    MultiPixStream2AXIvideo
* Parameters:  Multi Pixel Stream, AXI Video Stream, Image Resolution
* Return:      None
* Description: Convert a 4pixel/clk stream to AXI Video
*              (temporary function until official hls:video library is updated
*               to provide the required functionality)
**********************************************************************************/
int MultiPixStream2AXIvideo(HSC_STREAM_MULTIPIX& strmPix,
                            HSC_AXI_STREAM_OUT& AXI_video_strm,
                            U16 &Height,
                            U16 &WidthOut,
                            U8 &colorFormat,
							bool &fid_in,
							bool& fid,
							U16 &field_id)
{
    int res = 0;
    YUV_MULTI_PIXEL pix;
	ap_uint<BITS_PER_COMPONENT> pix_rgb, pix_444, pix_422;
    ap_axiu<(BITS_PER_CLOCK), 1, 1, 1> axi;
    int depth = BITS_PER_COMPONENT;
#if 0
    int rows = reg(Height);
    int cols = reg(WidthOut);
#else
    int rows = Height;
    int cols = WidthOut;
#endif
    assert(rows <= MAX_HEIGHT);
    assert(cols <= MAX_WIDTH);
    static U16 counter = 0;

#if (SAMPLES_PER_CLOCK == 1)
    const ap_uint<5> mapComp[4][3] =  {
                                        {1,  2,  0},     //RGB
                                        {0,  1,  2},     //4:4:4
                                        {0,  1,  2},     //4:2:2
                                        {0,  1,  2}     //4:2:0
                                        };
#endif
#if (SAMPLES_PER_CLOCK == 2)
    const ap_uint<5> mapComp[4][6] =  {
                                        {1,  2,  0,  4,  5,  3},     //RGB
                                        {0,  1,  2,  3,  4,  5},     //4:4:4
                                        {0,  1,  3,  4,  5,  2},     //4:2:2
                                        {0,  1,  3,  4,  5,  2}     //4:2:0
                                        };
#endif
#if (SAMPLES_PER_CLOCK == 4)
    const ap_uint<5> mapComp[4][12] =  {
                                        {1,  2,  0,  4,  5,  3,  7,  8,  6, 10, 11,  9},     //RGB
                                        {0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11},     //4:4:4
                                        {0,  1,  3,  4,  6,  7,  9, 10, 11,  8,  5,  2},     //4:2:2
                                        {0,  1,  3,  4,  6,  7,  9, 10, 11,  8,  5,  2}     //4:2:0
                                        };
#endif
#if (SAMPLES_PER_CLOCK == 8)
    const ap_uint<5> mapComp[4][24] =  {
                                        {1,  2,  0,  4,  5,  3,  7,  8,  6, 10, 11,  9, 13, 14, 12, 16, 17, 15, 19, 20, 18, 22, 23, 21},     //RGB
                                        {0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23},     //4:4:4
                                        {0,  1,  3,  4,  6,  7,  9, 10, 12, 13, 15, 16, 18, 19, 21, 22, 23, 20, 17, 14, 11,  8,  5,  2},     //4:2:2
                                        {0,  1,  3,  4,  6,  7,  9, 10, 12, 13, 15, 16, 18, 19, 21, 22, 23, 20, 17, 14, 11,  8,  5,  2}     //4:2:0
                                        };
#endif

    bool sof = 1;
    bool eof = 1;
    bool fid_toggle = 1;
    //fid = 0;

    for (int i = 0; i < rows; i++)
    {



        for (int j = 0; j < cols/SAMPLES_PER_CLOCK; j++)
        {
#pragma HLS loop_flatten off
#pragma HLS pipeline II=1




            if (sof)
            {
                axi.user = 1;
                sof = 0;
            }
            else
            {
                axi.user = 0;
            }
            if (j == (cols/SAMPLES_PER_CLOCK-1))
            {
                axi.last = 1;
            }
            else
            {
                axi.last = 0;
            }

            if(axi.user)
            {
             counter ++;
            }

            strmPix >> pix;
            axi.data = -1;

            for (int l = 0; l < SAMPLES_PER_CLOCK; l++)
            {
                for (int k = 0; k < NR_COMPONENTS; k++)
                {
                    int start = (k + l * NR_COMPONENTS) * depth;
                    //axi.data(start + depth - 1, start) = pix.val[kMap];
                    pix_rgb = pix.val[mapComp[0][k + l * NR_COMPONENTS]];
                    pix_444 = pix.val[mapComp[1][k + l * NR_COMPONENTS]];
                    pix_422 = pix.val[mapComp[2][k + l * NR_COMPONENTS]];
                    switch(colorFormat)
                    {
                    case 0x0:
                      axi.data(start + depth - 1, start) = pix_rgb;
                      break;
                    case 0x1:
                      axi.data(start + depth - 1, start) = pix_444;
                      break;
                    default:
                      axi.data(start + depth - 1, start) = pix_422;
                    }
                }
            }
            axi.keep = -1;

            AXI_video_strm << axi;
             fid_toggle = (counter )& 0x1;
            // fid = fid_toggle;

            // fid_toggle = (counter )& 0x1;
           /* switch(field_id)
        	 {
        	 case 0x0:
        		 fid = 0;
        		 break;
        	 case 0x1:
        		 fid =  fid_toggle;
        		 break;
        	 case 0x2:
        		 fid = 1;
        		 break;
        	 case 0x3:
        		 =!(fid_toggle);
        		 fid = fid_toggle;
        		 break;
        	 case 0x4:
        		 fid = fid_in;
        		 break;
        	 default:
        		 fid = 0;
        	 }*/

                if (field_id == 0)
                {
        		 fid = 0;
                 }
                else if(field_id == 1)
                 {
        		 fid =  fid_toggle;

                 }
                else if (field_id == 2)
                {
        		 fid = 1;
                 }
                else if(field_id == 3)
                 {
        		 fid_toggle =!(fid_toggle);
        		 fid = fid_toggle;
                 }
                else if (field_id == 4)
                {
        		 fid = fid_in;
                 }
                else
                {
                         fid = 0;
                }




    }
 }
                      return res;

}

YUV_MULTI_PIXEL tpgPatternHorizontalRamp( U16 y, U16 x, U16 rampStart, U8 color)
{

    static U16 rampVal = 0;
    YUV_MULTI_PIXEL pix;

	if (x==0)
		rampVal = rampStart;

	for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
	{
		pix.val[0+k*NR_COMPONENTS] = rampVal;
		pix.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? rampVal : 128<<(BITS_PER_COMPONENT-8);
		if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = (color==colorRgb) ? rampVal : 128<<(BITS_PER_COMPONENT-8);

		rampVal = (rampVal + 1) & ((1<<BITS_PER_COMPONENT)-1);
	}

    return pix;
}

YUV_MULTI_PIXEL tpgPatternVerticalRamp( U16 y, U16 x, U16 rampStart, U8 color)
{

    static U16 rampVal = 0;
    YUV_MULTI_PIXEL pix;

    if ((x==0) && (y==0))
    {
        rampVal = rampStart;
    }
    else if (x==0)
    {
        rampVal = (rampVal + 1) & ((1<<BITS_PER_COMPONENT)-1);
    }
    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
        pix.val[0+k*NR_COMPONENTS] = rampVal;
        pix.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? rampVal : 128<<(BITS_PER_COMPONENT-8);
        if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = (color==colorRgb) ? rampVal : 128<<(BITS_PER_COMPONENT-8);
    }
    return pix;
}

YUV_MULTI_PIXEL tpgPatternTemporalRamp( U16 y, U16 x, U16 rampStart, U8 color)
{

    YUV_MULTI_PIXEL pix;
    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
        pix.val[0+k*NR_COMPONENTS] = rampStart;
        pix.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? rampStart : 128<<(BITS_PER_COMPONENT-8);
        if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = (color==colorRgb) ? rampStart : 128<<(BITS_PER_COMPONENT-8);
    }
    return pix;
}

YUV_MULTI_PIXEL tpgPatternSolidRed(U16 x, U8 color)
{

    YUV_MULTI_PIXEL pix;
    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
        const U16 redRgb[] = {0xFFFF, 0x0000, 0x0000};
        const U16 redYuv[] = {0x4c<<(BITS_PER_COMPONENT-8), 0x55<<(BITS_PER_COMPONENT-8), 0xff<<(BITS_PER_COMPONENT-8)};

        pix.val[0+k*NR_COMPONENTS] = (color==colorRgb) ? redRgb[0] : redYuv[0] ;
        pix.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? redRgb[1] : redYuv[1+((color==color444) ? 0 : ((x+k)&1))] ;
        if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = (color==colorRgb) ? redRgb[2] : redYuv[2] ;
    }
    return pix;
}

YUV_MULTI_PIXEL tpgPatternSolidGreen(U16 x, U8 color)
{

    YUV_MULTI_PIXEL pix;
    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
        const U16 grnRgb[] = {0x0000, 0xffff, 0x0000};
        const U16 grnYuv[] = {0x95<<(BITS_PER_COMPONENT-8), 0x2b<<(BITS_PER_COMPONENT-8), 0x15<<(BITS_PER_COMPONENT-8)};

        pix.val[0+k*NR_COMPONENTS] = (color==colorRgb) ? grnRgb[0] : grnYuv[0] ;
        pix.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? grnRgb[1] : grnYuv[1+((color==color444) ? 0 : ((x+k)&1))] ;
        if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = (color==colorRgb) ? grnRgb[2] : grnYuv[2] ;
    }
    return pix;
}

YUV_MULTI_PIXEL tpgPatternSolidBlue(U16 x, U8 color)
{

    YUV_MULTI_PIXEL pix;
    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
        const U16 bluRgb[] = {0x0000, 0x0000, 0xffff};
        const U16 bluYuv[] = {0x1d<<(BITS_PER_COMPONENT-8), 0xff<<(BITS_PER_COMPONENT-8), 0x6b<<(BITS_PER_COMPONENT-8)};

        pix.val[0+k*NR_COMPONENTS] = (color==colorRgb) ? bluRgb[0] : bluYuv[0] ;
        pix.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? bluRgb[1] : bluYuv[1+((color==color444) ? 0 : ((x+k)&1))] ;
        if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = (color==colorRgb) ? bluRgb[2] : bluYuv[2] ;
    }
    return pix;
}

YUV_MULTI_PIXEL tpgPatternSolidBlack(U16 x, U8 color)
{

    YUV_MULTI_PIXEL pix;
    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
        const U16 blkRgb[] = {0x0000, 0x0000, 0x0000};
        const U16 blkYuv[] = {0x00<<(BITS_PER_COMPONENT-8), 0x80<<(BITS_PER_COMPONENT-8), 0x80<<(BITS_PER_COMPONENT-8)};

        pix.val[0+k*NR_COMPONENTS] = (color==colorRgb) ? blkRgb[0] : blkYuv[0] ;
        pix.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? blkRgb[1] : blkYuv[1+((color==color444) ? 0 : ((x+k)&1))] ;
        if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = (color==colorRgb) ? blkRgb[2] : blkYuv[2] ;
    }
    return pix;
}

YUV_MULTI_PIXEL tpgPatternSolidWhite(U16 x, U8 color)
{

    YUV_MULTI_PIXEL pix;
    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
        const U16 whiRgb[] = {0xffff, 0xffff, 0xffff};
        const U16 whiYuv[] = {0xffff, 0x80<<(BITS_PER_COMPONENT-8), 0x80<<(BITS_PER_COMPONENT-8)};

        pix.val[0+k*NR_COMPONENTS] = (color==colorRgb) ? whiRgb[0] : whiYuv[0] ;
        pix.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? whiRgb[1] : whiYuv[1+((color==color444) ? 0 : ((x+k)&1))] ;
        if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = (color==colorRgb) ? whiRgb[2] : whiYuv[2] ;
    }
    return pix;
}

YUV_MULTI_PIXEL tpgPatternColorBars(U16 y, U16 x, U16 width, U8 color, U16 height, U16 bck_motion_en)
{

    YUV_MULTI_PIXEL pix;
    static int s = 0;
    if (reg(bck_motion_en) == 0x0) {
    	s = 0;
    }
    static int count = 0;
    static U8 hBarSel[SAMPLES_PER_CLOCK] = {s};
    static ap_uint<11> xBar[SAMPLES_PER_CLOCK] = {0};

    ap_uint<11> barWidth = ((width+7) / NUM_BARS);

    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
        if (x == 0)
        {
            hBarSel[k] = s;
            xBar[k] = k;
        }
        else if ((xBar[k] + SAMPLES_PER_CLOCK)< barWidth)
        {
            xBar[k] = xBar[k] + SAMPLES_PER_CLOCK;
        }
        else
        {
            xBar[k] = xBar[k] + SAMPLES_PER_CLOCK - barWidth;
            hBarSel[k] = (hBarSel[k] + 1) % NUM_BARS;
        }

        pix.val[0+k*NR_COMPONENTS] = (color==colorRgb) ? tpgBarSelRgb[hBarSel[k]].r : tpgBarSelYuv[hBarSel[k]].y ;
        pix.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? tpgBarSelRgb[hBarSel[k]].g : ((color==color444 || (color!=color444 && !((x+k)&1))) ? tpgBarSelYuv[hBarSel[k]].u : tpgBarSelYuv[hBarSel[k]].v);
        if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = (color==colorRgb) ? tpgBarSelRgb[hBarSel[k]].b : tpgBarSelYuv[hBarSel[k]].v ;
    }

    if (reg(bck_motion_en) == 0x1)
    {
    	if (x == 0 && y == 0)
    	{
    		count++;

    		if (s < NUM_BARS )
    		{
    			if (count==10)
    			{
    				s = reg(s + 1);
    				count = 0;
    			}
    		}
    		else {
    			s = 0;
    		}
    	}
    }

    return pix;
}

YUV_MULTI_PIXEL tpgPatternRainbow(U16 y, U16 x, U16 rampStart, U8 color)
{

    YUV_MULTI_PIXEL pix;

    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
        U16 xk = x+k;
        U16 r = MIN((1<<BITS_PER_COMPONENT-1) + (tpgSinTableArray_9bit[(xk)%2048]<<(BITS_PER_COMPONENT-8)), (1<<BITS_PER_COMPONENT)-1);
        U16 g = MIN((1<<BITS_PER_COMPONENT-1) + (tpgSinTableArray_9bit[(xk+682)%2048]<<(BITS_PER_COMPONENT-8)), (1<<BITS_PER_COMPONENT)-1);
        U16 b = MIN((1<<BITS_PER_COMPONENT-1) + (tpgSinTableArray_9bit[(xk+2*682)%2048]<<(BITS_PER_COMPONENT-8)), (1<<BITS_PER_COMPONENT)-1);

        if (color!=colorRgb)
        {
#if 1
            /*  { 77,   150,    29,     4224},  */
            /*  {-43,   -85,    128,    32896}, */
            /*  {128,   -107,   -21,    32896}  */
            int yn = (int)(((16  << (BITS_PER_COMPONENT - 8)) + 0.5f) * 256 + 0.5f); //4224 for  8-bit
            int un = (int)(((128 << (BITS_PER_COMPONENT - 8)) + 0.5f) * 256 + 0.5f); //32896 for 8-bit
            int vn = (int)(((128 << (BITS_PER_COMPONENT - 8)) + 0.5f) * 256 + 0.5f); //32896 for 8-bit

            int y = ( (  77 * r + 150 * g +  29 * b + yn) >> 8);
            int u = ( ( -43 * r -  85 * g + 128 * b + un) >> 8);
            int v = ( ( 128 * r - 107 * g -  21 * b + vn) >> 8);
            r = MAX(MIN(y, (1<<BITS_PER_COMPONENT)-1), 0);
            g = MAX(MIN(u, (1<<BITS_PER_COMPONENT)-1), 0);
            b = MAX(MIN(v, (1<<BITS_PER_COMPONENT)-1), 0);
#else
            int rg = r - g;
            int bg = b - g;
            int acoef = (int)((0.2568f)*(1<<16));
            int bcoef = (int)((0.0979f)*(1<<16));
            int ccoef = (int)((0.5910f)*(1<<16));
            int dcoef = (int)((0.5772f)*(1<<16));
            int y = (((rg*acoef) + (bg*bcoef))>>16)+g;
            int cb = dcoef*(b-y);
            int cr = ccoef*(r-y);
            y = (y) + 16;
            r = y;
            g = ((cb>>16) + (1<<(BITS_PER_COMPONENT-1)));
            b = ((cr>>16) + (1<<(BITS_PER_COMPONENT-1)));
#endif
        }
        pix.val[0+k*NR_COMPONENTS] = r;
        pix.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? g : ((color==color444 || (color!=color444 && !((xk)&1))) ? g : b);
        if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = b;
    }
    return pix;
}


YUV_MULTI_PIXEL tpgPatternZonePlate(U16 y, U16 x, U16 rampStart, U16 Zplate_Hor_Control_Start, U16 Zplate_Hor_Control_Delta, U16 Zplate_Ver_Control_Start, U16 Zplate_Ver_Control_Delta, U8 color)
{


    static U16 zonePlateVAddr;
    static U16 zonePlateVDelta;
    static U16 zonePlateHAddr;
    static U16 zonePlateHDelta;

    int zonePlateSinVal;
    YUV_MULTI_PIXEL pix;
    if (x==0 && y==0){
        zonePlateVAddr = rampStart<<8;
        zonePlateVDelta = Zplate_Ver_Control_Start;
        zonePlateHAddr = rampStart<<8;
        zonePlateHDelta = Zplate_Hor_Control_Start;
    }
    else if (x==0 && y>0)
    {
        zonePlateHDelta = Zplate_Hor_Control_Start;

        zonePlateVAddr += zonePlateVDelta;

        zonePlateVDelta += Zplate_Ver_Control_Delta;
    }

    zonePlateHDelta = x*Zplate_Hor_Control_Start + reg((x*(x-1))>>1)*Zplate_Hor_Control_Delta;

    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
		zonePlateHAddr = (U16)(zonePlateVAddr + zonePlateHDelta + k*Zplate_Hor_Control_Start + ((k*((x<<1)+k-1))>>1)*Zplate_Hor_Control_Delta);

    	zonePlateSinVal = 144 + (tpgSinTableArray[zonePlateHAddr >> 5] * ((1 << ZONEPLATE_WIDTH) - 35) / ((1 << (19-ZONEPLATE_WIDTH)) * (1 << ZONEPLATE_WIDTH)));

        // Same values for RGB & YCbCr
        pix.val[0+k*NR_COMPONENTS] = (U8) (zonePlateSinVal);
        pix.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? (U8) (zonePlateSinVal) : 128<<(BITS_PER_COMPONENT-8);
        if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = (color==colorRgb) ? (U8) (zonePlateSinVal) : 128<<(BITS_PER_COMPONENT-8);
    }
    return pix;
}

YUV_MULTI_PIXEL tpgPatternTartanColorBars(U16 y, U16 x, U16 width, U16 height, U8 color)
{

    YUV_MULTI_PIXEL pix;
    ap_uint<10> barWidth = ((width+15) >> 4);
    ap_uint<10> barWidthMinSamples = ((width+15) >> 4) - SAMPLES_PER_CLOCK;
    ap_uint<10> barHeight = ((height+15) >> 4);
    static U8 hBarSel[SAMPLES_PER_CLOCK];
    static U8 vBarSel = 0;
    static ap_uint<10> yCount;
    static ap_uint<10> xCount[SAMPLES_PER_CLOCK];
    U16 tBarSel = 0;

    if ((y==0) && (x==0))
    {
        yCount = 0;
        vBarSel = 0;
    }
    else if ((yCount<barHeight-1) && (x==0))
    {
        yCount++;
    }
    else if (x == 0)
    {
        yCount = 0;
        vBarSel = (vBarSel + 1) % NUM_BARS;
    }

    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {

        YUV_PIXEL pixTartan;
        if (x == 0)
        {
            hBarSel[k] = 0;
            xCount[k] = k;
        }
        else if (xCount[k] < barWidthMinSamples)
        {
            xCount[k] += SAMPLES_PER_CLOCK;
        }
        else
        {
            xCount[k] -= barWidthMinSamples;
            hBarSel[k] = (hBarSel[k] + 1) % NUM_BARS;
        }

        tBarSel = (vBarSel << 3) | hBarSel[k];

        pix.val[0+k*NR_COMPONENTS] = (color==colorRgb) ? tpgBarSelRgb[tpgTartanBarArray[tBarSel]].r : tpgBarSelYuv[tpgTartanBarArray[tBarSel]].y;
        pix.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? tpgBarSelRgb[tpgTartanBarArray[tBarSel]].g : ((color==color444 || (color!=color444 && !((x+k)&1))) ? tpgBarSelYuv[tpgTartanBarArray[tBarSel]].u : tpgBarSelYuv[tpgTartanBarArray[tBarSel]].v);
        if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = (color==colorRgb) ? tpgBarSelRgb[tpgTartanBarArray[tBarSel]].b : tpgBarSelYuv[tpgTartanBarArray[tBarSel]].v;
    }

    return pix;
}

YUV_MULTI_PIXEL tpgPatternCrossHatch(U16 y, U16 x, U16 width, U16 height, U8 color)
{

    YUV_MULTI_PIXEL pix;
    ap_uint<10> barWidth = ((width+15) >> 4);
    ap_uint<10> barWidthMinSamples = ((width+15) >> 4) - SAMPLES_PER_CLOCK;
    ap_uint<10> barWidthMinSamples_delayed=reg<ap_uint<10> >(barWidthMinSamples);
    ap_uint<10> barHeight = ((height+15) >> 4);
    static bool vHatch;
    bool hHatch = false;
    static ap_uint<10> yCount;
    static ap_uint<10> xCount[SAMPLES_PER_CLOCK];

    if (((y==0)||(y==height-1)) && (x==0))
    {
        yCount = 0;
        vHatch = true;
    }
    else if ((yCount==barHeight-1) && (x==0))
    {
    	yCount = 0;
    	vHatch = true;
    }
    else if (x == 0)
    {
    	yCount++;
    	vHatch = false;
    }

    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {

        if (x == 0)
        {
            hHatch = (k == 0);
            xCount[k] = k;
        }
        else if ((x+k) == width-1)
        {
        	hHatch = 1;
        	xCount[k] = k;
        }
        else if (xCount[k] < barWidthMinSamples_delayed)
        {
            xCount[k] += SAMPLES_PER_CLOCK;
            hHatch = false;
        }
        else if (xCount[k] == barWidthMinSamples_delayed)
        {
        	xCount[k] = 0;
        	hHatch = true;
        }
        else
        {
            xCount[k] -= barWidthMinSamples_delayed;
            hHatch = false;
        }

        if (vHatch || hHatch)
        {
            const U16 whiRgb[] = {0xffff, 0xffff, 0xffff};
            const U16 whiYuv[] = {0xffff, 0x80<<(BITS_PER_COMPONENT-8), 0x80<<(BITS_PER_COMPONENT-8)};

            pix.val[0+k*NR_COMPONENTS] = (color==colorRgb) ? whiRgb[0] : whiYuv[0] ;
            pix.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? whiRgb[1] : whiYuv[1+((color==color444) ? 0 : ((x+k)&1))] ;
            if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = (color==colorRgb) ? whiRgb[2] : whiYuv[2] ;
        }
        else
        {
            const U16 blkRgb[] = {0x0000, 0x0000, 0x0000};
            const U16 blkYuv[] = {0x00<<(BITS_PER_COMPONENT-8), 0x80<<(BITS_PER_COMPONENT-8), 0x80<<(BITS_PER_COMPONENT-8)};

            pix.val[0+k*NR_COMPONENTS] = (color==colorRgb) ? blkRgb[0] : blkYuv[0] ;
            pix.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? blkRgb[1] : blkYuv[1+((color==color444) ? 0 : ((x+k)&1))] ;
            if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = (color==colorRgb) ? blkRgb[2] : blkYuv[2] ;
        }
    }
    return pix;
}

YUV_MULTI_PIXEL tpgPatternVerticalHorizontalRamp(U16 y, U16 x, U16 rampStart, U8 color)
{

    static U16 hdata = 0;
    YUV_MULTI_PIXEL pix;

    if (x == 0)
        hdata = (rampStart + y) & ((1<<BITS_PER_COMPONENT)-1);

    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
        // Same values for RGB & YCbCr
        pix.val[0+k*NR_COMPONENTS] = hdata;
        pix.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? hdata : 128<<(BITS_PER_COMPONENT-8);
        if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = (color==colorRgb) ? hdata : 128<<(BITS_PER_COMPONENT-8);

        hdata = (hdata + 1) & ((1<<BITS_PER_COMPONENT)-1);
    }

    return pix;
}

YUV_MULTI_PIXEL tpgPatternCheckerBoard(U16 y, U16 x, U16 width, U16 height, U8 color)
{

    YUV_MULTI_PIXEL pix;
    ap_uint<10> barWidth = ((width+15) >> 4);
    ap_uint<10> barWidthMinSamples = ((width+15) >> 4) - SAMPLES_PER_CLOCK;
    ap_uint<10> barHeight = ((height+15) >> 4);
    static U8 hBarSel[SAMPLES_PER_CLOCK];
    static U8 vBarSel = 0;
    static ap_uint<10> yCount = 0;
    static ap_uint<10> xCount[SAMPLES_PER_CLOCK];
    U8 tBarSel = 0;

    if ((y==0) && (x==0))
    {
        yCount = 0;
        vBarSel = 0;
    }
    else if ((yCount<barHeight-1) && (x==0))
    {
        yCount++;
    }
    else if (x == 0)
    {
        yCount = 0;
        vBarSel++;
    }

    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {

        if (x == 0)
        {
            hBarSel[k] = 0;
            xCount[k] = k;
        }
        else if (xCount[k] < barWidthMinSamples)
        {
            xCount[k] += SAMPLES_PER_CLOCK;
        }
        else
        {
            xCount[k] -= barWidthMinSamples;
            hBarSel[k] = (hBarSel[k] + 1) % NUM_BARS;
        }

        tBarSel = ((vBarSel & 0x1) << 4) | hBarSel[k];

        pix.val[0+k*NR_COMPONENTS] = (color==colorRgb) ? tpgBarSelRgb[tpgCheckerBoardArray[tBarSel]].r : tpgBarSelYuv[tpgCheckerBoardArray[tBarSel]].y;
        pix.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? tpgBarSelRgb[tpgCheckerBoardArray[tBarSel]].g : ((color==color444 || (color!=color444 && !((x+k)&1))) ? tpgBarSelYuv[tpgCheckerBoardArray[tBarSel]].u : tpgBarSelYuv[tpgCheckerBoardArray[tBarSel]].v);
        if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = (color==colorRgb) ? tpgBarSelRgb[tpgCheckerBoardArray[tBarSel]].b : tpgBarSelYuv[tpgCheckerBoardArray[tBarSel]].v;
    }

    return pix;
}

YUV_MULTI_PIXEL tpgPatternDPColorRamp(U16 y, U16 x, U16 width, U16 height, U8 color, U8 dpDynamicRange, U8 dpYUVCoef)
{

    YUV_MULTI_PIXEL tmp,pix;
    U16 Sel = 0;
    static U16 rampVal = 0;
    U16 colorSel = 0;
    U16 fineCourseSel = 0;

#if BITS_PER_COMPONENT==8
    //calculate ramp value
	if(x%256==0)
		rampVal=0;

	//assign ramp value to PIXEL
	Sel = (y>>6)%4;

	for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
	{
		switch(Sel)
		{
		case 0x0:
			tmp.val[0+k*NR_COMPONENTS] = rampVal;
			tmp.val[1+k*NR_COMPONENTS] = 0;
			tmp.val[2+k*NR_COMPONENTS] = 0;
			break;
		case 0x1:
			tmp.val[0+k*NR_COMPONENTS] = 0;
			tmp.val[1+k*NR_COMPONENTS] = rampVal;
			tmp.val[2+k*NR_COMPONENTS] = 0;
			break;
		case 0x2:
			tmp.val[0+k*NR_COMPONENTS] = 0;
			tmp.val[1+k*NR_COMPONENTS] = 0;
			tmp.val[2+k*NR_COMPONENTS] = rampVal;
			break;
		default:
			tmp.val[0+k*NR_COMPONENTS] = rampVal;
			tmp.val[1+k*NR_COMPONENTS] = rampVal;
			tmp.val[2+k*NR_COMPONENTS] = rampVal;
		}
		pix.val[0+k*NR_COMPONENTS] = tmp.val[0+k*NR_COMPONENTS];
		pix.val[1+k*NR_COMPONENTS] = (color<=color444 || (color>color444 && !((x+k)&1)))?tmp.val[1+k*NR_COMPONENTS]:tmp.val[2+k*NR_COMPONENTS];
		pix.val[2+k*NR_COMPONENTS] = tmp.val[2+k*NR_COMPONENTS];
		rampVal=rampVal+1;
	}

#else
		Sel = (y>>5)%8;
		fineCourseSel = Sel%2;
		colorSel = Sel>>1;

	    //calculate ramp value
		if(fineCourseSel==0){
			if(x%256==0)
				rampVal=0x180<<(BITS_PER_COMPONENT-10);
		}
		else{
			if(x%256==0)
				rampVal=0;
		}

		for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
		{
			switch(colorSel)
			{
			case 0x0:
				tmp.val[0+k*NR_COMPONENTS] = rampVal;
				tmp.val[1+k*NR_COMPONENTS] = 0;
				tmp.val[2+k*NR_COMPONENTS] = 0;
				break;
			case 0x1:
				tmp.val[0+k*NR_COMPONENTS] = 0;
				tmp.val[1+k*NR_COMPONENTS] = rampVal;
				tmp.val[2+k*NR_COMPONENTS] = 0;
				break;
			case 0x2:
				tmp.val[0+k*NR_COMPONENTS] = 0;
				tmp.val[1+k*NR_COMPONENTS] = 0;
				tmp.val[2+k*NR_COMPONENTS] = rampVal;
				break;
			default:
				tmp.val[0+k*NR_COMPONENTS] = rampVal;
				tmp.val[1+k*NR_COMPONENTS] = rampVal;
				tmp.val[2+k*NR_COMPONENTS] = rampVal;
			}
			pix.val[0+k*NR_COMPONENTS] = tmp.val[0+k*NR_COMPONENTS];
			pix.val[1+k*NR_COMPONENTS] = (color<=color444 || (color>color444 && !((x+k)&1)))?tmp.val[1+k*NR_COMPONENTS]:tmp.val[2+k*NR_COMPONENTS];
			pix.val[2+k*NR_COMPONENTS] = tmp.val[2+k*NR_COMPONENTS];
			if(fineCourseSel==0)
				rampVal=rampVal+1;
			else
				rampVal=rampVal+(4<<(BITS_PER_COMPONENT-10));
		}
#endif
    return pix;
}

YUV_MULTI_PIXEL tpgPatternDPBlackWhiteVerticalLine(U16 y, U16 x, U16 width, U16 height, U8 color)
{

    YUV_MULTI_PIXEL pix;
    const U16 black = 0x0000;
    const U16 white = 0xffff;

    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
        pix.val[0+k*NR_COMPONENTS] = ((x+k)&1)?white:black;
        pix.val[1+k*NR_COMPONENTS] = ((x+k)&1)?white:black;
        pix.val[2+k*NR_COMPONENTS] = ((x+k)&1)?white:black;
    }

    return pix;
}

YUV_MULTI_PIXEL tpgPatternDPColorSquare(U16 y, U16 x, U16 width, U16 height, U8 color, U8 dpDynamicRange, U8 dpYUVCoef)
{

    YUV_MULTI_PIXEL pix;
    ap_uint<10> barWidth = 64;
    ap_uint<10> barWidthMinSamples = 64 - SAMPLES_PER_CLOCK;
    ap_uint<10> barHeight = 64;
    static U8 hBarSel[SAMPLES_PER_CLOCK];
    static U8 vBarSel = 0;
    static ap_uint<10> yCount;
    static ap_uint<10> xCount[SAMPLES_PER_CLOCK];
    U16 tBarSel = 0;

    if ((y==0) && (x==0))
    {
        yCount = 0;
        vBarSel = 0;
    }
    else if ((yCount<barHeight-1) && (x==0))
    {
        yCount++;
    }
    else if (x == 0)
    {
        yCount = 0;
        vBarSel = (vBarSel + 1) % 2;
    }

    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
        if (x == 0)
        {
            hBarSel[k] = 0;
            xCount[k] = k;
        }
        else if (xCount[k] < barWidthMinSamples)
        {
            xCount[k] += SAMPLES_PER_CLOCK;
        }
        else
        {
            xCount[k] -= barWidthMinSamples;
            hBarSel[k] = (hBarSel[k] + 1) % 8;
        }

        tBarSel = (vBarSel << 3) | hBarSel[k];

        if(color==colorRgb){
        	if(dpDynamicRange==0){
        		pix.val[0+k*NR_COMPONENTS] = DPtpgBarSelRgb_VESA[DPtpgBarArray[tBarSel]].r;
        		pix.val[1+k*NR_COMPONENTS] = DPtpgBarSelRgb_VESA[DPtpgBarArray[tBarSel]].g;
        		pix.val[2+k*NR_COMPONENTS] = DPtpgBarSelRgb_VESA[DPtpgBarArray[tBarSel]].b;
        	}
        	else{
        		pix.val[0+k*NR_COMPONENTS] = DPtpgBarSelRgb_CEA[DPtpgBarArray[tBarSel]].r;
        		pix.val[1+k*NR_COMPONENTS] = DPtpgBarSelRgb_CEA[DPtpgBarArray[tBarSel]].g;
        		pix.val[2+k*NR_COMPONENTS] = DPtpgBarSelRgb_CEA[DPtpgBarArray[tBarSel]].b;
        	}
        }
        else{
        	if(dpYUVCoef==0){
        		pix.val[0+k*NR_COMPONENTS] = DPtpgBarSelYuv_601[DPtpgBarArray[tBarSel]].y;
        		pix.val[1+k*NR_COMPONENTS] = (color==color444 || (color!=color444 && !((x+k)&1))) ? DPtpgBarSelYuv_601[DPtpgBarArray[tBarSel]].u:DPtpgBarSelYuv_601[DPtpgBarArray[tBarSel]].v;
        		if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = DPtpgBarSelYuv_601[DPtpgBarArray[tBarSel]].v;
        	}
        	else{
        		pix.val[0+k*NR_COMPONENTS] = DPtpgBarSelYuv_709[DPtpgBarArray[tBarSel]].y;
        		pix.val[1+k*NR_COMPONENTS] = (color==color444 || (color!=color444 && !((x+k)&1))) ? DPtpgBarSelYuv_709[DPtpgBarArray[tBarSel]].u:DPtpgBarSelYuv_709[DPtpgBarArray[tBarSel]].v;
        		if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = DPtpgBarSelYuv_709[DPtpgBarArray[tBarSel]].v;
        	}
        }
    }

    return pix;
}

YUV_MULTI_PIXEL tpgPRBS(U16 x, U8 color)
{

    YUV_MULTI_PIXEL pix;
    static ap_uint<28> rSerie = 0x5a5a5a5;
    static ap_uint<28> gSerie = 0xaa55aa5;
    static ap_uint<28> bSerie = 0x00ff00f;
    ap_uint<28> newBit_r, newBit_g, newBit_b;
    ap_uint<28> lfsr_r, lfsr_g, lfsr_b;
    ap_uint<28> r_y,g_u,b_v;


    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
    	//red component
		lfsr_r = rSerie;
		//feedback polynomial taps: 28,25
		newBit_r  = ((lfsr_r >> 0) ^ (lfsr_r >> 3)) & 1;
		lfsr_r =  (lfsr_r >> 1) | (newBit_r << 27);
		rSerie = lfsr_r;

		//green component
		lfsr_g = gSerie;
		//feedback polynomial taps: 28,25
		newBit_g  = ((lfsr_g >> 0) ^ (lfsr_g >> 3)) & 1;
		lfsr_g =  (lfsr_g >> 1) | (newBit_g << 27);
		gSerie = lfsr_g;

		//blue component
		lfsr_b = bSerie;
		//feedback polynomial taps: 28,25
		newBit_b  = ((lfsr_b >> 0) ^ (lfsr_b >> 3)) & 1;
		lfsr_b =  (lfsr_b >> 1) | (newBit_b << 27);
		bSerie = lfsr_b;

        r_y = (rSerie >> (28-BITS_PER_COMPONENT));
        g_u = (gSerie >> (28-BITS_PER_COMPONENT));
        b_v = (bSerie >> (28-BITS_PER_COMPONENT));

        pix.val[0+k*NR_COMPONENTS] = r_y;
        pix.val[1+k*NR_COMPONENTS] = (color<=color444 || (color>color444 && !((x+k)&1))) ? g_u : b_v;
        if (NR_COMPONENTS==3) pix.val[2+k*NR_COMPONENTS] = b_v;
    }
    return pix;
}

YUV_MULTI_PIXEL tpgPatternBox(YUV_MULTI_PIXEL pixIn, U16 y, U16 x, U16 width, U16 height, U16 boxSize, U16 boxColorR, U16 boxColorG, U16 boxColorB, U16 motionSpeed, U8 color)
{

    YUV_MULTI_PIXEL pixOut = pixIn;
    U16 boxLeft, boxRight, boxTop, boxBottom;
    bool vBoxEn=0, hBoxEn=0;
    static U16 boxVCoord = 0;
    static U16 boxHCoord = 0;
    static bool hDir = false;
    static bool vDir = false;
    static bool hDirPrev = false;
    static bool vDirPrev = false;
    U16 hMax = width - boxSize;
    U16 vMax = height - boxSize;

    if (x == 0 && y == 0)
    {
        //  Determine motion in horizontal direction
        if (hDir == false)
        {
            if (boxHCoord > hMax)
                hDir = true;
        }
        else {
            if (boxHCoord < (motionSpeed << 1))
                hDir = false;
        }

        // Determine motion in the vertical direction
        if (vDir == false) {
            if (boxVCoord > vMax)
                vDir = true;
        }
        else {
            if (boxVCoord < (motionSpeed << 1))
                vDir = false;
        }

        // Move top left edge pixel of box when motion is enabled
        if (hDir == false)
            boxHCoord = boxHCoord + motionSpeed;
        else
            boxHCoord = boxHCoord - motionSpeed;
        if (vDir == false)
            boxVCoord = boxVCoord + motionSpeed;
        else
            boxVCoord = boxVCoord - motionSpeed;

        //hDirPrev = hDir;
        //vDirPrev = vDir;
    }

    // Calculate box edges
    boxLeft = boxHCoord;
    boxRight = boxHCoord + boxSize;
    boxTop = boxVCoord;
    boxBottom = boxVCoord + boxSize;

    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
        if (y >= boxTop && y < boxBottom)
            vBoxEn = true;
        else
            vBoxEn = false;

        if ((x+k) >= boxLeft && (x+k) < boxRight)
            hBoxEn = true;
        else
            hBoxEn = false;

        if (vBoxEn && hBoxEn)
        {
            // TODO add registers for box color
            pixOut.val[0+k*NR_COMPONENTS] = boxColorR;
            pixOut.val[1+k*NR_COMPONENTS] = (color<=color444 || (color>color444 && !((x+k)&1))) ? boxColorG : boxColorB;
            if (NR_COMPONENTS==3) pixOut.val[2+k*NR_COMPONENTS] = boxColorB;
        }
    }
    return pixOut;
}

YUV_MULTI_PIXEL tpgPatternCrossHair(YUV_MULTI_PIXEL pixIn, U16 y, U16 x, U16 crossHairX, U16 crossHairY, U8 color)
{

    YUV_MULTI_PIXEL pixOut = pixIn;

    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
        if ((y == crossHairY) || ((x+k) == crossHairX))
        {
            const U16 whiRgb[] = {0xf0<<(BITS_PER_COMPONENT-8), 0xf0<<(BITS_PER_COMPONENT-8), 0xf0<<(BITS_PER_COMPONENT-8)};
            const U16 whiYuv[] = {0xf0<<(BITS_PER_COMPONENT-8), 0x80<<(BITS_PER_COMPONENT-8), 0x80<<(BITS_PER_COMPONENT-8)};

            pixOut.val[0+k*NR_COMPONENTS] = (color==colorRgb) ? whiRgb[0] : whiYuv[0] ;
            pixOut.val[1+k*NR_COMPONENTS] = (color==colorRgb) ? whiRgb[1] : whiYuv[1+((color==color444) ? 0 : ((x+k)&1))] ;
            if (NR_COMPONENTS==3) pixOut.val[2+k*NR_COMPONENTS] = (color==colorRgb) ? whiRgb[2] : whiYuv[2] ;
        }
    }
    return pixOut;
}

YUV_MULTI_PIXEL tpgPatternMask(YUV_MULTI_PIXEL pix, U8 maskId, U8 color)
{

    YUV_MULTI_PIXEL pixOut;
    pixOut = pix;
    for (int k = 0; k < SAMPLES_PER_CLOCK; k++)
    {
    	if ((maskId&1)&(color==colorRgb))
    		pixOut.val[0+k*NR_COMPONENTS] = 0x0000 ;
    	if (((maskId>>1)&1)&(color==colorRgb))
    	    pixOut.val[1+k*NR_COMPONENTS] = 0x0000 ;
    	if (((maskId>>2)&1)&(color==colorRgb))
    	    pixOut.val[2+k*NR_COMPONENTS] = 0x0000 ;
    }
    return pixOut;
}

#if ((ENABLE_422 == 1) || (ENABLE_420 == 1))

#define KERNEL_H_SIZE   4

static void v_hcresampler_core(HSC_STREAM_MULTIPIX& srcImg,
                               U16 &height,
                               U16 &width,
                               U8 colorMode,
                               bool bPassThru,
							   HSC_STREAM_MULTIPIX& outImg)
{
    I16 y,x,k;
    I16 CRpix, first_pix, last_pix, chroma_out_pix, odd_col;
    I16 center_tap;
    I16 shift;
    I16 yOffset = 0;
    I16 xOffset; //offset between streaming pixel and processing pixel
    I16 loopHeight= height + yOffset;
    I16 loopWidth;
    I16 out_y, out_x;

    YUV_MULTI_PIXEL inpix;
    YUV_MULTI_PIXEL outpix;
    Y_MULTI_PIXEL mpix_y;
    C_MULTI_PIXEL mpix_cb, mpix_cr;

    const U8 PIXBUF_C_DEPTH = (((((((KERNEL_H_SIZE/2)+1)+SAMPLES_PER_CLOCK-1)+(SAMPLES_PER_CLOCK-1))/SAMPLES_PER_CLOCK)*SAMPLES_PER_CLOCK)+(KERNEL_H_SIZE/2)-1);
    const U8 PIXBUF_Y_DEPTH = ((PIXBUF_C_DEPTH-((KERNEL_H_SIZE/2)-1))*2);

    Y_PIXEL pixbuf_y[PIXBUF_Y_DEPTH];
    C_PIXEL pixbuf_cb[PIXBUF_C_DEPTH], pixbuf_cr[PIXBUF_C_DEPTH];

    if (bPassThru)
    {
        xOffset = 0;
        center_tap = 0;
    }
    else if (colorMode == color422)
    {
        xOffset = ((PIXBUF_Y_DEPTH/SAMPLES_PER_CLOCK)-1);
        center_tap = 0;
    }
    else
    {
        xOffset = ((PIXBUF_C_DEPTH-(KERNEL_H_SIZE/2))/SAMPLES_PER_CLOCK);
        center_tap = (PIXBUF_Y_DEPTH-((xOffset+1)*SAMPLES_PER_CLOCK));
    }

    loopWidth = (width/SAMPLES_PER_CLOCK) + xOffset;

    for(y=0; y<loopHeight; ++y)
    {

        for(x=0; x<loopWidth; ++x)
        {

#pragma HLS LOOP_FLATTEN OFF
#pragma HLS PIPELINE II=1

            //processing (output) pixel coordinates
            out_y = y;
            out_x = x - xOffset;

            if (x < (width/SAMPLES_PER_CLOCK))
            {
                srcImg >> inpix;

                // create multi-pixel samples of luma only or chroma only
                for (I16 s=0; s<SAMPLES_PER_CLOCK; ++s)
                {
                    mpix_y.val[s]  = inpix.val[s*3];
                    if (colorMode == color444)
                    {
                        mpix_cb.val[s] = inpix.val[s*3+1];
                        mpix_cr.val[s] = inpix.val[s*3+2];
                    }
                    else
                    {
                        if (((x*SAMPLES_PER_CLOCK)+s) & 1)
                        {
                            mpix_cr.val[s/2] = inpix.val[s*3+1];
                        }
                        else
                        {
                            mpix_cb.val[s/2] = inpix.val[s*3+1];
                        }
                    }
                }
            }
            //luma pixel buffer
#pragma HLS ARRAY_PARTITION variable=&pixbuf_y      complete dim=0
            //shift right by SAMPLES_PER_CLOCK to make space for next SAMPLES_PER_CLOCK inputs at top
            for(I16 i=0 ; i<(PIXBUF_Y_DEPTH-SAMPLES_PER_CLOCK); i++)
            {
                pixbuf_y[i] = pixbuf_y[i+SAMPLES_PER_CLOCK];
            }
            //push read pixels at FIFO top
            for(k=0; k<SAMPLES_PER_CLOCK; k++)
            {
                pixbuf_y[PIXBUF_Y_DEPTH-1-k].val[0] = mpix_y.val[SAMPLES_PER_CLOCK-1-k];
            }

            //chroma pixel buffer
#pragma HLS ARRAY_PARTITION variable=&pixbuf_cb      complete dim=0
#pragma HLS ARRAY_PARTITION variable=&pixbuf_cr      complete dim=0

#if (SAMPLES_PER_CLOCK == 1)
            shift = 1;
#else
            shift = (colorMode == color444) ? 1 : 2;
#endif

            //push read pixels at FIFO top
            for(k=0; k<SAMPLES_PER_CLOCK; k++)
            {

#if (SAMPLES_PER_CLOCK == 1)
                first_pix = (colorMode == color444) ? (x==0) : (x==1);
                CRpix = (colorMode == color444) ? 1 : (x & 1);
#else
                first_pix = (colorMode == color444) ? (x==0) : ((x==0) && (k==1));
                CRpix = (colorMode == color444) ? 1 : (k & 1);
#endif

                if (CRpix == 1) // work with Cb/Cr pairs
                {
                    //shift right to make space for next input at top
                    for(I16 i=0 ; i<(PIXBUF_C_DEPTH-1); i++)
                    {
                        pixbuf_cb[i] = pixbuf_cb[i+1];
                        pixbuf_cr[i] = pixbuf_cr[i+1];
                    }
                    if (x < (width/SAMPLES_PER_CLOCK))
                    {
                        pixbuf_cb[PIXBUF_C_DEPTH-1].val[0] = mpix_cb.val[k/shift];
                        pixbuf_cr[PIXBUF_C_DEPTH-1].val[0] = mpix_cr.val[k/shift];
                    }
                    else //right edge padding
                    {
                        pixbuf_cb[PIXBUF_C_DEPTH-1].val[0] = mpix_cb.val[(SAMPLES_PER_CLOCK/shift)-1];
                        pixbuf_cr[PIXBUF_C_DEPTH-1].val[0] = mpix_cr.val[(SAMPLES_PER_CLOCK/shift)-1];
                    }
                }
                //left edge padding
                if (first_pix==1)
                {
                    for(I16 i=(PIXBUF_C_DEPTH-SAMPLES_PER_CLOCK); i>=0; --i)
                    {
                        pixbuf_cb[i].val[0] = mpix_cb.val[0];
                        pixbuf_cr[i].val[0] = mpix_cr.val[0];
                    }
                }
            }

            for(k=0; k<SAMPLES_PER_CLOCK; ++k)
            {

#if (SAMPLES_PER_CLOCK == 1)
                odd_col = (out_x & 1);
                chroma_out_pix = (colorMode == color422) ? 1 : !(out_x & 1);
#else
                odd_col = (k & 1);
                chroma_out_pix = (colorMode == color422) ? 1 : !(k & 1);
#endif

                long filt_res0, filt_res1;
                if (colorMode == color444)
                {
                    // 444 to 422 fixed coef filtering [ 1/4 1/2 1/4 ]
                    // luma component
                    outpix.val[k*3] = pixbuf_y[center_tap+k].val[0];

                    if(chroma_out_pix == 1)
                    {
                        // filter
                        filt_res0 = (pixbuf_cb[0+((k/2)*2)].val[0] + 2*pixbuf_cb[1+((k/2)*2)].val[0] + pixbuf_cb[2+((k/2)*2)].val[0] + 2) / 4;
                        filt_res1 = (pixbuf_cr[0+((k/2)*2)].val[0] + 2*pixbuf_cr[1+((k/2)*2)].val[0] + pixbuf_cr[2+((k/2)*2)].val[0] + 2) / 4;
                    }
                    outpix.val[k*3+1] = (odd_col) ? filt_res1 : filt_res0;
                    outpix.val[k*3+2] =  0;
                }
                else
                {
                    // 422 to 444 fixed coef filtering [ 1/2 1/2 ]
                    // luma component
                    outpix.val[k*3] = pixbuf_y[center_tap+k].val[0];
                    if (odd_col) // odd cols (1, 3, 5, etc)
                    {
                        //interpolate by averaging nearest neighbors
                        outpix.val[k*3+1] = (pixbuf_cb[2+(k/2)].val[0] + pixbuf_cb[1+(k/2)].val[0] + 1) / 2;
                        outpix.val[k*3+2] = (pixbuf_cr[2+(k/2)].val[0] + pixbuf_cr[1+(k/2)].val[0] + 1) / 2;
                    }
                    else // even cols (0, 2, 4, etc)
                    {
                        // passthru co-sited pixel
                        outpix.val[k*3+1] = pixbuf_cb[1+(k/2)].val[0];
                        outpix.val[k*3+2] = pixbuf_cr[1+(k/2)].val[0];
                    }
                }

            }

            if((out_y>=0) && (out_x>=0))
            {
                outImg << ((bPassThru) ? inpix : outpix);
            }
        }
    }
}
#endif

#if (ENABLE_420 == 1)

#define KERNEL_V_SIZE   3
#define CHROMA_LINES    3
#define LUMA_LINES      2

typedef hls::Scalar<1, PIXEL_TYPE> Y_PIXEL;
typedef hls::Scalar<SAMPLES_PER_CLOCK, PIXEL_TYPE>  Y_MULTI_PIXEL;
typedef hls::Scalar<1, PIXEL_TYPE> C_PIXEL;
typedef hls::Scalar<SAMPLES_PER_CLOCK, PIXEL_TYPE>  C_MULTI_PIXEL;

typedef hls::LineBuffer<LUMA_LINES,   (MAX_WIDTH/SAMPLES_PER_CLOCK), Y_MEM_PIXEL_TYPE>    LINE_BUFFER_Y;
typedef hls::LineBuffer<CHROMA_LINES, (MAX_WIDTH/SAMPLES_PER_CLOCK), C_MEM_PIXEL_TYPE>    LINE_BUFFER_C;

void v_vcresampler_core(HSC_STREAM_MULTIPIX& srcImg,
                        U16 &height,
                        U16 &width,
                        U8 colorMode,
                        bool bPassThru,
						HSC_STREAM_MULTIPIX& outImg)
{
    I16 y,x,k;
    I16 yOffset; //offset between streaming row and processing row
    I16 xOffset = 0;
    I16 loopHeight;
    I16 loopWidth = (width/SAMPLES_PER_CLOCK) + xOffset;
    I16 out_y, out_x;
    I16 ChromaLine;

    LINE_BUFFER_Y linebuf_y;
    LINE_BUFFER_C linebuf_c;

    YUV_MULTI_PIXEL pix;
    YUV_MULTI_PIXEL outpix;
    Y_MULTI_PIXEL mpix_y;
    C_MULTI_PIXEL mpix_c;
    //local storage for line buffer column (to avoid multiple read clients on BRAM)
    Y_MULTI_PIXEL pixbuf_y[LUMA_LINES+1];
    C_MULTI_PIXEL pixbuf_c[KERNEL_V_SIZE];
    Y_MEM_PIXEL_TYPE InYPix;
    C_MEM_PIXEL_TYPE InCPix;

#if (USE_URAM == 1)
#pragma HLS RESOURCE variable=&linebuf_y core=XPM_MEMORY uram
#pragma HLS RESOURCE variable=&linebuf_c core=XPM_MEMORY uram
#endif

    if (bPassThru)
    {
        yOffset = 0;
    }
    else if (colorMode == color420)
    {
        yOffset = 2;
    }
    else
    {
        yOffset = 1;
    }

    loopHeight = height + yOffset;

    for(y=0; y<loopHeight; ++y)
    {

        for(x=0; x<loopWidth; ++x)
        {

#pragma HLS LOOP_FLATTEN OFF
#pragma HLS PIPELINE II=1

            //processing (output) pixel coordinates
            out_y = y - yOffset;
            out_x = x; //x - xOffset;

            if (y < height)
            {
                srcImg >> pix;
                // create multi-pixel samples of luma only or chroma only
                for (I16 s=0; s<SAMPLES_PER_CLOCK; ++s)
                {
                    mpix_y.val[s] = pix.val[s*NR_COMPONENTS];
                    mpix_c.val[s] = pix.val[s*NR_COMPONENTS+1];
                }
            }

            //luma line buffer
#pragma HLS ARRAY_PARTITION variable=&pixbuf_y      complete dim=0
            // get column of pixels from the line buffer to local pixel array
            for (I16 i=0; i<LUMA_LINES; i++)
            {
                Y_MEM_PIXEL_TYPE LineBufVal = linebuf_y.getval(i,x);
                for (int l = 0; l < SAMPLES_PER_CLOCK; l++)
                {
                    int start = (l * BITS_PER_COMPONENT);
                    pixbuf_y[LUMA_LINES-1-i].val[l] = LineBufVal(start + BITS_PER_COMPONENT -1, start);
                }
            }

            // get new pixels from stream
            for (int l = 0; l < SAMPLES_PER_CLOCK; l++)
            {
                int start = (l * BITS_PER_COMPONENT);
                InYPix(start + BITS_PER_COMPONENT -1, start) = mpix_y.val[l];
            }
            linebuf_y.insert_bottom(InYPix, x); //pix does not change after final line - bottom edge padding
            pixbuf_y[LUMA_LINES] = mpix_y;

            for (I16 i=LUMA_LINES-1; i>0;  i--) // for circular buffer implementation
            {
                //on first line, fill line buffer with first pixel value - top edge padding
                Y_MEM_PIXEL_TYPE LineBufVal;
                Y_MULTI_PIXEL PixBufVal = (y>0) ? pixbuf_y[LUMA_LINES-i] : pixbuf_y[LUMA_LINES];
                for (int l = 0; l < SAMPLES_PER_CLOCK; l++)
                {
                        int start = (l* BITS_PER_COMPONENT);
                        LineBufVal(start + BITS_PER_COMPONENT -1, start) = PixBufVal.val[l];
                }
                linebuf_y.val[i][x] = LineBufVal;
            }

            // chroma line buffer
#pragma HLS ARRAY_PARTITION variable=&pixbuf_c      complete dim=0
            ChromaLine = ((y&1) && (colorMode == color420)) ? 0 : 1;
            // get column of pixels from the line buffer to local pixel array
            for (I16 i=0; i<CHROMA_LINES-1; i++)
            {
                C_MULTI_PIXEL CBufVal;
                C_MEM_PIXEL_TYPE LineBufVal = linebuf_c.getval(i,x);
                for (int l = 0; l < SAMPLES_PER_CLOCK; l++)
                {
                    int start = (l * BITS_PER_COMPONENT);
                    CBufVal.val[l] = LineBufVal(start + BITS_PER_COMPONENT -1, start);
                }
                if (ChromaLine == 1)
                {
                    pixbuf_c[CHROMA_LINES-1-i-1] = CBufVal;
                }
                else
                {
                    pixbuf_c[CHROMA_LINES-1-i] = CBufVal;
                }
            }

            if (ChromaLine == 1)
            {
                if (y < height)
                {
                    pixbuf_c[CHROMA_LINES-1] = mpix_c;
                }
                else
                {
                    pixbuf_c[CHROMA_LINES-1] = pixbuf_c[CHROMA_LINES-2];
                }
            }
            else
            {
                C_MEM_PIXEL_TYPE LineBufCVal = linebuf_c.getval(CHROMA_LINES-1,x);
                for (int l = 0; l < SAMPLES_PER_CLOCK; l++)
                {
                    int start = (l * BITS_PER_COMPONENT);
                    pixbuf_c[0].val[l] = LineBufCVal(start + BITS_PER_COMPONENT -1, start);
                }
            }

            if (ChromaLine == 1)
            {
                if (y < height) //only insert new pixel if reading in new chroma line from image - bottom edge padding
                {
                    for (int l = 0; l < SAMPLES_PER_CLOCK; l++)
                    {
                            int start = (l * BITS_PER_COMPONENT);
                            InCPix(start + BITS_PER_COMPONENT -1, start) = mpix_c.val[l];
                    }
                    linebuf_c.insert_bottom(InCPix, x); //push read data to line buffer
                }
                for (I16 i=CHROMA_LINES-2; i>0;  i--) // for circular buffer implementation
                {
                    //on first line, fill line buffer with first pixel value - top edge padding
                    C_MEM_PIXEL_TYPE LineBufVal;
                    C_MULTI_PIXEL PixBufVal = (y>0) ? pixbuf_c[CHROMA_LINES-i-1] : pixbuf_c[CHROMA_LINES-1];
                    for (int l = 0; l < SAMPLES_PER_CLOCK; l++)
                    {
                            int start = (l* BITS_PER_COMPONENT);
                            LineBufVal(start + BITS_PER_COMPONENT -1, start) = PixBufVal.val[l];
                    }
                    linebuf_c.val[i][x] = LineBufVal;
                }
            }

            for(k=0; k<SAMPLES_PER_CLOCK; ++k)
            {
                {
                    if (colorMode == color422)
                    {
                        // 422 to 420 fixed coef filtering [ 1/4 1/2 1/4 ]
                        // luma component
                        outpix.val[k*NR_COMPONENTS] = pixbuf_y[1].val[k];
                        if (out_y & 1) // odd rows (1, 3, 5, etc)
                        {
                            // set rows with no chroma information to zero
                            outpix.val[k*NR_COMPONENTS+1] = 0;
                        }
                        else // even rows (0, 2, 4, etc)
                        {
                            // interpolate co-sited pixel
                            outpix.val[k*NR_COMPONENTS+1] = (pixbuf_c[0].val[k] + 2*pixbuf_c[1].val[k] + pixbuf_c[2].val[k] + 2) / 4;
                        }
                    }
                    else
                    {
                        // 420 to 422 fixed coef filtering [ 1/2 1/2 ]
                        // luma component
                        outpix.val[k*NR_COMPONENTS] = pixbuf_y[0].val[k];
                        if (out_y & 1) // odd rows (1, 3, 5, etc)
                        {
                            //interpolate by averaging nearest neighbors
                            outpix.val[k*NR_COMPONENTS+1] = (pixbuf_c[1].val[k] + pixbuf_c[2].val[k] + 1) / 2;
                        }
                        else // even rows (0, 2, 4, etc)
                        {
                            // passthru co-sited pixel
                            outpix.val[k*NR_COMPONENTS+1] = pixbuf_c[1].val[k];
                        }
                    }
                }

            // set unused third video component to zero
            outpix.val[k*NR_COMPONENTS+2] = 0;

            } // for (k

            if((out_y>=0) && (out_x>=0))
            {
                outImg << ((bPassThru) ? pix : outpix);
            }
        }
    }
}

#endif
