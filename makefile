CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = crapdb
SRC = main.c row.c

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean
