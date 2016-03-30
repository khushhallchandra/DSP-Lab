/*
 * ECE5655
 * Sean O'Brien
 */

#ifndef AIC3204_H_
#define AIC3204_H_

// Sampling rates
enum {AIC3204_FS_8KHZ,
	  AIC3204_FS_16KHZ,
	  AIC3204_FS_24KHZ,
	  AIC3204_FS_32KHZ,
	  AIC3204_FS_44_1KHZ,
	  AIC3204_FS_48KHZ,
	  AIC3204_FS_96KHZ};

// Function Prototypes
void AIC3204_Init(void);
void input_sample(short *l_chan, short *r_chan);
void output_sample(short l_chan, short r_chan);

#endif /*AIC3204_H_*/
