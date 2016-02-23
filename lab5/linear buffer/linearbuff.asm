      .ARMS_off                     ;enable assembler for ARMS=0
      .CPL_on                      	;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names

	.global _linearbuff				; Linear Buffer Function Declaration 
	.global _inPtr					; Pointer Contianing the Address of Input
	.global _outPtr					; Pointer Contianing the Address of Output		
	.global _coeff					; Pointer Contianing the First Address of Coefficient Array
	
	
; This is a skeleton project for initializing linear buffer

	.data							;data section
									;section where all the data is stored 
									
FIR_len	.set 12						;length of the impulse response ex: 12 length filter
									;(Change the length according to given impulse response)	
	.align 16
			
firbuff	.space 16*FIR_len			; allocating buffer space, "firbuff" is the address of the first location of buffer space
									; Each Coefficient of impulse response
									; is represented in 16 Bits
									; 16 times the Filter Length
									

oldindex	.word  0				; Allocate storage to save oldindex (Will be used in Circular buffer)
									; (defines where next sample has to be put in buffer)
									

	.text							;this section contains the code 

_linearbuff							; Linear Buffering function definition

; section 1: Loading addresses of pointers (inPtr, outPtr & coeff) in Extended Registers 
	
	mov dbl(*(#_inPtr)),XAR6		; XAR6 contains address to input
	mov dbl(*(#_outPtr)),XAR7		; XAR7 contains address to Output;
	mov dbl(*(#_coeff)), XAR5 		; XAR5 contains address to First Address of Coefficient Array;
 

; section 2: Start code for linear buffering from here
 
	mov #(firbuff+FIR_len-2),AR3	 	; AR3 points to second last location of buffer space 
	mov #(firbuff+FIR_len-1),AR4		; AR4 points to last location of buffer space 


	RPT #(FIR_len-2)					; Repeat the next instruction for (FIR_len -1) times
	MOV *AR3-,*AR4-;					: Moving the value pointed by AR3 to location pointed by AR4, and decremeting pointers by one location
										; After this loop AR4 will be pointing to the first location ("firbuff") of buffer space 		
										; Shifting operation is facilitated by above two instructions
										
										
	MOV *AR6,*AR4;						; Now value pointed by AR6 is stored in first location ("firbuff") of buffer space

; section 3: Convolution block start from here ....

	mov #0,AC0;							;Before performing the MAC operation always clear the contents of the accumulator.
	
	RPT #FIR_len-1						; Repeat the next instruction for "FIR_len" times
	MAC *AR5+,*AR4+,AC0					; Multiply and accumulate operation
										; AC0= AC0 + (value at Address(AR5) x value at Address(AR4))
										; Address at AR5 and AR4 increments by one (points to the next memory location of size word,i.e, 16 bits)
													
											
	MOV HI(AC0),*AR7					; Move the higher byte of the result to the output pointer, here AR7 is containg the output address
										

	RET									; Return to the main C-program