
// ****************************************************************
// Description: This application uses Probe Points to obtain input
// (a sine wave). It then takes this signal, and applies a gain
// factor to it.
// Filename: Sine.c
// ****************************************************************

#include <stdio.h>
#include "usbstk5515.h"
#define BUFFSIZE 256

// Define some functions  
static void dataInput();             // dummy function to be used with ProbePoint
Int16 x[BUFFSIZE];
void main()
{
  puts("Squarewave checkpoint started.\n");
      
    while(1) // loop forever
    {       
        /*  Read input data using a probe-point connected to a host file. */
       dataInput();

    }
}
 
/*
 * FUNCTION:     Read input signal and write processed output signal
 *              using ProbePoints
 * PARAMETERS: none.
 * RETURN VALUE: none.
 */
static void dataInput()
{
   /* do data I/O */
    return;
}

