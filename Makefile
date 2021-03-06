PATH := $(DEVKITARM)/bin:$(PATH)

# --- Project details -------------------------------------------------

PROJ    := duck_hunter
TITLE   := $(PROJ)

# Setup Environment var LIBTONC to /C/tonc/code/tonclib
INCLUDE  := -I$(LIBTONC)/include
LIBPATHS := -L$(LIBTONC)/lib

LIBS    := -ltonc

CROSS   ?= arm-none-eabi-
AS      := $(CROSS)gcc
CC      := $(CROSS)gcc
LD      := $(CROSS)gcc
OBJCOPY := $(CROSS)objcopy

all : duck_hunter.gba


background.c background.h : background.png
	grit background.png -gu16 -gB4 -mLs -ftc
background.h : background.c

background.o : background.c background.h
	arm-none-eabi-gcc -I${INCLUDE} -O2 -Wall -fno-strict-aliasing -mthumb-interwork -mthumb -c background.c -o background.o
	
background2.c background2.h : background2.png
	grit background2.png -gu16 -gB4 -mLs -ftc
background2.h : background2.c

background2.o : background2.c background2.h
	arm-none-eabi-gcc -I${INCLUDE} -O2 -Wall -fno-strict-aliasing -mthumb-interwork -mthumb -c background2.c -o background2.o

duck.c :
	grit duck.png -gu16 -gB4 -Mw 4 -Mh 4 -ftc

duck.o : duck.c
	arm-none-eabi-gcc ${INCLUDE} -O2 -Wall -fno-strict-aliasing -mthumb-interwork -mthumb -c duck.c -o duck.o

duck_hunter.o : duck_hunter.c background.h background2.h
	arm-none-eabi-gcc ${INCLUDE} -O2 -Wall -fno-strict-aliasing -mthumb-interwork -mthumb -c duck_hunter.c -o duck_hunter.o

duck_hunter.elf : duck_hunter.o background.o background2.o duck.o
	arm-none-eabi-gcc duck_hunter.o background.o duck.o background2.o -mthumb-interwork -mthumb -specs=gba.specs ${LIBPATHS} -ltonc -o duck_hunter.elf

duck_hunter.gba : duck_hunter.elf
	arm-none-eabi-objcopy -v -O binary duck_hunter.elf duck_hunter.gba
	gbafix duck_hunter.gba -tduck_hunter

clean :
	rm -f background.c
	rm -f background.h
	rm -f background.o
	rm -f background2.c
	rm -f background2.h
	rm -f background2.o
	rm -f duck.c
	rm -f duck.o
	rm -f duck_hunter.o
	rm -f duck_hunter.elf
	rm -f duck_hunter.gba
