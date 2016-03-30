#include "data_types.h"
#include "dma_setup.h"
#include "i2s_setup.h"
#include "register_system.h"
#include "register_cpu.h"
#include "aic3204.h"
#include "global_constants.h"

#define PLL_100M 1 /* Set PLL system clock to 100MHz */
#define PLL_98M  0
#define PLL_40M  0
#define PLL_12M  0

/*Flags for determining whether the PING or the PONG buffer is filled*/
Int16 PingPongFlagInL;
Int16 PingPongFlagInR;
Int16 PingPongFlagOutL;
Int16 PingPongFlagOutR;

/* Buffers for DMA in/out and overlap-add */
Int16 DMA_InpL[PING_PONG_SIZE];		//first half of these buffer will be used as PING buffer
Int16 DMA_InpR[PING_PONG_SIZE];		//second part will be used as PONG buffer
Int16 DMA_OutL[PING_PONG_SIZE];
Int16 DMA_OutR[PING_PONG_SIZE];

/* Buffers for processing */
Int16 BufferL[PING_PONG_SIZE/2];
Int16 BufferR[PING_PONG_SIZE/2];

void InitSystem(void);
void ConfigPort(void);
void SYS_GlobalIntEnable(void);
void SYS_GlobalIntDisable(void);

/* Choose AIC3204 sampling rate */
short fs = AIC3204_FS_48KHZ;

void main(void) 
{
	Int16 i;
	
	InitSystem();
	ConfigPort();
	
	SYS_GlobalIntEnable(); /* Enable global interrupts */
	IER0 = 0x0100;         /* Enable DMA0 interrupt */

    I2S0_setup();          /* Setup I2S0 */

	AIC3204_Init();        /* Initialize AIC3204 */

	DMA0_setup();          /* Setup DMA0 CH0-3 */
   	
   	I2S0_enable();         /* Enable I2S0 */  
   	       
   	DMA0_enable_CH(0);	   /* Enable DMA0CH0 */
 
   	DMA0_enable_CH(1);	   /* Enable DMA0CH1 */
   	
   	DMA0_enable_CH(2);	   /* Enable DMA0CH2 */	
   	 
   	DMA0_enable_CH(3);	   /* Enable DMA0CH3 */	

	/* Begin infinite loop */
	while (1)
	{
		if (PingPongFlagInL && PingPongFlagInR) 			//If this condition is satisfied, then input PONG buffer is filled. Access it. 
		{													//input PONG buffer is essentially the last half of DMA_InpX.
			for (i = 0; i < PING_PONG_SIZE/2; i++) 
			{
				BufferL[i] = DMA_InpL[i + PING_PONG_SIZE/2];
				BufferR[i] = DMA_InpR[i + PING_PONG_SIZE/2];
			}
		} 
		else 												// Else, input PONG buffer is filled. Access it.
		{													// input PING buffer is essentially the first half of DMA_InpX.
			for (i = 0; i < PING_PONG_SIZE/2; i++) 
			{
				BufferL[i] = DMA_InpL[i];
				BufferR[i] = DMA_InpR[i];
			}			
		}
		
        if (PingPongFlagOutL && PingPongFlagOutR) 			//If this condition is satisfied, then output PONG buffer is filled. Access it. 
        {													//output PONG buffer is essentially the last half of DMA_OutX.
			for (i = 0; i < PING_PONG_SIZE/2; i++) 
			{
        		DMA_OutL[i + PING_PONG_SIZE/2] = BufferL[i];
				DMA_OutR[i + PING_PONG_SIZE/2] = BufferL[i];
        	}
        }
        else 
        {
			for (i = 0; i < PING_PONG_SIZE/2; i++) 			//If this condition is satisfied, then output PONG buffer is filled. Access it. 
			{												//output PONG buffer is essentially the last half of DMA_OutX.
        		DMA_OutL[i] = BufferL[i];
				DMA_OutR[i] = BufferL[i];
        	}
        }
	}
}

/* ======================== Initialize DSP System Clock =========================  */
/* ------------------------------------------------------------------------------  */
/* For more info see SPRUFX5D - Section 1.4.3.2.6 (copying below for reference:)   */
/* You can follow the steps below to program the PLL of the DSP clock generator.   */ 
/* The recommendation is to stop all peripheral operation before changing the PLL  */ 
/* frequency, with the exception of the device CPU and USB. The device CPU must be */
/* operational to program the PLL controller. Software is responsible for ensuring */
/* the PLL remains in BYPASS_MODE for at least 4 ms before switching to PLL_MODE.  */
/* 1. Make sure the clock generator is in BYPASS MODE by setting SYSCLKSEL = 0.    */
/* 2. Program RDRATIO, M, and RDBYPASS in CGCR1 and CGCR2 according to your        */
/*    required settings.														   */
/* 3. Program ODRATIO and OUTDIVEN in CGCR4 according to your required settings.   */
/* 4. Write 0806h to the INIT field of CGCR3.									   */
/* 5. Set PLL_PWRDN = 0.														   */
/* 6. Wait 4 ms for the PLL to complete its phase-locking sequence.				   */
/* 7. Place the clock generator in its PLL MODE by setting SYSCLKSEL = 1.		   */
/* ------------------------------------------------------------------------------  */
/* Note: This is a suggested sequence. It is most important to have all 		   */ 
/* programming done before the last step to place the clock generator in PLL MODE. */
/* =============================================================================== */
void InitSystem(void)
{
	Uint16 i;
	
	/*Clock Configuration Register 2 (CCR2) - Section 1.4.4.6 */
    CONFIG_MSW = 0x0; /* System Clock Generator is in Bypass Mode */

#if  (PLL_100M == 1)
	/* CGCR2 - Section 1.4.4.2 */
    PLL_CNTL2 = 0x8000; /* Bypass reference divider */
    /* CGCR4 - Section 1.4.4.4 */
    PLL_CNTL4 = 0x0000; /* Bypass output divider */
    /* CGCR3 - Section 1.4.4.3 */
    PLL_CNTL3 = 0x0806; /* initialization bits */
    /* CGCR1 - Section 1.4.4.1 */
    /* PLL power up. PLL Multiplier M = 1000 */
    PLL_CNTL1 = 0x8BE8; //PG1.4: 0x82FA;

#elif (PLL_12M == 1)
    PLL_CNTL2 = 0x8000;
    PLL_CNTL4 = 0x0200;
    PLL_CNTL3 = 0x0806;
    PLL_CNTL1 = 0x82ED;

#elif (PLL_98M == 1)    
    PLL_CNTL2 = 0x8000;
    PLL_CNTL4 = 0x0000;
    PLL_CNTL3 = 0x0806;
    PLL_CNTL1 = 0x82ED;

#elif (PLL_40M == 1)        
    PLL_CNTL2 = 0x8000;
    PLL_CNTL4 = 0x0300;
    PLL_CNTL3 = 0x0806;
    PLL_CNTL1 = 0x8262;    
#endif

    while ( (PLL_CNTL3 & 0x0008) == 0);
    
	/*Clock Configuration Register 2 (CCR2) - Section 1.4.4.6 */
    CONFIG_MSW = 0x1; /* System Clock Generator is in PLL Mode */

    /* Peripheral Clock Gating Configuration Register 1 (PCGCR1) - Section 1.5.3.2.1 */
    IDLE_PCGCR = 0x0020; /* System clock and other clocks active */
    					 /* According to Table 1-24 bit 5 should be always set to 1 */
    /* Peripheral Clock Gating Configuration Register 2 (PCGCR2) - Section 1.5.3.2.1 */
    IDLE_PCGCR_MSW = 0x007D; /* Enable SAR clock */
    
	/* Peripheral Software Reset Counter Register (PSRCR) - Section 1.7.5.1 */
    PER_RSTCOUNT = 0x08; /* Software reset signals asserted after 2 clock cycles */
    					 /* NOTE: p.75 states this value must be at least 0x08   */
    /* Peripheral Reset Control Register (PRCR) - Section 1.7.5.2 */
    PER_RESET = 0x00FF; /* Reset ALL peripherals */
    
    for (i=0; i< 0xFFFF; i++);
}

/* ========================= Configure External Busses ==========================  */
/* ------------------------------------------------------------------------------  */
/* For more info see SPRUFX5D - Section 1.7.3.1									   */
/* =============================================================================== */
void ConfigPort(void)
{
    Int16 i;
    
    /* External Bus Selection Register (EBSR) - Section 1.7.3.1 */
    PERIPHSEL0 = 0x6900; /* PPMODE = 110 - Mode 6 */
    					 /* SP1MODE = 10 - Mode 2 */
						 /* SP0MODE = 01 - Mode 1 */
						 
    for (i=0; i< 0xFFF; i++);
}

void SYS_GlobalIntEnable(void)
{
    asm(" BIT (ST1, #ST1_INTM) = #0");
}

void SYS_GlobalIntDisable(void)
{
    asm(" BIT (ST1, #ST1_INTM) = #1");
}
