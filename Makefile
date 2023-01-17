CC := gcc
CFLAGS := -Wall -ansi -I. -Wall
OBJ := linecounter.o

all: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o linecounter

%.o: %.c
	$(CC) $(CFLAGS) $< -c

debug: CFLAGS += -ggdb
debug: all

clean:
	rm -f linecounter
	rm -f *.o