#ifndef FONCTIONS_FICHIERS_H
#define FONCTIONS_FICHIERS_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



/*
 allouer un tableau de caractères de taille n × m, 
 où n et m sont les nombres de lignes et de colonnes 
 et initialiser ce tableau avec le caractère espace (’ ’).
*/
char** allouer_tab_2D(int n, int m); 


/*
 libérer un tableau à deux dimensions, de n lignes.
*/ 
void desallouer_tab_2D(char** tab, int n); 


/*
 afficher le contenu d’un tableau de caractères de taille n × m.
*/
void afficher_tab_2D(char** tab, int n, int m);

/*
 compter le nombre max de lignes (nbLig) et de colonnes (nbCol) dans le fichier dont le nom est nomFichier
*/
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);


/*
 lire un fichier dont le nom est nomFichier
 et retourner le tableau qui contient les caractères du fichier
 tel qu’une ligne du tableau correspond à une ligne du fichier.
*/
char** lire_fichier(const char* nomFichier); 

/*
 Retourner un nouveau tableau, dans lequel toutes les occurrences du
 caractère ancien sont remplacées par le caractère nouveau.
*/
char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau);


/*
 Écrire le tableau tab de taille n × m dans un fichier dont le nom est nomFichier.
*/
void ecrire_fichier(const char* nomFichier, char** tab, int n, int m);


SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer);

SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);

/*
* affiche le trou demandé dans le renderer
*/
void displayHole(SDL_Rect *SrcR_fond, SDL_Rect *DestR_fond, SDL_Rect *SrcR_hole, SDL_Rect *DestR_hole, SDL_Rect *SrcR_ball, SDL_Rect *DestR_ball, const char* nomFichier);

void display_arrow(SDL_Rect* SrcR_arrow,SDL_Rect* DestR_arrow,SDL_Rect* DestR_ball,int posx,int posy, double* angle);

#endif