CC := gcc
CFLAGS := -std="c99" -I./src -Wall
OBJ := linecounter.o count.o flags.o
OBJDIR := ./src
DFLAGS := 

debug: DFLAGS += -g
debug: all

all: $(OBJ)
	@echo Building executable
	$(CC) $(OBJ) $(DFLAGS) $(CFLAGS) -o linecounter

%.o: $(OBJDIR)/%.c
	@echo Building $@
	$(CC) $(DFLAGS) $< -c

clean:
	@echo "Removing executable"
	rm -f linecounter
	@echo "Removing object files"
	rm -f *.o