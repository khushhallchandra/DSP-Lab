#include "stdio.h"
#include "usbstk5515.h"
#include "intrindefs.h"

Int16 x[100]; 
Int16 y[100]; 

main(void)
{
	USBSTK5515_init( );
	
	for(int i=4000;i<4100;i++)
	{
		x[i-4000]=i;
	}

/***************************************
*****Your conversion code goes here***** 
***************************************/

	// Your code should return, in y, the values in x, expressed such that
	// they occupy fully the available 16 bit range provided by the datatype
	// Int16.

	return 0;
}

