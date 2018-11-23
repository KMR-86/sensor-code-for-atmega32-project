avr-gcc -g -Os -mmcu=atmega32 -c blink.c
avr-gcc -g -mmcu=atmega32 -o blink.elf blink.o
avr-objcopy -j .text -j .data -O ihex blink.elf blink.hex
avr-size --format=avr --mcu=atmega32 blink.elf
avrdude -c usbasp -p m32 -P /dev/ttyACM0 -B10 -U flash:w:blink.hex -F
