;****************************************************************
;circular buffering

      .ARMS_off                     ;enable assembler for ARMS=0
      .CPL_on                      	;enable assembler for CPL=1
      .mmregs                       ;enable mem mapped register names

	.global _circbuffconfig		; Circular Buffer Function Name

; This is a skeleton project for initializing circular buffer

	.data							;data section
									;section where all the data is stored 

buff_length	.set 5  					;length of the impulse response ex: length 5 filter

	.align 16			
firbuff	.space 16*buff_length		; allocating buffer space
									; Each Coefficient of impulse response
									; is represented in 16 Bits
									; 16 times the Filter Length
									
	.text							;this section contains the code 

_circbuffconfig					; Circular Buffering function definition


;*************************************************
;***** Your AR1 configuration code goes here *****
;*************************************************
 
 	RPT #buff_length*3-1
 	ADD #5, *AR1+                   ; This instruction assumes that AR1 is configured to be circularly rotating over the buffer 'firbuff'
 	                                ; Your AR1 configuration code above should take care of this.

    RET
