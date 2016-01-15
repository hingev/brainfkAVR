
SRC = bfc

AVRDUDE_TARGET = m644
PROGRAMMER     = usbtiny

clean:
	rm -rf *~ out.bin out.hex

all: get_crts compile run objcopy

compile:
	gcc -L. $(SRC).c -o $(SRC)

run:
	./$(SRC)

objcopy:
	avr-objcopy -I binary -O ihex out.bin out.hex

disasm: run objcopy
	avr-objdump -D --architecture=avr out.hex

bfdisasm: run objcopy
	avr-objdump -D --architecture=avr out.hex > disasm
	python3 bfdisasm.py > bfdisasm

flash:
	avrdude -p $(AVRDUDE_TARGET) -c $(PROGRAMMER) -B 1 -v \
        -U flash:w:out.hex

debug:
	make reset
	python3 read_putty.py

reset:
	avrdude -p $(AVRDUDE_TARGET) -c $(PROGRAMMER) -B 1 -v \
	-E reset

get_crts:
	make -C avr/. PRG=crt0_for_bfc clean all
	cp avr/crt0_for_bfc.bin crt_0.bin
	make -C avr/. PRG=crt_for_bfc clean all
	cp avr/crt_for_bfc.bin crt_t0.bin

