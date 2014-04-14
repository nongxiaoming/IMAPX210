#ifndef __IMAP_UART_H
#define __IMAP_UART_H
/*UART寄存器*/

/*uart0寄存器定义*/
#define RBR0        (*(volatile unsigned *)(0x20E20000))        /*LCR[7]=0,接收缓冲区寄存器，只读*/
#define THR0        (*(volatile unsigned *)(0x20E20000))        /*LCR[7]=0,发送缓冲区寄存器，只写*/
#define DLL0        (*(volatile unsigned *)(0x20E20000))        /*LCR[7]=1,时钟分频寄存器L，读写*/
#define DLH0        (*(volatile unsigned *)(0x20E20004))        /*LCR[7]=1,时钟分频寄存器H，读写*/
#define IER0        (*(volatile unsigned *)(0x20E20004))        /*LCR[7]=0,中断使能寄存器，读写*/
#define IIR0        (*(volatile unsigned *)(0x20E20008))        /*中断辨别寄存器，只读*/
#define FCR0        (*(volatile unsigned *)(0x20E20008))        /*FIFO控制寄存器，只写*/
#define LCR0        (*(volatile unsigned *)(0x20E2000C))        /*线控制寄存器，读写*/
#define MCR0        (*(volatile unsigned *)(0x20E20010))        /*模式制寄存器，读写*/
#define LSR0        (*(volatile unsigned *)(0x20E20014))        /*线状态寄存器，只读*/
#define CSR0        (*(volatile unsigned *)(0x20E20018))        /*CTS状态寄存器，只读*/
#define LPDLL0        (*(volatile unsigned *)(0x20E20020))        /*低功耗时钟分频寄存器L，读写*/
#define LPDLH0        (*(volatile unsigned *)(0x20E20024))        /*低功耗时钟分频寄存器H，读写*/
#define USR0        (*(volatile unsigned *)(0x20E2007C))          /*UART状态寄存器，只读*/
#define TFL0        (*(volatile unsigned *)(0x20E20080))          /*FIFO传输级别寄存器，只读*/
#define RFL0        (*(volatile unsigned *)(0x20E20084))          /*FIFO接收级别寄存器，只读*/
#define HTX0        (*(volatile unsigned *)(0x20E200A4))          /*UART异常TX寄存器，读写*/
#define DMASA0        (*(volatile unsigned *)(0x20E200A8))        /*DAM软件应答寄存器，只写*/
#define CKSR0        (*(volatile unsigned *)(0x20E20100))          /*UART时钟选择寄存器，读写*/

