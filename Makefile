C       = arm-none-eabi-gcc
C_OBJ   = arm-none-eabi-objcopy
ST_FLASH = st-flash

ANIMATION ?= PIPES

CFLAGS = -D$(ANIMATION)=1 \
	 -DSTM32F401xE \
         -Wall -Wextra -g -std=c99 -O3 \
         -nostartfiles -nostdlib -ffreestanding \
         -mthumb -mcpu=cortex-m4 \
         -mfpu=fpv4-sp-d16 \
         -mfloat-abi=hard \
         -Iinclude \
         -Ilib/STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
         -Ilib/STM32CubeF4/Drivers/CMSIS/Include

LDFLAGS = -Tlinker.ld \
          -nostdlib -nodefaultlibs -nostartfiles -Wl,--gc-sections
          -mfpu=fpv4-sp-d16 \
          -mfloat-abi=hard

SRC     = $(wildcard src/*.c)
DATA_FILES = $(wildcard data/poly[1-8].dat)
DATA_OBJ = $(patsubst data/%.dat, bin/%_dat.o, $(DATA_FILES))
OBJ     = $(patsubst src/%.c, bin/%.o, $(SRC)) $(DATA_OBJ)
TARGET  = main.elf
BIN     = main.bin

all: $(BIN)

$(TARGET): $(OBJ)
	$(C) $(LDFLAGS) -o $@ $^


bin/%_dat.o: data/%.dat | bin
	$(C_OBJ) -I binary -O elf32-littlearm --binary-architecture=armv7e-m $< $@

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
