CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./include
LIBS = -lreadline
TARGET = crapdb
SRC = $(wildcard src/*.c)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
