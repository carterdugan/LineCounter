CC := gcc
CFLAGS := -std="c90" -I./src -Wall
OBJ := linecounter.o count.o flags.o
OBJDIR := ./src

all: $(OBJ)
	@echo Building executable
	$(CC) $(OBJ) $(CFLAGS) -o linecounter

%.o: $(OBJDIR)/%.c
	@echo Building object files
	$(CC) $< -c

clean:
	@echo "Removing executable"
	rm -f linecounter
	@echo "Removing object files"
	rm -f *.o