/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

#include "stdio.h"
#include "usbstk5515.h"
#include "usbstk5515_gpio.h"
#include "usbstk5515_i2c.h"

extern void circbuffconfig();

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  main( )                                                                 *
 *                                                                          *
 * ------------------------------------------------------------------------ */
main( void )
{
	/* Initialize BSL */
    SYS_EXBUSSEL = 0x6100;
    USBSTK5515_init( );
    
    while(1)
    {
    	circbuffconfig();		// this function implements the linear buffer
   	}	
    
    return 0;
}
