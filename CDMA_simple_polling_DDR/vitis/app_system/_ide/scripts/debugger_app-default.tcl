# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: /home/rom41797/Documents/Project/CDMA_simple_polling_DDR/vitis/app_system/_ide/scripts/debugger_app-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source /home/rom41797/Documents/Project/CDMA_simple_polling_DDR/vitis/app_system/_ide/scripts/debugger_app-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent Cora Z7 - 7007S 210370A92FA7A" && level==0 && jtag_device_ctx=="jsn-Cora Z7 - 7007S-210370A92FA7A-13722093-0"}
fpga -file /home/rom41797/Documents/Project/CDMA_simple_polling_DDR/vitis/app/_ide/bitstream/dma_demo_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw /home/rom41797/Documents/Project/CDMA_simple_polling/vitis/dma_demo_wrapper/export/dma_demo_wrapper/hw/dma_demo_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source /home/rom41797/Documents/Project/CDMA_simple_polling_DDR/vitis/app/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow /home/rom41797/Documents/Project/CDMA_simple_polling_DDR/vitis/app/Debug/app.elf
configparams force-mem-access 0
bpadd -addr &main
