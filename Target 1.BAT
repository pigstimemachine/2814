SET PATH=K:\keil5\ARM\ARMCC\Bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files\NVIDIA Corporation\NVIDIA NvDLISR;D:\Program Files\Git\cmd;D:\programFiles\tortoisegit\bin;D:\programFiles\CADENCE\openaccess\bin\win32\opt;D:\programFiles\CADENCE\tools\capture;D:\programFiles\CADENCE\tools\pspice;D:\programFiles\CADENCE\tools\specctra\bin;D:\programFiles\CADENCE\tools\fet\bin;D:\programFiles\CADENCE\tools\libutil\bin;D:\programFiles\CADENCE\tools\bin;D:\programFiles\CADENCE\tools\pcb\bin;C:\Users\ZhaoCJ\AppData\Local\Microsoft\WindowsApps;D:\programFiles\PADS\PADSVX.2.3\SDD_HOME\CAMCAD
SET ARMCC5_ASMOPT=--diag_suppress=9931
SET ARMCC5_CCOPT=--diag_suppress=9931
SET ARMCC5_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\delay.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\sys.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\usart.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\timer.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stmflash.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\can.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\key.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\oled.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\showinterface.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\pic.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\led.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\taskmgr.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\main.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\uapp_can.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\uapp_comm.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\uapp_senser.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmAsm" --Via ".\output\startup_stm32f10x_md._ia"
"K:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\system_stm32f10x.__i"
"K:\keil5\ARM\ARMCC\Bin\ArmLink" --Via ".\OUTPUT\2810-3testt.lnp"
"K:\keil5\ARM\ARMCC\Bin\fromelf.exe" ".\OUTPUT\2810-3testt.axf" --i32combined --output ".\OUTPUT\2810-3testt.hex"
fromelf.exe --bin -o "E:\XG\AllProducts\SM-100\2814\Program\2814-1\OUTPUT\2810-3testt.bin" "E:\XG\AllProducts\SM-100\2814\Program\2814-1\OUTPUT\2810-3testt.axf"
