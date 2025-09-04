CPU = -mcpu=cortex-m4 -mthumb
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = $(CPU) -Wall -Wextra -O2 -ffreestanding -fno-builtin
LDFLAGS = -T linker.ld -nostdlib -Wl,--gc-sections

# Files
TARGET = main
SRCS = main.c lcd.c system.c startup.c debug.c
OBJ = $(TARGET).elf
BIN = $(TARGET).bin
HEX = $(TARGET).hex

# Default target
all: $(BIN) $(HEX)

$(OBJ): $(SRCS) linker.ld
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $(OBJ)

$(BIN): $(OBJ)
	$(OBJCOPY) -O binary $(OBJ) $(BIN)

$(HEX): $(OBJ)
	$(OBJCOPY) -O ihex $(OBJ) $(HEX)

clean:
	rm -f $(OBJ) $(BIN) $(HEX)

flash: $(BIN)
	st-flash write $(BIN) 0x08000000

.PHONY: all clean flash
