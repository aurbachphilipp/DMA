###############################################################################
#
# Copyright (C) 2014 - 2019 Xilinx, Inc.  All rights reserved.
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
###############################################################################
#
# Modification History
#
# Ver   Who  Date     Changes
# ----- ---- -------- -----------------------------------------------
# 1.0	pkp  07/21/14 Initial common::version
# 1.3   mus  02/20/17 Updated tcl to guard xparameters.h by protection macros
# 1.4   ms   04/18/17 Modified tcl file to add suffix U for XPAR_CPU_ID
#                     parameter of cpu_cortexa53 in xparameters.h
# 1.4   mus  07/26/17 Updated extra compiler flags for a53 32 bit processor
#                     by appending "-mfpu=vfpv3 -mfloat-abi=hard". This change
#                     has been done to support hard floating point operations
#                     for a53 32 bit BSP.
# 1.5   mus  09/18/17 Updated to check each extra compiler flag individually
#                     for Cortexa53 32 mode BSP.This change allows users to
#                     modify default flag value.It fixes CR#984945.
# 1.6   mus  01/30/18 Updated to support armclang compiler
#       aru  04/18/19 Updated to add Assembler support for armclang
##############################################################################
#uses "xillib.tcl"

############################################################
# "generate" procedure
############################################################
proc generate {drv_handle} {

    xdefine_cortexa53_params $drv_handle
    ::hsi::utils::define_include_file $drv_handle "xparameters.h" "XCPU_CORTEXA53" "C_CPU_CLK_FREQ_HZ" "C_TIMESTAMP_CLK_FREQ"
    ::hsi::utils::define_canonical_xpars $drv_handle "xparameters.h" "CPU_CORTEXA53" "C_CPU_CLK_FREQ_HZ" "C_TIMESTAMP_CLK_FREQ"
    xdefine_addr_params_for_ext_intf $drv_handle "xparameters.h"
}

proc xdefine_cortexa53_params {drvhandle} {

    set sw_proc_handle [hsi::get_sw_processor]
    set hw_proc_handle [hsi::get_cells -hier [common::get_property HW_INSTANCE $sw_proc_handle ]]
    set procdrv [get_sw_processor]
    set compiler [common::get_property CONFIG.compiler $procdrv]
    if {[string compare -nocase $compiler "arm-none-eabi-gcc"] == 0} {
	set extra_flags [common::get_property CONFIG.extra_compiler_flags [hsi::get_sw_processor]]
	set temp_flag $extra_flags
	if {[string compare -nocase $temp_flag "-DARMA53_32  -mfpu=vfpv3 -mfloat-abi=hard -g -Wall -Wextra -march=armv7-a "] != 0} {
	      set flagindex [string first {-DARMA53_32} $temp_flag 0]
	      if { $flagindex == -1 } {
		   set temp_flag "$temp_flag -DARMA53_32"
	      }

	      set flagindex [string first {-mfpu=} $temp_flag 0]
              if { $flagindex == -1 } {
	           set temp_flag "$temp_flag -mfpu=vfpv3"
	      }

	      set flagindex [string first {-mfloat-abi=} $temp_flag 0]
	      if { $flagindex == -1 } {
		    set temp_flag "$temp_flag -mfloat-abi=hard"
	      }

	      set flagindex [string first {-g} $temp_flag 0]
	      if { $flagindex == -1 } {
		    set temp_flag "$temp_flag -g"
	      }

	      set flagindex [string first {-Wall} $temp_flag 0]
	      if { $flagindex == -1 } {
		   set temp_flag "$temp_flag -Wall"
	      }

	      set flagindex [string first {-Wextra} $temp_flag 0]
	      if { $flagindex == -1 } {
		   set temp_flag "$temp_flag -Wextra"
	      }

	      set flagindex [string first {-march=} $temp_flag 0]
	      if { $flagindex == -1 } {
		   set temp_flag "$temp_flag -march=armv7-a"
	      }

	      set extra_flags $temp_flag
              common::set_property -name {EXTRA_COMPILER_FLAGS} -value $extra_flags -objects [hsi::get_sw_processor]
         }
    } elseif {[string compare -nocase $compiler "armclang"] == 0} {
	set extra_flags [common::get_property CONFIG.extra_compiler_flags [hsi::get_sw_processor]]
	set extra_flags ""
	set temp_flag $extra_flags
	if {[string compare -nocase $temp_flag "-mfpu=fp-armv8 -g -Wall -Wextra -march=armv8-a --target=aarch64-arm-none-eabi "] != 0} {
	      set flagindex [string first {-mfpu=} $temp_flag 0]
              if { $flagindex == -1 } {
	           set temp_flag "$temp_flag -mfpu=fp-armv8"
	      }

	      set flagindex [string first {-g} $temp_flag 0]
	      if { $flagindex == -1 } {
		    set temp_flag "$temp_flag -g"
	      }

	      set flagindex [string first {-Wall} $temp_flag 0]
	      if { $flagindex == -1 } {
		   set temp_flag "$temp_flag -Wall"
	      }

	      set flagindex [string first {-Wextra} $temp_flag 0]
	      if { $flagindex == -1 } {
		   set temp_flag "$temp_flag -Wextra"
	      }

	      set flagindex [string first {-march=} $temp_flag 0]
	      if { $flagindex == -1 } {
		   set temp_flag "$temp_flag -march=armv8-a"
	      }

              set flagindex [string first {--target=} $temp_flag 0]
	      if { $flagindex == -1 } {
		   set temp_flag "$temp_flag --target=aarch64-arm-none-eabi"
	      }

	      set extra_flags $temp_flag
              common::set_property -name {EXTRA_COMPILER_FLAGS} -value $extra_flags -objects [hsi::get_sw_processor]
         }
	set assembler_value "armasm"
	common::set_property -name {ASSEMBLER} -value $assembler_value -objects  [hsi::get_sw_processor]
    }


    #Append LTO flag in EXTRA_COMPILER_FLAGS for zynqmp_fsbl_bsp
    set is_zynqmp_fsbl_bsp [common::get_property CONFIG.ZYNQMP_FSBL_BSP [hsi::get_os]]
    if {$is_zynqmp_fsbl_bsp == true} {
		set extra_flags [common::get_property CONFIG.extra_compiler_flags [hsi::get_sw_processor]]
		if {[string compare -nocase $compiler "armclang"] == 0} {
		    #Append -Oz in EXTRA_COMPILER_FLAGS if not exist previoulsy.
		    if {[string first "-Oz" $extra_flags] == -1 } {
			    append extra_flags " -Oz"
			    common::set_property -name {EXTRA_COMPILER_FLAGS} -value $extra_flags -objects [hsi::get_sw_processor]
		     }
		} else {
		    #Append LTO flag in EXTRA_COMPILER_FLAGS if not exist previoulsy.
		    if {[string first "-flto" $extra_flags] == -1 } {
			    append extra_flags " -Os -flto -ffat-lto-objects"
			    common::set_property -name {EXTRA_COMPILER_FLAGS} -value $extra_flags -objects [hsi::get_sw_processor]
		     }
		}
    }

    set archiver [common::get_property CONFIG.archiver $procdrv]
    if {[string first "iarchive" $archiver] < 0 } {
    } else {
	 set libxil_a [file join .. .. lib libxil.a]
	 if { ![file exists $libxil_a] } {
	 # create empty libxil.a
		set fd [open "test.a" a+]
		close $fd
		exec $archiver --create --output $libxil_a test.a
		file delete -force test.a
	}
    }
    set periphs [::hsi::utils::get_common_driver_ips $drvhandle]
    set lprocs [hsi::get_cells -hier -filter "IP_NAME==psu_cortexa53"]
    set lprocs [lsort $lprocs]

    set config_inc [::hsi::utils::open_include_file "xparameters.h"]
    puts $config_inc "#ifndef XPARAMETERS_H   /* prevent circular inclusions */"
    puts $config_inc "#define XPARAMETERS_H   /* by using protection macros */"
    puts $config_inc ""
    puts $config_inc "/* Definition for CPU ID */"

    foreach periph $periphs {
        set iname [common::get_property NAME $periph]

	#-----------
	# Set CPU ID
	#-----------
	set id 0
	set uSuffix "U"
	foreach processor $lprocs {
	    if {[string compare -nocase $processor $iname] == 0} {
		puts $config_inc "#define XPAR_CPU_ID $id$uSuffix"
	    }
	    incr id
	}
    }

    close $config_inc
}

