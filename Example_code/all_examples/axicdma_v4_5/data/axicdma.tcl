###############################################################################
#
# Copyright (C) 2010 - 2018 Xilinx, Inc.  All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# 
#
##############################################################################

proc generate {drv_handle} {
	::hsi::utils::define_include_file $drv_handle "xparameters.h" "XAxiCdma" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" "C_INCLUDE_DRE" "C_USE_DATAMOVER_LITE" "C_M_AXI_DATA_WIDTH" "C_INCLUDE_SG" "C_M_AXI_MAX_BURST_LEN" "C_ADDR_WIDTH"

	::hsi::utils::define_config_file  $drv_handle "xaxicdma_g.c" "XAxiCdma" "DEVICE_ID" "C_BASEADDR" "C_INCLUDE_DRE" "C_USE_DATAMOVER_LITE" "C_M_AXI_DATA_WIDTH" "C_M_AXI_MAX_BURST_LEN" "C_ADDR_WIDTH"

	::hsi::utils::define_canonical_xpars $drv_handle "xparameters.h" "AxiCdma" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" "C_INCLUDE_DRE" "C_USE_DATAMOVER_LITE" "C_M_AXI_DATA_WIDTH" "C_INCLUDE_SG" "C_M_AXI_MAX_BURST_LEN" "C_ADDR_WIDTH"
}
