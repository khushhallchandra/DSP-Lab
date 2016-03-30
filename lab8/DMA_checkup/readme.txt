A template project for audio processing applications using the C5515 eZDSP kit.
This project uses the small memory model in order to support hardware-accelerated 
FFTS. The system is set up using register programming. In each step appropriate
references to relevant documentation are given as comments. Generally, the project
has not been extensively test and has possibly significant bugs. It is provided to
the community so a more robust and useful template can be developed with input from
those interest. Also note, that in no case is the code optimal in terms of memory
and/or performance.

If you have any comments, suggestions, etc, contact me.

Elias Kokkinis (ekokkinis@upatras.gr)

Parts of the project are based on:
- The system initialization function is based on the C5515 audio filter example.
  (http://code.google.com/p/c5505-ezdsp/)
  
- The SAR and switch functionality provided by Spectrum Digital's example code.

- The AIC3204 initialization by Sean O' Brien.

Notes:
- Two wrapper functions have been created to allow simple FFT/IFFT implementation
  and conversion between complex (32-bit packed) and real numbers (16-bit).

- You have to compile the following project: 
  C:\Program Files\Texas Instruments\ccsv4\emulation\boards\usbstk5515_v1\lib
  using small memory model and 16 bit pointer math.
  
- In order to support higher sampling rates you have to turn on optimizations.

LICENSE:
--------
Permission to use, copy, modify, and/or distribute this software for any 
purpose with or without fee is hereby granted, provided that the above 
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES 
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF 
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY 
SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER 
RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, 
NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE 
USE OR PERFORMANCE OF THIS SOFTWARE.