

brainfuck compiler for AVRs
===========================

**BFC** - well, the title is pretty self explanatory. It compiles **bf** instructions.

## How this works ? ##

Well.. In **bf** you have a tape of bytes. In this case, the tape is the built in **SRAM** of **AVR**.
The program navigates over **RAM** using `>` and `<`.
The `+` and `-` just do

    	* Load from data space
    	* Increment / decrement
    	* Store to data space

For simplicity, all jumps and loads were done directly (mostly).
In the **/avr** directory, there is the source code of prologue and output communication stuff.

### Prologue ###
Basic set-up of **UART0** in 9600 baud.
All the usable **RAM** gets zeroed.

### The other part ###
Sends the character, waits for **UART** to finish.

In this version the optimization level is low (like, reallly low). But maybe in future versions (if any) it will be fixed.

