#ifndef FONCTIONS_FICHIERS_H
#define FONCTIONS_FICHIERS_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "objet.h"
#include <SDL2/SDL_ttf.h>
#include "constante.h"

/**
 * \brief Type qui correspond aux données du sprite
 */











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
void apply_texture(SDL_Texture *texture,SDL_Renderer *renderer,int x, int y,int w,int h,double angle);

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

void display_arrow(world_t* world);

bool entre(int v1,int v2,int v3);

bool pointeur_collision(sprite_t sp1);

void enregistrer_world_s(const char *nom_fichier, const struct world_s *world);

bool sprites_collide(sprite_t sp2, sprite_t sp1);

void lire_sauvgarde(world_t* world) ;
void lire_sauv_ball(world_t* world);
int nombres_niveau();
void char_array_empty(char* char_array) ;
void enregistre_score(const char *filename,world_t* world);
#endif