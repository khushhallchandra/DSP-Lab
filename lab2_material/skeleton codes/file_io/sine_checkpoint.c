
// ****************************************************************
// Description: This application uses Probe Points to obtain input
// (a sine wave). It then takes this signal, and applies a gain
// factor to it.
// Filename: sine_checkpoint.c
// ****************************************************************

#include <stdio.h>
#include "sine.h"
#include "usbstk5515.h"

// Define some functions 
static void processing();            // process the input and generate output 
static void dataInput();             // dummy function to be used with ProbePoint
static void dataOutput();            // dummy function to be used with ProbePoint

Int16 input[BUFFSIZE];
Int16 output[BUFFSIZE];
void main()
{
  puts("SineWave example started.\n");
      
    while(TRUE) // loop forever
    {       
        /*  Read input data using a probe-point connected to a host file. */
       dataInput();
       
       /* Apply the gain to the input to obtain the output */
       processing();

       /*  Write output data to a graph connected through a probe-point. */
       dataOutput();
    }
}

/*
 * FUNCTION:    Apply signal processing transform to input signal 
 *               to generate output signal
 * PARAMETERS:     BufferContents struct containing input/output arrays of size BUFFSIZE
 * RETURN VALUE:   none.
 */

static void processing()
{
    Int16 size = 0;

    while(size++ < BUFFSIZE){
        output[size] = input[size] * GAIN;  // apply gain to input
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


static void dataOutput()
{
   /* do data I/O */
   return;
}

