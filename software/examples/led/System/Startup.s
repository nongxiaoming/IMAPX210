********************************************************************************************************
;                                《《《ARM S3C6410启动文件》》》
;
;                 说明：三星S3C6410启动汇编文件，参考ARM官方S3C2440A代码
;									 	                          ----nongxiaoming
;********************************************************************************************************


; Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs

Mode_USR        EQU     0x10				;用户模式，正常程序执行模式，用于应用程序
Mode_FIQ        EQU     0x11				;快速中断模式，用于高速数据传输和通道处理。
Mode_IRQ        EQU     0x12				;外部中断模式，用于通用的中断处理。
Mode_SVC        EQU     0x13				;管理模式，使用的一种保护模式。
Mode_ABT        EQU     0x17				;数据访问中止模式，用于虚拟存储用存储保护
Mode_UND        EQU     0x1B				;未定义指令中止模式，当未定义指令执行时进入此模式。
Mode_SYS        EQU     0x1F				;系统模式，用于特权级的操作系统任务

I_Bit           EQU     0x80            	; 如果I位被置1，则外部中断被禁止(IRQ is disabled)
F_Bit           EQU     0x40            	; 如果F位被置1，则快速中断被禁止(FIQ is disabled)	
			
;----------------------- Stack and Heap Definitions ----------------------------

UND_Stack_Size  EQU     0x00000100		 	;设置各种模式栈大小
SVC_Stack_Size  EQU     0x00000100
ABT_Stack_Size  EQU     0x00000100
FIQ_Stack_Size  EQU     0x00000100
IRQ_Stack_Size  EQU     0x00000100
USR_Stack_Size  EQU     0x00000100


											;总栈的大小，也就是也有模式下栈相加
ISR_Stack_Size  EQU     (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                         FIQ_Stack_Size + IRQ_Stack_Size)


											;开辟一个堆栈段，段名字为STACK，定义为可读可写，将内存单元初始化为0,
                AREA    STACK, NOINIT, READWRITE, ALIGN=3

Stack_Mem       SPACE   USR_Stack_Size		;SPACE -- 伪指令，用于分配一块内存单元，并用0初始化，与%同义
__initial_sp    SPACE   ISR_Stack_Size
Stack_Top									;堆栈段内容结束， 在这里放个标号,用来获得堆栈顶部地址



Heap_Size       EQU     0x00001000		  	;定义堆大小，一般程序中用到malloc才用到堆
											;开辟一个名字为HEAP可读可写，不初始化内存单的内存单元。

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base									;堆的基址
Heap_Mem        SPACE   Heap_Size			;堆内存起始地址标号
__heap_limit								;堆结束

;----------------------- 看门狗定时器定义 ----------------------------
WDT_BASE         EQU     0x20d90000            ; 看门狗基地址
WDT_CR_OFS       EQU     0x00                  ; 看门狗控制寄存器地址偏移
WDT_TORR_OFS       EQU     0x04                ; 看门狗数据寄存器地址偏移
WDT_CCVR_OFS       EQU     0x08                ; 看门狗计数寄存器地址偏移

;// <e> 看门狗寄存器设置
;//   <h> 看门狗控制寄存器 (WTCON)
;//     <o1.8..15>  Prescaler Value <0-255>
;//     <o1.5>      看门狗寄存器使能
;//     <o1.3..4>   看门狗时钟分频
;//       <0=> 16   <1=> 32  <2=> 64  <3=> 128
;//     <o1.2>      看门狗中断使能
;//     <o1.0>      看门狗复位使能
;//   </h>
;//   <h> 看门狗数据寄存器 (WTDAT)
;//     <o2.0..15>  计数值 <0-65535>
;//   </h>
;// </e> 看门狗寄存器设置
WT_SETUP        EQU     1                   ;是否设置看门狗：1为设置，0为不设置
WTCON_Val       EQU     0x00000000          ;WTCON的配置值
WTDAT_Val       EQU     0x00008000          ;WTDAT的配置值



                PRESERVE8					 ;PRESERVE8 -- 伪指令，指示当前文件请求堆栈为8字节对齐。
                

;  Area Definition and Entry Point
;  Startup Code must be linked first at Address at which it expects to run.

                AREA    RESET, CODE, READONLY ;声明一个名为RESET的代码段,属性为只读
                ARM 
               mrs	r0, CPSR
               bic	r0, r0, #31	; 0x1f
               orr	r0, r0, #211	; 0xd3
               msr	CPSR_fc, r0
			   bl	cpu_init_crit
; 配置看门狗---------------------------------------------------------------

                IF      WT_SETUP != 0             ;如果WT_SETUP不为0，默认为1
                LDR     R0, =WDT_BASE             ;将看门狗基地址存入R0
                LDR     R1, =WTCON_Val            ;将看门狗控制寄存器配置值存入R1
                LDR     R2, =WTDAT_Val            ;将看门狗数据寄存器配置值存入R2
                STR     R2, [R0, #WDT_CCVR_OFS]   ;将配置数据存入看门狗计数寄存器
                STR     R2, [R0, #WDT_TORR_OFS]   ;将配置数据存入看门狗数据寄存器
                STR     R1, [R0, #WDT_CR_OFS]     ;将配置数据存入看门狗控制寄存器，这里是关闭看门狗
                ENDIF
                

 ; Setup Stack for each mode ----------------------------------------------------

                LDR     R0, =Stack_Top

;  Enter Undefined Instruction Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #UND_Stack_Size

;  Enter Abort Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #ABT_Stack_Size

;  Enter FIQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #FIQ_Stack_Size

;  Enter IRQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #IRQ_Stack_Size

;  Enter Supervisor Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #SVC_Stack_Size

;  Enter User Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_USR
                MOV     SP, R0
                SUB     SL, SP, #USR_Stack_Size

;  Enter User Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_SYS:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     SL, SP, #USR_Stack_Size

;  Enter User Mode and set its Stack Pointer
;               MSR     CPSR_c, #Mode_USR
                IF      :DEF:__MICROLIB

                EXPORT __initial_sp

                ELSE

                MOV     SP, R0
                SUB     SL, SP, #USR_Stack_Size

                ENDIF

                ;LDR SP,=1024*4

                IMPORT  __main
                ;LDR     R0, =Main
                ;BX      R0
			    BL __main
cpu_init_crit
                mov	r0, #0	; 0x0
                MCR	p15, 0, r0, c7, c7, 0
                mcr	p15, 0, r0, c8, c7, 0
                mrc	p15, 0, r0, c1, c0, 0
                bic	r0, r0, #4	; 0x4
                bic	r0, r0, #4096	; 0x1000
                bic	r0, r0, #2048	; 0x800
                orr	r0, r0, #4194304	; 0x400000
                mcr	p15, 0, r0, c1, c0, 0
                mrc	p15, 0, r0, c1, c0, 2
                orr	r0, r0, #15728640	; 0xf00000
                mcr	p15, 0, r0, c1, c0, 2
                mov	ip, lr
				bl	lowlevel_init
                mov	lr, ip
                BX lr
lowlevel_init
                mov	r5, lr
                mov	r0, #549453824	; 0x20c00000
                orr	r0, r0, #19	; 0x13
                mcr	p15, 0, r0, c15, c2, 4
                mov	r1, #1	; 0x1
                str	r1, [r0, #264]
			   
            IF      :DEF:__MICROLIB

                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE
; User Initial Stack & Heap
                AREA    |.text|, CODE, READONLY

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + USR_Stack_Size)
                LDR     R2, = (Heap_Mem +      Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDIF


                END

