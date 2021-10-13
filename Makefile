LIB        = lib/
BUILD        = build/
TARGET     = main
SERVO      = servo
BRIDGE     = bridge
LEDS       = leds
BUTTONS    = buttons
PORT       = COM6
DEVICE     = atmega2560
PROGRAMMER = wiring
BAUD       = 115200
COMPILE    = avr-gcc -Wall -Os -mmcu=$(DEVICE)

default: compile

compile: clean
	$(COMPILE) -c $(LIB)$(LEDS).c -o $(BUILD)$(LEDS).o
	$(COMPILE) -c $(LIB)$(BUTTONS).c -o $(BUILD)$(BUTTONS).o
	$(COMPILE) -c $(LIB)$(SERVO).c -o $(BUILD)$(SERVO).o
	$(COMPILE) -c $(LIB)$(BRIDGE).c -o $(BUILD)$(BRIDGE).o
	$(COMPILE) -c $(TARGET).c -o $(BUILD)$(TARGET).o
	$(COMPILE) -o $(BUILD)$(TARGET).elf $(BUILD)$(TARGET).o $(BUILD)$(LEDS).o $(BUILD)$(BUTTONS).o $(BUILD)$(SERVO).o $(BUILD)$(BRIDGE).o
	avr-objcopy -j .text -j .data -O ihex $(BUILD)$(TARGET).elf $(BUILD)$(TARGET).hex
	avr-size --format=avr --mcu=$(DEVICE) $(BUILD)$(TARGET).elf

compile2: clean
	$(COMPILE) -c $(TARGET).c -o $(BUILD)$(TARGET).o
	$(COMPILE) -c $(LIB)$(SERVO).c -o $(BUILD)$(SERVO).o
	$(COMPILE) -o $(BUILD)$(TARGET).elf $(BUILD)$(TARGET).o $(BUILD)$(SERVO).o
	avr-objcopy -j .text -j .data -O ihex $(BUILD)$(TARGET).elf $(BUILD)$(TARGET).hex
	avr-size --format=avr --mcu=$(DEVICE) $(BUILD)$(TARGET).elf

upload: compile
	avrdude -v -D -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -Uflash:w:$(BUILD)$(TARGET).hex:i

clean:
	rm $(BUILD) -rf
	mkdir $(BUILD)


debug: compile
	simulavr -f $(TARGET) -d $(DEVICE) -G -F $(BAUD) -V