

.include "m644Adef.inc"
	
.text
.org 0x00

prologue:	
	ldi XL, lo8 (RAMEND)
	ldi XH, hi8 (RAMEND)

;;; init stack
	out SPL, XL
	out SPH, XH

	sbi DDRB, PB0

	clr r20
cleanup:	
	st -x, r20
	cpi XH, 0x00
	brne cleanup

	;; set PB0
	sbi PORTB, PB0	

	;;; init the UART0
	ldi r17, (1<<TXEN0)
	sts UCSR0B, r17

	ldi r17, (1<<UCSZ01) | (1<<UCSZ00)
	sts UCSR0C, r17

	ldi r17, lo8 (103)
	sts UBRR0L, r17
	clr r17
	sts UBRR0H, r17

	sbi DDRD, PD0
	nop
	nop
;; loop:
;; 	rjmp loop
