################################################################################
#
# Copyright (C) 2017 Xilinx, Inc.  All rights reserved.
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
################################################################################

proc generate {drv_handle} {
    xdefine_include_file $drv_handle "xparameters.h" "XV_SdiTx" \
    "NUM_INSTANCES" \
    "DEVICE_ID" \
    "AXI_CTRL_BASEADDR" \
    "AXI_CTRL_HIGHADDR" \
    "C_INCLUDE_EDH" \
    "C_LINE_RATE" \
    "C_TX_INSERT_C_STR_ST352"

    xdefine_config_file $drv_handle "xv_sditx_g.c" \
    "XV_SdiTx" \
    "DEVICE_ID" \
    "AXI_CTRL_BASEADDR" \
    "C_INCLUDE_EDH" \
    "C_LINE_RATE" \
    "C_TX_INSERT_C_STR_ST352"

    xdefine_canonical_xpars $drv_handle "xparameters.h" "XV_SdiTx" \
    "NUM_INSTANCES" \
    "DEVICE_ID" \
    "AXI_CTRL_BASEADDR" \
    "AXI_CTRL_HIGHADDR" \
    "C_INCLUDE_EDH" \
    "C_LINE_RATE" \
    "C_TX_INSERT_C_STR_ST352"
set orig_dir [pwd]
cd ../../include/

set timestamp [clock format [clock seconds] -format {%Y%m%d%H%M%S}]
set filename "xparameters.h"
set temp $filename.new.$timestamp
set backup $filename.bak.$timestamp

set in [open $filename r]
set out [open $temp w]

# line-by-line, read the original file
while {[gets $in line] != -1} {
	# if XPAR_.*V_SMPTE_UHDSDI_TX is present in the string
	if { [regexp -nocase {XPAR_.*V_SMPTE_UHDSDI_TX} $line] ||
		[regexp -nocase {XPAR_.*SDITX} $line] } {
		# if substring LINE_RATE is present in the string
		if { [regexp -nocase {LINE_RATE } $line] } {
			# using string map to replace strings with numbers
			set line [string map {3G_SDI 0 6G_SDI 1 12G_SDI_8DS 2 12G_SDI_16DS 3} $line]
			set line [string map {3GSDI 0 6GSDI 1 12GSDI8DS 2 12GSDI16DS 3} $line]
		}
		if { [regexp -nocase {INCLUDE_EDH } $line] } {
		}
	}

		# then write the transformed line
		puts $out $line
	}
close $in
close $out

# move the new data to the proper filename
file delete $filename
file rename -force $temp $filename
cd $orig_dir

}
