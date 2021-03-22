BUILD_DIR=build
OUTPUT=$(BUILD_DIR)/sokoban

CC=gcc
CFLAGS=-Wall

SOURCE=src
INCLUDE=include

build: clean $(SOURCE)/* $(INCLUDE)/*
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $(OUTPUT) src/*.c

run: build ./$(OUTPUT)
	./$(OUTPUT)

clean:
	rm -rf $(BUILD_DIR)