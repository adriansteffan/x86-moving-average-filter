CC = gcc
NASM = nasm

CFLAGS =  -m32
NFLAGS = -f elf32

OBJECTS = filter.o

PROG = movafilter
CSRC = $(PROG).c

# make
all: $(PROG)

$(PROG): $(CSRC) 
	$(NASM) $(NFLAGS) -o $(OBJECTS) filter.asm
	$(CC) $(CFLAGS) -o $(PROG) $(CSRC) $(OBJECTS)

# make clean
clean:
	rm -f $(OBJECTS) $(PROG) filter
