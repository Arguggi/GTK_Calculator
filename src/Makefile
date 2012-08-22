PKG = `pkg-config --libs --cflags gtk+-2.0`
CC = gcc
CFLAGS = -Wdeprecated-declarations -Wall -Wextra -pedantic -std=c99
OBJ = calc.o table.o icon.o

calc : $(OBJ)
	$(CC) -o calc $(OBJ) $(PKG)

calc.o : calc.c table.c icon.c
	$(CC) -c calc.c $(CFLAGS) $(PKG)
table.o : table.c 
	$(CC) -c table.c $(CFLAGS) $(PKG)
icon.o : icon.c 
	$(CC) -c icon.c $(CFLAGS) $(PKG)
clean :
	rm calc *.o
