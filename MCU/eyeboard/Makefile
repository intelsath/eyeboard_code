GCCFLAGS=-g -Os -Wall -mmcu=atmega328p 
LINKFLAGS=-Wl,-u,vfprintf -lprintf_flt -Wl,-u,vfscanf -lscanf_flt -lm
AVRDUDEFLAGS=-c avr109 -p m328p -b 115200 -P /dev/ttyUSB0
LINKOBJECTS=../libs/uart.o

all:	eog-upload

eog.hex:	eog.c
	make -C ../libs
	avr-gcc ${GCCFLAGS} ${LINKFLAGS} -o eog.o eog.c ${LINKOBJECTS}
	avr-objcopy -j .text -O ihex eog.o eog.hex
	
eog.ass:	eog.hex
	avr-objdump -S -d eog.o > eog.ass
	
eog-upload:	eog.hex
	avrdude ${AVRDUDEFLAGS} -U flash:w:eog.hex:a
