#include "stdio.h"
#include "usbstk5515.h"
#include "fdacoefs_int.h"

extern void linearbuff();

Int16 *inPtr; 		//pointer to input sample
Int16 *outPtr; 		//pointer to output
Int16 *coeff;		//pointer to the coefficients
Int16 input;
Int16 output;
Int16 input_syn[40];
Int16 out[40];


main(void)
{
	int i;
    SYS_EXBUSSEL = 0x6100;
    USBSTK5515_init( );
    
//    input_syn = coefs;
    coeff = &coefs[0]; 	//coefs is coefficient of impulse response defined in fdacoefs_int.h
    inPtr = &input;		//inPtr is a globally declared pointer to a Int16 
    outPtr = &output;
    
    for (i=0;i<11;i++)
	{
		coefs[i]= 32767;
	}

	for (i=0;i<40;i++)
	{
			if (i<=19)
				input_syn[i]=32767;
			else
				input_syn[i]=0;
	}
    
    for(i=0; i<40;i++)
	 { 
		input = input_syn[i];
     	linearbuff();		// this function implements the linear buffer
      	out[i]=output;
	 
	}
    /* Disble I2S */
    I2S0_CR = 0x00;
    return 0;
}

/*
 _____ _____     ______  ___________   _       _      
|_   _|_   _|    |  _  \/  ___| ___ \ | |     | |     
  | |   | |______| | | |\ `--.| |_/ / | | __ _| |__   
  | |   | |______| | | | `--. \  __/  | |/ _` | '_ \  
  | |  _| |_     | |/ / /\__/ / |     | | (_| | |_) | 
  \_/  \___/     |___/  \____/\_|     |_|\__,_|_.__/  IIT Bombay
*/
