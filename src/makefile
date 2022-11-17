CC = gcc
CFLAGS = -W -Wall -ansi -std=c99
LDFLAGS = `sdl2-config --cflags --libs` -lm
EXEC = main
all: $(EXEC)
main: fonctions_fichiers.o main.o
	$(CC) -o main fonctions_fichiers.o liste.o main.o $(LDFLAGS)	
fonctions_fichiers.o: fonctions_fichiers.c
	$(CC) -o fonctions_fichiers.o -c fonctions_fichiers.c $(CFLAGS)
liste.o: liste.c
	$(CC) -o liste.o -c liste.c $(CFLAGS)	
clean:
	rm -rf *.o *~
mrproper: clean
	rm -rf $(EXEC)

