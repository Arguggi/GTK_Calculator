PKG = `pkg-config --libs --cflags gtk+-2.0`
CC = gcc
CFLAGS = -Wdeprecated-declarations

all : calc

calc : calc.c
	$(CC) -o calc calc.c $(CFLAGS) $(PKG)
clean :
	rm calc
