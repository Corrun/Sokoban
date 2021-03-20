BUILD_DIR=build
OUTPUT=build/sokoban

CC=gcc
CFLAGS=-Wall


build: src/*.c include/*.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(OUTPUT) src/*.c

run: build ./$(OUTPUT)
	./$(OUTPUT)
