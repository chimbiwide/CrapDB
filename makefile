CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./include
TARGET = crapdb
SRC = $(wildcard src/*.c)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean
