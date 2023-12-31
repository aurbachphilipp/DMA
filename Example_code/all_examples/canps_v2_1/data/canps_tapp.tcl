###############################################################################
#
# Copyright (C) 2004 - 2014 Xilinx, Inc.  All rights reserved.
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
# Use of the Software is limited solely to applications:
# (a) running on a Xilinx device, or
# (b) that interact with a Xilinx device through a bus or interconnect.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
# OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# Except as contained in this notice, the name of the Xilinx shall not be used
# in advertising or otherwise to promote the sale, use or other dealings in
# this Software without prior written authorization from Xilinx.
#
###############################################################################
##############################################################################
#
# Modification History
#
# Ver      Who    Date     Changes
# -------- ------ -------- ----------------------------------------------------
# 2.0     adk    10/12/13 Updated as per the New Tcl API's
##############################################################################

# Uses $XILINX_EDK/bin/lib/xillib_sw.tcl
# -----------------------------------------------------------------
# Software Project Types (swproj):
#   0 : MemoryTest - Calls basic  memorytest routines from common driver dir
#   1 : PeripheralTest - Calls any existing polled_example and/or selftest
# -----------------------------------------------------------------

# -----------------------------------------------------------------
# TCL Procedures:
# -----------------------------------------------------------------

proc gen_include_files {swproj mhsinst} {
     
    if {$swproj == 0} {
            return ""
    }
    if {$swproj == 1} {
            set inc_file_lines {xcanps.h canps_header.h}
    }    
        return $inc_file_lines
}
    
proc gen_src_files {swproj mhsinst} {
  if {$swproj == 0} {
    return ""
  }
  set isintr [::hsm::utils::is_ip_interrupting_current_proc $mhsinst]
  if {$swproj == 1} {
            if {$isintr == 1} {
		set inc_file_lines {examples/xcanps_polled_example.c examples/xcanps_intr_example.c data/canps_header.h}
	     } else {
		set inc_file_lines {examples/xcanps_polled_example.c data/canps_header.h}
	     }
		return $inc_file_lines
  }
}

proc gen_testfunc_def {swproj mhsinst} {
  return ""
}

proc gen_init_code {swproj mhsinst} {
    
    if {$swproj == 0} {
        return ""
    }
    if {$swproj == 1} {
        
      set ipname [get_property NAME $mhsinst]
      set decl "   static XCanPs ${ipname};"
      set inc_file_lines $decl
      return $inc_file_lines
      
    }
    
}

proc gen_testfunc_call {swproj mhsinst} {
    
    if {$swproj == 0} {
        return ""
    }

    set ipname [get_property NAME $mhsinst] 
    set deviceid [::hsm::utils::get_ip_param_name $mhsinst "DEVICE_ID"]
    set stdout [get_property CONFIG.STDOUT [get_os]]
    if { $stdout == "" || $stdout == "none" } {
       set hasStdout 0
    } else {
       set hasStdout 1
    }
    set isintr [::hsm::utils::is_ip_interrupting_current_proc $mhsinst]
    set intcvar intc
       
    set testfunc_call ""

    if {${hasStdout} == 0} {

      append testfunc_call "

   {
      int Status;
                        
      Status = CanPsPolledExample(${deviceid});

   }"
	if {$isintr == 1} {
        set intr_id "XPAR_${ipname}_INTR"
	set intr_id [string toupper $intr_id]
	
      append testfunc_call "
        
   {
      int Status;
      Status = CanPsIntrExample(&${intcvar}, &${ipname}, \\
                                 ${deviceid}, \\
                                 ${intr_id});
   }"
 
   }



  } else {

      append testfunc_call "

   {
      int Status;
      
      print(\"\\r\\n Running CanPsPolledExample() for ${ipname}...\\r\\n\");
      
      Status = CanPsPolledExample(${deviceid});
      
      if (Status == 0) {
         print(\"CanPsPolledExample PASSED\\r\\n\");
      }
      else {
         print(\"CanPsPolledExample FAILED\\r\\n\");
      }
   }"

	if {$isintr ==1 } {
        set intr_id "XPAR_${ipname}_INTR"
	set intr_id [string toupper $intr_id]
	
      append testfunc_call "
   {
      int Status;

      print(\"\\r\\n Running Interrupt Test  for ${ipname}...\\r\\n\");
      
      Status = CanPsIntrExample(&${intcvar}, &${ipname}, \\
                                 ${deviceid}, \\
                                 ${intr_id});
	
      if (Status == 0) {
         print(\"CanPsIntrExample PASSED\\r\\n\");
      } 
      else {
         print(\"CanPsIntrExample FAILED\\r\\n\");
      }

   }"
 } 


  }

  return $testfunc_call
}

