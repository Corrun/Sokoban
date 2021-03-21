BUILD_DIR=build
OUTPUT=$(BUILD_DIR)/sokoban

CC=gcc
CFLAGS=-Wall

INCLUDE=include

build: src/*.c include/*.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $(OUTPUT) src/*.c

run: build ./$(OUTPUT)
	./$(OUTPUT)
