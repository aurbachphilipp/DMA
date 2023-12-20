# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct /home/rom41797/Documents/Project/DMA_demo_no_SG/project_1/vitis/dma_demo_wrapper/platform.tcl
# 
# OR launch xsct and run below command.
# source /home/rom41797/Documents/Project/DMA_demo_no_SG/project_1/vitis/dma_demo_wrapper/platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {dma_demo_wrapper}\
-hw {/home/rom41797/Documents/Project/DMA_demo_no_SG/project_1/dma_demo_wrapper.xsa}\
-fsbl-target {psu_cortexa53_0} -out {/home/rom41797/Documents/Project/DMA_demo_no_SG/project_1/vitis}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {dma_demo_wrapper}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate
platform active {dma_demo_wrapper}
platform config -updatehw {/home/rom41797/Documents/Project/CDMA_simple_polling/dma_demo_wrapper.xsa}
platform generate -domains 
platform clean
platform generate
