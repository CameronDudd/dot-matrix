C       = arm-none-eabi-gcc
C_OBJ   = arm-none-eabi-objcopy
ST_FLASH = st-flash

CFLAGS = -DSTM32F401xE \
         -Wall -Wextra -g -std=c99 -O3 \
         -nostartfiles -nostdlib -ffreestanding \
         -mthumb -mcpu=cortex-m4 \
         -Iinclude \
         -Ilib/STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
         -Ilib/STM32CubeF4/Drivers/CMSIS/Include

LDFLAGS = -Tlinker.ld \
          -nostdlib -nodefaultlibs -nostartfiles -Wl,--gc-sections

SRC     = $(wildcard src/*.c)
OBJ     = $(patsubst src/%.c, bin/%.o, $(SRC))
TARGET  = main.elf
BIN     = main.bin

all: $(BIN)

$(TARGET): $(OBJ)
	$(C) $(LDFLAGS) -o $@ $^

bin/%.o: src/%.c | bin
	$(C) $(CFLAGS) -c $< -o $@

bin:
	mkdir -p bin

$(BIN): $(TARGET)
	$(C_OBJ) -O binary $< $@
	rm $<

flash: $(BIN)
	$(ST_FLASH) --connect-under-reset write $(BIN) 0x8000000

clean:
	rm -rf bin $(TARGET) $(BIN)

paint:
	cd lib/dot-matrix-paint; npm i; npm run dev

cloc:
	cloc --md src include
