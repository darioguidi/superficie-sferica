CC = gcc
CFLAGS = -Wall -Wextra -O2

ifeq ($(OS),Windows_NT)
    LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lm
else
    LDFLAGS = -lSDL2 -lm
endif

RM = rm -f

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

.PHONY: all clean
