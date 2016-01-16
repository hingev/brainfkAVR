

brainfuck compiler for AVRs
===========================

**BFC** - well, the title is pretty self explanatory. It compiles **bf** instructions.

## How to compile ##

Make sure you have `avr-libc` and `make`, `avrdude`.
Have your **brainfuck** code in `src/src.bf` (terminal arguments not added yet).
Then do:

    $ cd src
    $ make clean all
    
It compiles `src.bf` into `out.bin`, which `objcopy` turns into the `out.hex` file.
Change programmer settings (`AVRDUDE_TARGET` and `PROGRAMMER`) in `src/Makefile` and do

    $ make flash

If you'd like to see what the brainfuck commands were turned to in assembly, do

	$ make bfdisasm

And take a look inside the `bfdisasm` file. It will look something like this:

	[
		68:	0c 91       	ld	r16, X
		6a:	00 30       	cpi	r16, 0x00	; 0
		6c:	11 f4       	brne	.+4      	;  0x72
		6e:	0c 94 5e 00 	jmp	0xbc	;  0xbc

	-
		72:	0c 91       	ld	r16, X
		74:	0a 95       	dec	r16
		76:	0c 93       	st	X, r16

	etc.



## How this works ? ##

Well.. In **bf** you have a tape of bytes. In this case, the tape is the built in **SRAM** of **AVR**.
The program navigates over **RAM** using `>` and `<`.
The `+` and `-` just do `INC` and `DEC`.

~~For simplicity, all jumps and loads were done directly (mostly)~~.

Change in plans. 
In the boot time, the starting address for the 'tape' is loaded in the **X** register. After what, all calls are done indirectly. So for example `+` will just do

```assembly
ld r16, X
inc r16
st x, r16
```

While the `>` and `<` just do a load with **post/pre increment/decrement**.

```assembly
ld r2, X+
```

or

```assembly
ld r2, -X
```

In the **/avr** directory, there is the source code of [prologue](https://github.com/geohhot/brainfkAVR/blob/master/src/avr/crt0_for_bfc.S) and [output communication stuff](https://github.com/geohhot/brainfkAVR/blob/master/src/avr/crt_for_bfc.S).

### What ~~works~~ is implemented ? ###

Not fully tested, but everything except `,` (input command)

### Prologue ###
Basic set-up of **UART0** in 9600 baud.
All the usable **RAM** gets zeroed.

### The other part ###
Sends the character, waits for **UART** to finish.

### TODO ###
Well, maybe implement input from **UART**, and some optimizations.

In this version the optimization level is low (like, reallly low). But maybe in future versions (if any) it will be fixed.
