# Compilatore e flag
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Linker flags specifici per OS
ifeq ($(OS),Windows_NT)
    LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lm
    TARGET = surface.exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LDFLAGS = `sdl2-config --libs` -lm
    else
        LDFLAGS = -lSDL2 -lm
    endif
    TARGET = surface
endif

# File sorgenti e oggetti
SRC = main.c function.c
OBJ = $(SRC:.c=.o)

# Comandi
RM = rm -f

# Regole principali
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c function.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(TARGET)

.PHONY: all clean
