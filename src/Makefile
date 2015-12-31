
SRC = bfc

AVRDUDE_TARGET = m644
PROGRAMMER     = usbtiny

clean:
	rm -rf *~ out.bin out.hex

all: compile run

compile:
	gcc -L. $(SRC).c -o $(SRC)

run:
	./$(SRC)

disasm:
	avr-objcopy -I binary -O ihex out.bin out.hex
	avr-objdump -D --architecture=avr out.hex

flash:
	avrdude -p $(AVRDUDE_TARGET) -c $(PROGRAMMER) -B 1 -v \
        -U flash:w:out.hex

reset:
	avrdude -p $(AVRDUDE_TARGET) -c $(PROGRAMMER) -B 1 -v \
	-E reset

get_crts:
	make -C avr/. PRG=crt0_for_bfc clean all
	cp avr/crt0_for_bfc.bin .
	make -C avr/. PRG=crt_for_bfc clean all
	cp avr/crt_for_bfc.bin .

