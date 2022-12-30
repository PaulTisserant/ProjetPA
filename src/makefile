CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lm 

INC = fonctions_fichiers.h liste.h  sdl2-ttf-light.h 
SRC = main.c fonctions_fichiers.c liste.c sdl2-ttf-light.c
OBJ = $(SRC:%.c=%.o)
PROG = golf


%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<

golf: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@
clean:
	rm -f *~ *.o $(PROG)