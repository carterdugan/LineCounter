CC := gcc
CFLAGS := -Wall -ansi -I./src -Wall
OBJ := linecounter.o count.o flags.o
OBJDIR := ./src

all: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o linecounter

%.o: $(OBJDIR)/%.c
	$(CC) $(CFLAGS) $< -c

debug: CFLAGS += -ggdb
debug: all

clean:
	rm -f linecounter
	rm -f *.o