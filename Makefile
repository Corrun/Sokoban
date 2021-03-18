BUILD_DIR=build
OUTPUT=build/sokoban

CC=gcc
CFLAGS=-Wall


all: src/*.c src/*.h src/struct/*.c src/struct/*.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(OUTPUT) src/*.c src/struct/*.c
