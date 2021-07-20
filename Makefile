# MAKEFILE 
#
# reference: https://sourceforge.net/p/sdcc/mailman/message/11632749/
#

CC = sdcc 

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.rel,$(SRCS))

VERBOSE = --verbose
TARGET = -mmcs51
INCLUDES = -I.
OPTIMIZE = --opt-code-size #--no-xinit-opt
CFLAGS = -c $(VERBOSE) $(TARGET) $(INCLUDES) $(OPTIMIZE) -DDBG
LFLAGS = $(VERBOSE) $(TARGET) --iram-size 512 --code-size 8192
LIBS = 

ifeq ($(OS), Windows_NT)
RM = del
else
RM = rm
endif

all : rom.hex

rom.hex : $(OBJS)
	$(CC) -o $(patsubst %.hex,%.ihx,$@) $(LFLAGS) $(LIBS) $^ 
	packihx rom.ihx > rom.hex
#	objcopy -Iihex -Obinary rom.hex rom.bin
	makebin -p rom.hex rom.bin

%.rel : %.c
	$(CC) $(CFLAGS) $< 

clean:
	$(RM) -f *.rel *.s *.asm *.lst *.sym *.rst *.txt *.mem *.map *.lk *.ihx *.hex *.bin
