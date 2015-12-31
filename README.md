

brainfuck compiler for AVRs
===========================

**BFC** - well, the title is pretty self explanatory. It compiles **bf** instructions.

## How to compile ##

Make sure you have `avr-libc` and `make`.
Then do:

    $ cd src
    $ make clean all
    
It compiles `src.bf` into `out.bin`. Then change programmer settings in `src/Makefile` and do

    $ make flash

## How this works ? ##

Well.. In **bf** you have a tape of bytes. In this case, the tape is the built in **SRAM** of **AVR**.
The program navigates over **RAM** using `>` and `<`.
The `+` and `-` just do `INC` and `DEC`.

For simplicity, all jumps and loads were done directly (mostly).
In the **/avr** directory, there is the source code of [prologue](https://github.com/geohhot/brainfkAVR/blob/master/src/avr/crt0_for_bfc.S) and [output communication stuff](https://github.com/geohhot/brainfkAVR/blob/master/src/avr/crt_for_bfc.S).

### What works ? ###

Not fully tested, but everything except `,` (input command)

### Prologue ###
Basic set-up of **UART0** in 9600 baud.
All the usable **RAM** gets zeroed.

### The other part ###
Sends the character, waits for **UART** to finish.


In this version the optimization level is low (like, reallly low). But maybe in future versions (if any) it will be fixed.
