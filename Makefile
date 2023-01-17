CC := 

ifeq ($(OS), Windows_NT)
	CC += i686-w64-mingw32-gcc
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CC += gcc
	endif
endif

CFLAGS := -Wall -ansi -I.
OBJ := linecounter.o

all: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o linecounter

%.o: %.c
	$(CC) $(CFLAGS) $< -c

debug: CFLAGS += -ggdb
debug: all

clean:
	rm -f linecounter
	rm -f linecounter.exe
	rm -f *.o