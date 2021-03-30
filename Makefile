BUILD_DIR=build
OUTPUT=$(BUILD_DIR)/sokoban

CC=gcc
CFLAGS=-Wall

SOURCE=src
INCLUDE=include
LDFLAGS=-lncurses

build: clean $(SOURCE)/* $(INCLUDE)/*
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $(OUTPUT) src/*.c $(LDFLAGS)

run: build ./$(OUTPUT)
	./$(OUTPUT)

clean:
	rm -rf $(BUILD_DIR)

# Install required packages using apt (development env)
install-dev-with-apt:
	apt-get install libncurses5-dev ncurses-doc

# Install required packages using apt (prod)
install-with-apt:
	apt-get install libncurses5