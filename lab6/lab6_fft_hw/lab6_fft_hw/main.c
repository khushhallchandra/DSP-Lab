#include "data_types.h"
#include "hwafft.h"
#include "stdio.h"

#define FFT_LENGTH 8

void USBSTK5515_init(void);

Int16 x[FFT_LENGTH]={1,0,2,0,3,0,4,0};

///* --- Special buffers required for HWAFFT ---*/
#pragma DATA_SECTION(complex_buffer, "cmplxBuf");
Int32 complex_buffer[FFT_LENGTH];

#pragma DATA_SECTION(bitreversed_buffer, "brBuf");
#pragma DATA_ALIGN(bitreversed_buffer, 2*FFT_LENGTH);
Int32 bitreversed_buffer[FFT_LENGTH];

#pragma DATA_SECTION(temporary_buffer,"tmpBuf");
Int32 temporary_buffer[FFT_LENGTH];
/* -------------------------------------------*/

void do_fft(Int16 *real_data, Int16 *fft_real, Int16 *fft_imag, Uint16 scale);
void do_ifft(Int16 *fft_real, Int16 *fft_imag, Int16 *ifft_data, Uint16 scale);
Int16 realpart_fft[8],imagpart_fft[8],scale=0;

int main(void)
{
	//USBSTK5515_init();
	do_fft(x, realpart_fft, imagpart_fft, scale);
	
	/*do frequency domain processing
	     * 
	     * 
	     * Write code for magnitude calculation. (real part is stored in realpart_fft and 
		 * imaginary part is stored in imagpart_fft array)
	     * 
	     * 
		 * here*/
		 
	return 0;
}

/* ---------------- Wrapper function to implement HWAFFT ---------------- */
/* For more information see: Application Report - SPRABB6A, June 2010     */
/* Note that there are also several discussions in e2e.ti.com forums.     */
/* The appropriate functions are linked via c5515.cmd. See also:          */
/* http://e2e.ti.com/support/dsp/c5000/f/109/p/49635/176118.aspx#176118   */
/*																		  */
/* The function requires pre-allocated arrays for input data (16-bit Q15) */
/* and real and imaginray parts of the FFT.                               */
/* ---------------------------------------------------------------------- */
void do_fft(Int16 *real_data, Int16 *fft_real, Int16 *fft_imag, Uint16 scale)
{
	Uint16 i, data_selection;
	Int32 *complex_data, *bitrev_data, *temp_data, *fft_data;
	
	/* Initialize relevant pointers */
	bitrev_data  = bitreversed_buffer;
	temp_data    = temporary_buffer;
	complex_data = complex_buffer;
	
	/* Convert real data to "pseudo"-complex data (real, 0) */
	/* Int32 complex = Int16 real (MSBs) + Int16 imag (LSBs) */
	for (i = 0; i < FFT_LENGTH; i++) {
		*(complex_data + i) = ( (Int32) (*(real_data + i)) ) << 16;
	}
	
	/* Perform bit-reversing */
	hwafft_br(complex_data, bitrev_data, FFT_LENGTH);
	
	/* Perform FFT */
	if (scale) {
//		data_selection = hwafft_128pts(bitrev_data, temp_data, FFT_FLAG, SCALE_FLAG);
		data_selection = hwafft_8pts(bitrev_data, temp_data, FFT_FLAG, SCALE_FLAG);
	} else {
//		data_selection = hwafft_128pts(bitrev_data, temp_data, FFT_FLAG, NOSCALE_FLAG);
		data_selection = hwafft_8pts(bitrev_data, temp_data, FFT_FLAG, NOSCALE_FLAG);	
	}
	
	/* Return appropriate data pointer */
	if (data_selection) {
		fft_data = temp_data;
	} else {
		fft_data = bitrev_data;
	}
	
	/* Extract real and imaginary parts */
	for (i = 0; i < FFT_LENGTH; i++) {
		*(fft_real + i) = (Int16)((*(fft_data + i)) >> 16);
		*(fft_imag + i) = (Int16)((*(fft_data + i)) & 0x0000FFFF);
	}
		   	
}

/* ---------------- Wrapper function to implement HWAIFFT --------------- */
/* For more information see: Application Report - SPRABB6A, June 2010     */
/* Note that there are also several discussions in e2e.ti.com forums.     */
/* The appropriate functions are linked via c5515.cmd. See also:          */
/* http://e2e.ti.com/support/dsp/c5000/f/109/p/49635/176118.aspx#176118   */
/*																		  */
/* The function requires pre-allocated arrays for output data (16-bit Q15)*/
/* of the IFFT.							                                  */
/* ---------------------------------------------------------------------- */
void do_ifft(Int16 *fft_real, Int16 *fft_imag, Int16 *ifft_data, Uint16 scale)
{
	Uint16 i, data_selection;
	Int32 *complex_data, *bitrev_data, *temp_data, *ifft_tmp;
	
	/* Initialize relevant pointers */
	complex_data = complex_buffer;
	bitrev_data  = bitreversed_buffer;
	temp_data    = temporary_buffer;

	/* Reconstruct complex data from real and imaginary parts */
	for (i = 0; i < FFT_LENGTH; i++) {
		*(complex_data + i) = ((Int32)(*(fft_real + i)) << 16);
		*(complex_data + i) = *(complex_data + i) | ((Int32)(*(fft_imag + i)) & 0x0000FFFF);
	}
	
	/* Perform bit-reversing */
	hwafft_br(complex_data, bitrev_data, FFT_LENGTH);
	
	/* Perform IFFT */
	if (scale) {
//		data_selection = hwafft_128pts(bitrev_data, temp_data, IFFT_FLAG, SCALE_FLAG);
		data_selection = hwafft_512pts(bitrev_data, temp_data, IFFT_FLAG, SCALE_FLAG);
	} else {
//		data_selection = hwafft_128pts(bitrev_data, temp_data, IFFT_FLAG, NOSCALE_FLAG);
		data_selection = hwafft_512pts(bitrev_data, temp_data, IFFT_FLAG, NOSCALE_FLAG);	
	}
	
	/* Return appropriate data pointer */
	if (data_selection) {
		ifft_tmp = temp_data;
	} else {
		ifft_tmp = bitrev_data;
	}
	
	/* Return real part of IFFT */
	for (i = 0; i < FFT_LENGTH; i++) {
		*(ifft_data + i) = (Int16)((*(ifft_tmp + i)) >> 16); 
	}   	
}

