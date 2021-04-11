BUILD_DIR=build
OUTPUT=$(BUILD_DIR)/sokoban

CC=gcc
CFLAGS=-Wall

SOURCE=src
INCLUDE=include
LDFLAGS=-lncurses

build: $(SOURCE)/* $(INCLUDE)/*
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $(OUTPUT) src/*.c $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)

run: build ./$(OUTPUT)
	./$(OUTPUT)

debug:
	$(CC) -g -I$(INCLUDE) -o $(OUTPUT) src/*.c $(LDFLAGS)

rund: debug ./$(OUTPUT) #Need to install valgrind
	valgrind -s $(OUTPUT)

# Install required packages using apt (development env)
install-dev-with-apt:
	apt-get install libncurses5 libncurses5-dev ncurses-doc

# Install required packages using apt (prod)
install-with-apt:
	apt-get install libncurses5