proc xdefine_addr_params_for_ext_intf {drvhandle file_name} {
    set sw_proc_handle [hsi::get_sw_processor]
    set hw_proc_handle [hsi::get_cells -hier [common::get_property HW_INSTANCE $sw_proc_handle ]]

 # Open include file
   set file_handle [::hsi::utils::open_include_file $file_name]

   set mem_ranges [hsi::get_mem_ranges -of_objects $hw_proc_handle]
   foreach mem_range $mem_ranges {
       set inst [common::get_property INSTANCE $mem_range]
       if {$inst != ""} {
            continue
       }


       set bparam_name [common::get_property BASE_NAME $mem_range]
       set bparam_value [common::get_property BASE_VALUE $mem_range]
       set hparam_name [common::get_property HIGH_NAME $mem_range]
       set hparam_value [common::get_property HIGH_VALUE $mem_range]

       # Print all parameters for all peripherals


           set name [string toupper [common::get_property NAME $mem_range]]
	   puts $file_handle ""
           puts $file_handle "/* Definitions for interface [string toupper $name] */"
           set name [format "XPAR_%s_" $name]


           if {$bparam_value != ""} {
               set value [::hsi::utils::format_addr_string $bparam_value $bparam_name]
                   set param [string toupper $bparam_name]
                   if {[string match C_* $param]} {
                       set name [format "%s%s" $name [string range $param 2 end]]
                   } else {
                       set name [format "%s%s" $name $param]
                   }

               puts $file_handle "#define $name $value"
           }

	   set name [string toupper [common::get_property NAME $mem_range]]
           set name [format "XPAR_%s_" $name]
           if {$hparam_value != ""} {
               set value [::hsi::utils::format_addr_string $hparam_value $hparam_name]
                set param [string toupper $hparam_name]
                   if {[string match C_* $param]} {
                       set name [format "%s%s" $name [string range $param 2 end]]
                   } else {
                       set name [format "%s%s" $name $param]
                   }

               puts $file_handle "#define $name $value"
           }


           puts $file_handle ""
      }

    close $file_handle
}

proc post_generate_final {drv_handle} {

	set type [get_property CLASS $drv_handle]
	if {[string equal $type "driver"]} {
	   return
	}

	set file_handle [::hsi::utils::open_include_file "xparameters.h"]
	puts $file_handle "#endif  /* end of protection macro */"
	close $file_handle
}
