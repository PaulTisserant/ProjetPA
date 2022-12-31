CC = gcc
CFLAGS = -W -Wall -ansi -std=c99
LDFLAGS = `sdl2-config --cflags --libs` -lm -lSDL2_ttf
EXEC = main
all: $(EXEC)
main: menu.o graphique.o event.o gestion.o sdl2-ttf-light.o liste.o fonctions_fichiers.o main.o 
	$(CC) -o main menu.o graphique.o event.o gestion.o sdl2-ttf-light.o fonctions_fichiers.o liste.o main.o $(LDFLAGS)    
fonctions_fichiers.o: fonctions_fichiers.c
	$(CC) -o fonctions_fichiers.o -c fonctions_fichiers.c $(CFLAGS)
liste.o: liste.c
	$(CC) -o liste.o -c liste.c $(CFLAGS)
sdl2-ttf-light.o: sdl2-ttf-light.c
	$(CC) -o sdl2-ttf-light.o -c sdl2-ttf-light.c $(CFLAGS)    
gestion.o: gestion.c
	$(CC) -o gestion.o -c gestion.c $(CFLAGS) 
graphique.o: graphique.c
	$(CC) -o graphique.o -c graphique.c $(CFLAGS) 
event.o: event.c
	$(CC) -o event.o -c event.c $(CFLAGS)
menu.o: menu.c
	$(CC) -o menu.o -c menu.c $(CFLAGS) 
clean:
	rm -rf *.o *~
mrproper: clean
	rm -rf $(EXEC)