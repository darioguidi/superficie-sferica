CC = gcc
CFLAGS = -Wall -Wextra -O2

# Rileva sistema operativo e setta LDFLAGS di conseguenza
ifeq ($(OS),Windows_NT)
    # Windows (MinGW)
    LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lm
    RM = del /Q
else
    # Linux / Unix
    LDFLAGS = -lSDL2 -lm
    RM = rm -f
endif

SRC = main.c function.c
OBJ = $(SRC:.c=.o)
TARGET = surface

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c function.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(TARGET)
