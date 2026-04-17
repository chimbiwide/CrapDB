UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	CC = gcc
endif

ifeq ($(UNAME_S), Darwin)
	CC = clang
endif

CC = clang
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
