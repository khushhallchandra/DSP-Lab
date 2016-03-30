#include "dma_setup.h"

/* For information see SPRUFT2A, Section 2.13, p.18 */
void DMA0_setup(void) {
	
	Uint16 register_value;
	Uint32 dma_address; 

	/* Step 3 - Clear interrupt flags */
	DMA_IFR = 0xFFFF; /* Clear ALL DMA interrupt flags */
    IFR0 = 0x0100;    /* Clear DMA CPU interrupt flag */
    
    /* Step 4 - Enable interrupts */
    DMA_IER = 0x000F; /* Enable interrupts for DMA0CH0-DMA0CH3 */
    
	/* Step 5 - Setup sync event */
	register_value = DMA0_CESR1;
	DMA0_CESR1 = register_value | 0x0101; /* Set CH1, CH0 sync event to I2S0 transmit */
	register_value = DMA0_CESR2;
	DMA0_CESR2 = register_value | 0x0202; /* Set CH3, CH2 sync event to I2S0 receive*/

	/* Step 6 - Channel source addresses */
	DMA0_CH2_SSAL = 0x2828;//I2S0_RXLT0; /* 16 LSBs of I2S0 left receive */
	DMA0_CH2_SSAU = 0x0000;
	
	DMA0_CH3_SSAL = 0x282C;//I2S0_RXRT0; /* 16 LSBs of I2S0 right receive */
	DMA0_CH3_SSAU = 0x0000;
	
	dma_address = convert_address(DMA_OutL);       /* convert address */
	DMA0_CH0_SSAL = (Uint16)dma_address;          /* keep LSBs */
	DMA0_CH0_SSAU = 0xFFFF & (dma_address >> 16); /* keep MSBs */
	
	dma_address = convert_address(DMA_OutR);       /* convert address */
	DMA0_CH1_SSAL = (Uint16)dma_address;
	DMA0_CH1_SSAU = 0xFFFF & (dma_address >> 16);
	
	/* Step 7 - Channel destination addresses*/
	dma_address = convert_address(DMA_InpL);
	DMA0_CH2_DSAL = (Uint16)dma_address;
	DMA0_CH2_DSAU = 0xFFFF & (dma_address >> 16);
	
	dma_address = convert_address(DMA_InpR);
	DMA0_CH3_DSAL = (Uint16)dma_address;
	DMA0_CH3_DSAU = 0xFFFF & (dma_address >> 16);
	
	DMA0_CH0_DSAL = 0x2808;//I2S0_TXLT0;
	DMA0_CH0_DSAU = 0x0000;
	
	DMA0_CH1_DSAL = 0x280C;//I2S0_TXRT0;
	DMA0_CH1_DSAU = 0x0000;
	
	/* Step 8 - DMA Transfer Length */
	/* Note the following (Sections 2.9, 4.3):                          */
	/* - DMA transfer length is specified in bytes.                     */
	/* - DMA transfer length in ping/pong mode is half the length of    */
	/*   the TCR1 register.                                             */
	/* - Ping/pong buffers should occupy contiguous memory spaces and   */
	/*   it is recommended to setup a buffer double the size of the     */
	/*   intended one to ensure this.                                   */
	/* In order to transfer _AUDIO_IO_SIZE_ 16-bit samples in ping/pong */
	/* mode, we specify the transfer length as 2*2*AUDIO_IO_SIZE.       */
	/* According to PINGPONG PING_PONG_SIZE is either AUDIO_IO_SIZE or  */
	/* 2*AUDIO_IO_SIZE and hence it is calculated in audio_setup.h. Here*/
	/* we use 2*PING_PONG_SIZE to ensure complete transfer of 16-bit data.*/
    DMA0_CH0_TCR1 = 2*PING_PONG_SIZE;
    DMA0_CH1_TCR1 = 2*PING_PONG_SIZE;
    DMA0_CH2_TCR1 = 2*PING_PONG_SIZE;
    DMA0_CH3_TCR1 = 2*PING_PONG_SIZE;
    
    /* Step 9 - Configure options */
    DMA0_CH2_TCR2 = 0x3081;
    DMA0_CH3_TCR2 = 0x3081;
    DMA0_CH0_TCR2 = 0x3201;
    DMA0_CH1_TCR2 = 0x3201;
}

void DMA0_enable_CH(Uint16 channel_number) {
	
	Uint16 register_value;
	
	switch (channel_number) {
		case 0:	         
    		register_value = DMA0_CH0_TCR2;
    		DMA0_CH0_TCR2 = register_value | 0x8004;
    		break;
    	case 1:
    		register_value = DMA0_CH1_TCR2;
    		DMA0_CH1_TCR2 = register_value | 0x8004;
    		break;
    	case 2:
    		register_value = DMA0_CH2_TCR2;
    		DMA0_CH2_TCR2 = register_value | 0x8004;
    		break;
    	case 3:
    		register_value = DMA0_CH3_TCR2;
    		DMA0_CH3_TCR2 = register_value | 0x8004;
    		break;
	}
    
}

interrupt void DMA_ISR(void)
{
	Uint16 register_value1, register_value2;
	
	/* Clear CPU DMA interrupt */
	register_value1 = IFR0;
	IFR0 = register_value1;
	   
	/* Read DMA interrupt flags */
    register_value1 = DMA_IFR;
    
    /* Channels 0-1, output */
    if (register_value1 & 0x0003) {
    	
    	register_value2 = DMA0_CH0_TCR2;
    	if (register_value2 & 0x0002) {
    		PingPongFlagOutL = 1;
    	} else {
    		PingPongFlagOutL = 0;
    	}
    	
    	register_value2 = DMA0_CH1_TCR2;
    	if (register_value2 & 0x0002) {
    		PingPongFlagOutR = 1;
    	} else {
    		PingPongFlagOutR = 0;
    	}
 	    	    
    	/* Clear CH0-1 interrupts */
    	DMA_IFR = 0x0003; 
    }
    
    /* Channels 2-3, input */
    if (register_value1 & 0x000C) {
    	
    	register_value2 = DMA0_CH2_TCR2;
    	if (register_value2 & 0x0002) {
    		PingPongFlagInL = 1;
    	} else {
    		PingPongFlagInL = 0;
    	}
    	
    	register_value2 = DMA0_CH3_TCR2;
    	if (register_value2 & 0x0002) {
    		PingPongFlagInR = 1;
    	} else {
    		PingPongFlagInR = 0;
    	}
    	
    	/* Clear CH2-3 interrupts */
    	DMA_IFR = 0x000C; 
    }

}

/* Change word address to byte address and add DARAM offset for DMA */
Uint32 convert_address(Int16 *buffer) {
	
	Uint32 dma_address;
	
	dma_address = (Uint32)buffer;
	dma_address = (dma_address<<1) + 0x010000;
	
	return dma_address;
}
