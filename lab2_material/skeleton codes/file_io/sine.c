
// ****************************************************************
// Description: This application uses Probe Points to obtain input
// (a sine wave).
// Filename: Sine.c
// ****************************************************************

#include <stdio.h>
#include "usbstk5515.h"

// Declare the function
static void dataInput();             // dummy function to be used with ProbePoint

void main()
{
  puts("SineWave example started.\n");
      
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

