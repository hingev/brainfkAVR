
.include "m644Adef.inc"
	
.text
.org 0x00

send_char:
	;; ldi r16, 'G'
	sts UDR0, r16
lloop:	
	lds r17, UCSR0A
	sbrs r17, TXC0
	rjmp lloop
	sbr r17, (1 << TXC0)
	sts UCSR0A, r17	
