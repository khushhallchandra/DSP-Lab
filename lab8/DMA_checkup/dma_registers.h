#ifndef DMA_REGISTERS_H_
#define DMA_REGISTERS_H_
/* For more information see SPRUFT2A, Section 4, p.25, Tables 4-8 */
/* This file includes only DMA0 and global registers */

/* ==================== System Registers ==================== */
#define DMA_IFR *(ioport volatile unsigned *)0x1C30 //DMA Interrupt Flag Register
#define DMA_IER *(ioport volatile unsigned *)0x1C31 //DMA Interrupt Enable Register

#define DMA0_CESR1 *(ioport volatile unsigned *)0x1C1A //DMA0 Channel Event Source Register 1
#define DMA0_CESR2 *(ioport volatile unsigned *)0x1C1B //DMA0 Channel Event Source Register 2

/* ==================== DMA Controller 0 ==================== */
/* ------------------------ Channel 0 ----------------------- */
#define DMA0_CH0_SSAL *(ioport volatile unsigned *)0x0c00 //Channel 0 Source Start Address (Lower Part) Register
#define DMA0_CH0_SSAU *(ioport volatile unsigned *)0x0c01 //Channel 0 Source Start Address (Upper Part) Register
#define DMA0_CH0_DSAL *(ioport volatile unsigned *)0x0c02 //Channel 0 Destination Start Address (Lower Part) Register
#define DMA0_CH0_DSAU *(ioport volatile unsigned *)0x0c03 //Channel 0 Destination Start Address (Upper Part) Register
#define DMA0_CH0_TCR1 *(ioport volatile unsigned *)0x0c04 //Channel 0 Transfer Control Register 1
#define DMA0_CH0_TCR2 *(ioport volatile unsigned *)0x0c05 //Channel 0 Transfer Control Register 2
/* ---------------------------------------------------------- */

/* ------------------------ Channel 1 ----------------------- */
#define DMA0_CH1_SSAL *(ioport volatile unsigned *)0x0c20 //Channel 1 Source Start Address (Lower Part) Register
#define DMA0_CH1_SSAU *(ioport volatile unsigned *)0x0c21 //Channel 1 Source Start Address (Upper Part) Register
#define DMA0_CH1_DSAL *(ioport volatile unsigned *)0x0c22 //Channel 1 Destination Start Address (Lower Part) Register
#define DMA0_CH1_DSAU *(ioport volatile unsigned *)0x0c23 //Channel 1 Destination Start Address (Upper Part) Register
#define DMA0_CH1_TCR1 *(ioport volatile unsigned *)0x0c24 //Channel 1 Transfer Control Register 1
#define DMA0_CH1_TCR2 *(ioport volatile unsigned *)0x0c25 //Channel 1 Transfer Control Register 2
/* ---------------------------------------------------------- */

/* ------------------------ Channel 2 ----------------------- */
#define DMA0_CH2_SSAL *(ioport volatile unsigned *)0x0c40 //Channel 2 Source Start Address (Lower Part) Register
#define DMA0_CH2_SSAU *(ioport volatile unsigned *)0x0c41 //Channel 2 Source Start Address (Upper Part) Register
#define DMA0_CH2_DSAL *(ioport volatile unsigned *)0x0c42 //Channel 2 Destination Start Address (Lower Part) Register
#define DMA0_CH2_DSAU *(ioport volatile unsigned *)0x0c43 //Channel 2 Destination Start Address (Upper Part) Register
#define DMA0_CH2_TCR1 *(ioport volatile unsigned *)0x0c44 //Channel 2 Transfer Control Register 1
#define DMA0_CH2_TCR2 *(ioport volatile unsigned *)0x0c45 //Channel 2 Transfer Control Register 2
/* ---------------------------------------------------------- */

/* ------------------------ Channel 3 ----------------------- */
#define DMA0_CH3_SSAL *(ioport volatile unsigned *)0x0c60 //Channel 3 Source Start Address (Lower Part) Register
#define DMA0_CH3_SSAU *(ioport volatile unsigned *)0x0c61 //Channel 3 Source Start Address (Upper Part) Register
#define DMA0_CH3_DSAL *(ioport volatile unsigned *)0x0c62 //Channel 3 Destination Start Address (Lower Part) Register
#define DMA0_CH3_DSAU *(ioport volatile unsigned *)0x0c63 //Channel 3 Destination Start Address (Upper Part) Register
#define DMA0_CH3_TCR1 *(ioport volatile unsigned *)0x0c64 //Channel 3 Transfer Control Register 1
#define DMA0_CH3_TCR2 *(ioport volatile unsigned *)0x0c65 //Channel 3 Transfer Control Register 2
/* ---------------------------------------------------------- */

#endif /*DMA_REGISTERS_H_*/
