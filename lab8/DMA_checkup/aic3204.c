/*
 * ECE5655
 * Sean O'Brien
 */

#include "aic3204.h"
#include "usbstk5515.h"
#include "usbstk5515_gpio.h"
#include "usbstk5515_i2c.h"

// Polling Masks
#define AIC3204_I2C_ADDR 0x18
#define XmitL 0x10
#define XmitR 0x20
#define RcvR 0x08
#define RcvL 0x04

// Function Prototypes
//static Int16 AIC3204_rget(Uint16 regnum, Uint16* regval);
static Int16 AIC3204_rset(Uint16 regnum, Uint16 regval);

// Sampling rate variable
extern short fs;

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _AIC3204_rget(regnum, regval)                                           *
 *                                                                          *
 *      Return value of codec register regnum                               *
 *                                                                          *
 * ------------------------------------------------------------------------ */
 /*
static Int16 AIC3204_rget(Uint16 regnum, Uint16* regval)
{
    Int16 retcode = 0;
    Uint8 cmd[2];

    cmd[0] = regnum & 0x007F;       // 7-bit Device Address
    cmd[1] = 0;

    retcode |= USBSTK5515_I2C_write(AIC3204_I2C_ADDR, cmd, 1);
    retcode |= USBSTK5515_I2C_read(AIC3204_I2C_ADDR, cmd, 1);

    *regval = cmd[0];
    USBSTK5515_wait(10);
    return retcode;
}
*/
/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _AIC3204_rset(regnum, regval)                                           *
 *                                                                          *
 *      Set codec register regnum to value regval                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */
static Int16 AIC3204_rset(Uint16 regnum, Uint16 regval)
{
    Uint8 cmd[2];
    cmd[0] = regnum & 0x007F;       // 7-bit Device Address
    cmd[1] = regval;                // 8-bit Register Data

    return USBSTK5515_I2C_write(AIC3204_I2C_ADDR, cmd, 2);
}

