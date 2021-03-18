CC=gcc
CFLAGS=-Wall

all: src/*.c src/*.h src/struct/*.c src/struct/*.h
	$(CC) $(CFLAGS) -o compil src/*.c src/struct/*.c