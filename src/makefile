CC = gcc
CFLAGS = -W -Wall -ansi -std=c99
LDFLAGS = `sdl2-config --cflags --libs` -lm
EXEC = main
all: $(EXEC)
main: fonctions_fichiers.o main.o
	$(CC) -o main fonctions_fichiers.o main.o $(LDFLAGS)
fonctions_fichiers.o: fonctions_fichiers.c
	$(CC) -o fonctions_fichiers.o -c fonctions_fichiers.c $(CFLAGS)
main.o: main.c fonctions_fichiers.h
	$(CC) -o main.o -c main.c $(CFLAGS)
clean:
	rm -rf *.o *~
mrproper: clean
	rm -rf $(EXEC)