void AIC3204_Init(void)
{
	/* Define sampling rate parameters */
	unsigned char pll_dh, pll_dl, madc, mdac, nadc, ndac;

	/* Initialize BSL */
    USBSTK5515_init();
	
	/* Configure Serial Bus */
    SYS_EXBUSSEL |= 0x0100;  // Configure Serial bus 0 for I2S0
	
	/* Set Sampling Rate */
	if(fs == AIC3204_FS_44_1KHZ)
	{
		// PLL D = 560
		pll_dh = 0x02;
		pll_dl = 0x30;

		// MDAC & MACC = 3
		madc = 0x03;
		mdac = 0x03;

		// NDAC & NADC = 5
		nadc = 0x05;
		ndac = 0x05;
	}
	else // 8, 16, 24, 32, 48, 96 KHz
	{
		// PLL D = 1680
		pll_dh = 0x06;
		pll_dl = 0x90;

		switch(fs) {
			case AIC3204_FS_8KHZ:
				madc = 0x0C;
				mdac = 0x0C;
				break;
			case AIC3204_FS_16KHZ:
				madc = 0x06;
				mdac = 0x06;
				break;
			case AIC3204_FS_24KHZ:
				madc = 0x04;
				mdac = 0x04;
				break;
			case AIC3204_FS_32KHZ:
				madc = 0x03;
				mdac = 0x03;
				break;
			case AIC3204_FS_48KHZ:
				madc = 0x02;
				mdac = 0x02;
				break;
			case AIC3204_FS_96KHZ:
				madc = 0x01;
				mdac = 0x01;
				break;
		}

		// NDAC & NADC = 7
		nadc = 0x07;
		ndac = 0x07;
	}
     
    /* Configure AIC3204 */
    AIC3204_rset( 0, 0 );      // Select page 1
    AIC3204_rset( 1, 1 );      // Reset codec
    AIC3204_rset( 0, 1 );      // Point to page 1
    AIC3204_rset( 1, 8 );      // Disable crude AVDD generation from DVDD
    AIC3204_rset( 2, 1 );      // Enable Analog Blocks, use LDO power
    AIC3204_rset( 0, 0 );

    /* PLL and Clocks config and Power Up  */
    AIC3204_rset(27, 0x0D);			// BCLK and WCLK is set as o/p to AIC3204(Master)
    AIC3204_rset(28, 0x00);			// Data ofset = 0
    AIC3204_rset(4, 3);				// PLL setting: PLLCLK <- MCLK, CODEC_CLKIN <-PLL CLK
    AIC3204_rset(6, 0x07);			// Set PLL J
    AIC3204_rset(7, pll_dh);		// PLL setting: D HI_BYTE(5:0)
    AIC3204_rset(8, pll_dl);		// PLL setting: D LO_BYTE(7:0)
    AIC3204_rset(30, 0x88);			// For 32 bit clocks per frame in Master mode ONLY
									// BCLK=DAC_CLK/N =(12288000/8) = 1.536MHz = 32*fs
    AIC3204_rset(5, 0x91);			//PLL setting: Power up PLL, P=1 and R=1
    AIC3204_rset(13, 0x00);			// DOSR Hi_Byte(1:0) = 0
    AIC3204_rset(14, 0x80);			// DOSR Lo_Byte(7:0) = 128
    AIC3204_rset(20, 0x80);			// AOSR (7:0) = 128
    AIC3204_rset(11, 0x80 | ndac);  // Power up NDAC and set NDAC value
    AIC3204_rset(12, 0x80 | mdac);  // Power up MDAC and set MDAC value
    AIC3204_rset(18, 0x80 | nadc);  // Power up NADC and set NADC value
    AIC3204_rset(19, 0x80 | madc);  // Power up MADC and set MADC value
   
	/* DAC ROUTING and Power Up */
    AIC3204_rset( 0, 1 );      // Select page 1
    AIC3204_rset( 0x0c, 8 );   // LDAC AFIR routed to HPL
    AIC3204_rset( 0x0d, 8 );   // RDAC AFIR routed to HPR
    AIC3204_rset( 0, 0 );      // Select page 0
    AIC3204_rset( 64, 2 );     // Left vol=right vol
    AIC3204_rset( 65, 0 );     // Left DAC gain to 0dB VOL; Right tracks Left
    AIC3204_rset( 63, 0xd4 );  // Power up left,right data paths and set channel
    AIC3204_rset( 0, 1 );      // Select page 1
    AIC3204_rset( 0x10, 0 );   // Unmute HPL , 0dB gain
    AIC3204_rset( 0x11, 0 );   // Unmute HPR , 0dB gain
    AIC3204_rset( 9, 0x30 );   // Power up HPL,HPR
    AIC3204_rset( 0, 0 );      // Select page 0
    USBSTK5515_wait( 100 );    // wait
    
    /* ADC ROUTING and Power Up */
    AIC3204_rset( 0, 1 );      // Select page 1
    AIC3204_rset( 0x33, 0x00 );// Disable MICBIAS
    AIC3204_rset( 0x34, 0x10 );// STEREO 1 Jack
		                       // IN2_L to LADC_P through 10 kohm
    AIC3204_rset( 0x37, 0x10 );// IN2_R to RADC_P through 10 kohm
    AIC3204_rset( 0x36, 0x40 );// CM_1 (common mode) to LADC_M through 10 kohm
    AIC3204_rset( 0x39, 0x40 );// CM_1 (common mode) to RADC_M through 10 kohm
    AIC3204_rset( 0x3b, 0 );   // MIC_PGA_L unmute
    AIC3204_rset( 0x3c, 0 );   // MIC_PGA_R unmute
    AIC3204_rset( 0, 0 );      // Select page 0
    AIC3204_rset( 0x51, 0xc0 );// Powerup Left and Right ADC
    AIC3204_rset( 0x52, 0 );   // Unmute Left and Right ADC
    
    AIC3204_rset( 0, 0 );    
    USBSTK5515_wait( 100 );  // Wait
}

void input_sample(short *l_chan, short *r_chan)
{
	/* Read Digital audio input */
        while((RcvR & I2S0_IR) == 0);  // Wait for receive interrupt to be pending
	*l_chan = I2S0_W0_MSW_R;
	*r_chan = I2S0_W1_MSW_R;
}

void output_sample(short l_chan, short r_chan)
{
	while((XmitR & I2S0_IR) == 0); // Wait for transmit interrupt to be pending
	I2S0_W0_MSW_W = l_chan;  // 16 bit left channel transmit audio data
    I2S0_W1_MSW_W = r_chan;  // 16 bit right channel transmit audio data
}
