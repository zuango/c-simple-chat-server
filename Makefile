CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c17
LIBS = -lcrypto
INCLUDE = -Iinclude

SRC = src/main.c src/net.c src/process.c 
OBJ = $(SRC:src/%.c=build/%.o)
TARGET = build/shadowcomms

all: $(TARGET)

build:
	mkdir -p build

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@


$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -rf build

.PHONY: all clean
