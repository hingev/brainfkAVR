
PRG = crt_for_bfc
#PRG = crt0_for_bfc

MCU = atmega644a

LIBS = 

AVRDUDE_TARGET = m644
PROGRAMMER     = usbtiny

PUTTYSESION = TTY0_9600

all: clean gasm

reset:
	avrdude -p $(AVRDUDE_TARGET) -c $(PROGRAMMER) -B 1 -v \
	-E reset

clean:
	rm -rf $(PRG).o

%.o: %.S
#	@echo "Assembling.."
	avr-as -mmcu=$(MCU) -o $@ $<
#	avr-as -mmcu=$(MCU) -o $(PRG).o $(PRG).S

# $(PRG).o:
# 	@echo "Assembling 1.."
# 	avr-as -mmcu=$(MCU) -o $@ $(basename $@).S

avr-as: $(PRG).o

size:
	@echo "Total size"
	@avr-size $(PRG).elf
	@echo "Size of output"
	@avr-size $(PRG).ihex

gasm: avr-as stuff size

flash: $(PRG).ihex
	avrdude -p $(AVRDUDE_TARGET) -c $(PROGRAMMER) -B 1 -v \
         -U flash:w:$(PRG).ihex

objdump:
	avr-objdump -x --syms $(PRG).o 

stuff:
	@echo "Linking .."
	avr-ld -o $(PRG).elf $(PRG).o
#avr-objcopy --output-target=ihex $(PRG).elf $(PRG).ihex
	@echo "Objcopy .."
	avr-objcopy -j .text -O ihex   $(PRG).elf $(PRG).ihex
	avr-objcopy -j .text -O binary $(PRG).elf $(PRG).bin
#	avr-objcopy -w -j * -O ihex $(PRG).elf $(PRG)_eeprom.ihex
#	avr-objcopy -j bleh -O ihex $(PRG).elf $(PRG).ihex

eeprom:
	avr-objcopy -j .data -O ihex $(PRG).elf $(PRG)_eeprom.ihex
	avr-size $(PRG)_eeprom.ihex

term:
	putty -load $(PUTTYSESION)

disasm:
	avr-objdump -D --architecture=avr $(PRG).ihex