/*uart1寄存器定义*/
#define RBR1        (*(volatile unsigned *)(0x20E21000))        /*LCR[7]=0,接收缓冲区寄存器，只读*/
#define THR1        (*(volatile unsigned *)(0x20E21000))        /*LCR[7]=0,发送缓冲区寄存器，只写*/
#define DLL1        (*(volatile unsigned *)(0x20E21000))        /*LCR[7]=1,时钟分频寄存器L，读写*/
#define DLH1        (*(volatile unsigned *)(0x20E21004))        /*LCR[7]=1,时钟分频寄存器H，读写*/
#define IER1        (*(volatile unsigned *)(0x20E21004))        /*LCR[7]=0,中断使能寄存器，读写*/
#define IIR1        (*(volatile unsigned *)(0x20E21008))        /*中断辨别寄存器，只读*/
#define FCR1        (*(volatile unsigned *)(0x20E21008))        /*FIFO控制寄存器，只写*/
#define LCR1        (*(volatile unsigned *)(0x20E2100C))        /*线控制寄存器，读写*/
#define MCR1        (*(volatile unsigned *)(0x20E21010))        /*模式制寄存器，读写*/
#define LSR1        (*(volatile unsigned *)(0x20E21014))        /*线状态寄存器，只读*/
#define CSR1        (*(volatile unsigned *)(0x20E21018))        /*CTS状态寄存器，只读*/
#define LPDLL1        (*(volatile unsigned *)(0x20E21020))        /*低功耗时钟分频寄存器L，读写*/
#define LPDLH1        (*(volatile unsigned *)(0x20E21024))        /*低功耗时钟分频寄存器H，读写*/
#define USR1        (*(volatile unsigned *)(0x20E2107C))          /*UART状态寄存器，只读*/
#define TFL1        (*(volatile unsigned *)(0x20E21080))          /*FIFO传输级别寄存器，只读*/
#define RFL1        (*(volatile unsigned *)(0x20E21084))          /*FIFO接收级别寄存器，只读*/
#define HTX1        (*(volatile unsigned *)(0x20E210A4))          /*UART异常TX寄存器，读写*/
#define DMASA1        (*(volatile unsigned *)(0x20E210A8))        /*DAM软件应答寄存器，只写*/
#define CKSR1        (*(volatile unsigned *)(0x20E21100))          /*UART时钟选择寄存器，读写*/
/*uart2寄存器定义*/
#define RBR2        (*(volatile unsigned *)(0x20E22000))        /*LCR[7]=0,接收缓冲区寄存器，只读*/
#define THR2        (*(volatile unsigned *)(0x20E22000))        /*LCR[7]=0,发送缓冲区寄存器，只写*/
#define DLL2        (*(volatile unsigned *)(0x20E22000))        /*LCR[7]=1,时钟分频寄存器L，读写*/
#define DLH2        (*(volatile unsigned *)(0x20E22004))        /*LCR[7]=1,时钟分频寄存器H，读写*/
#define IER2        (*(volatile unsigned *)(0x20E22004))        /*LCR[7]=0,中断使能寄存器，读写*/
#define IIR2        (*(volatile unsigned *)(0x20E22008))        /*中断辨别寄存器，只读*/
#define FCR2        (*(volatile unsigned *)(0x20E22008))        /*FIFO控制寄存器，只写*/
#define LCR2        (*(volatile unsigned *)(0x20E2200C))        /*线控制寄存器，读写*/
#define MCR2        (*(volatile unsigned *)(0x20E22010))        /*模式制寄存器，读写*/
#define LSR2        (*(volatile unsigned *)(0x20E22014))        /*线状态寄存器，只读*/
#define CSR2        (*(volatile unsigned *)(0x20E22018))        /*CTS状态寄存器，只读*/
#define LPDLL2        (*(volatile unsigned *)(0x20E22020))        /*低功耗时钟分频寄存器L，读写*/
#define LPDLH2        (*(volatile unsigned *)(0x20E22024))        /*低功耗时钟分频寄存器H，读写*/
#define USR2        (*(volatile unsigned *)(0x20E2207C))          /*UART状态寄存器，只读*/
#define TFL2        (*(volatile unsigned *)(0x20E22080))          /*FIFO传输级别寄存器，只读*/
#define RFL2        (*(volatile unsigned *)(0x20E22084))          /*FIFO接收级别寄存器，只读*/
#define HTX2        (*(volatile unsigned *)(0x20E220A4))          /*UART异常TX寄存器，读写*/
#define DMASA2        (*(volatile unsigned *)(0x20E220A8))        /*DAM软件应答寄存器，只写*/
#define CKSR2        (*(volatile unsigned *)(0x20E22100))          /*UART时钟选择寄存器，读写*/

/*uart3寄存器定义*/
#define RBR3        (*(volatile unsigned *)(0x20E23000))        /*LCR[7]=0,接收缓冲区寄存器，只读*/
#define THR3        (*(volatile unsigned *)(0x20E23000))        /*LCR[7]=0,发送缓冲区寄存器，只写*/
#define DLL3        (*(volatile unsigned *)(0x20E23000))        /*LCR[7]=1,时钟分频寄存器L，读写*/
#define DLH3        (*(volatile unsigned *)(0x20E23004))        /*LCR[7]=1,时钟分频寄存器H，读写*/
#define IER3        (*(volatile unsigned *)(0x20E23004))        /*LCR[7]=0,中断使能寄存器，读写*/
#define IIR3        (*(volatile unsigned *)(0x20E23008))        /*中断辨别寄存器，只读*/
#define FCR3        (*(volatile unsigned *)(0x20E23008))        /*FIFO控制寄存器，只写*/
#define LCR3        (*(volatile unsigned *)(0x20E2300C))        /*线控制寄存器，读写*/
#define MCR3        (*(volatile unsigned *)(0x20E23010))        /*模式制寄存器，读写*/
#define LSR3        (*(volatile unsigned *)(0x20E23014))        /*线状态寄存器，只读*/
#define CSR3        (*(volatile unsigned *)(0x20E23018))        /*CTS状态寄存器，只读*/
#define LPDLL3        (*(volatile unsigned *)(0x20E23020))        /*低功耗时钟分频寄存器L，读写*/
#define LPDLH3        (*(volatile unsigned *)(0x20E23024))        /*低功耗时钟分频寄存器H，读写*/
#define USR3        (*(volatile unsigned *)(0x20E2307C))          /*UART状态寄存器，只读*/
#define TFL3        (*(volatile unsigned *)(0x20E23080))          /*FIFO传输级别寄存器，只读*/
#define RFL3        (*(volatile unsigned *)(0x20E23084))          /*FIFO接收级别寄存器，只读*/
#define HTX3        (*(volatile unsigned *)(0x20E230A4))          /*UART异常TX寄存器，读写*/
#define DMASA3        (*(volatile unsigned *)(0x20E230A8))        /*DAM软件应答寄存器，只写*/
#define CKSR3        (*(volatile unsigned *)(0x20E23100))          /*UART时钟选择寄存器，读写*/

#endif
