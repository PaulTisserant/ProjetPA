#ifndef FONCTIONS_FICHIERS_H
#define FONCTIONS_FICHIERS_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "liste.h"

#define PI 3.14159265
enum STATUS{PERDU , GAGNER , STOP , JOUER , LANCEMENT } ;
enum PAGES{INIT,OPTION};
enum BUTTON{J_OFF,J_ON,O_OFF,O_ON,S_OFF,S_ON};
/**
 * \brief Type qui correspond aux données du sprite
 */
typedef struct sprite_s sprite_t;
/**
 * \brief Représentation des sprites du jeu
*/

struct sprite_s{
    int x; /*!< Coordonnée en abscisse. */
    int y; /*!< Coordonnée en ordonnée. */
    int w; /*!< Dimension en largeur. */
    int h; /*!< Dimension en hauteur. */
    int v; /*!< Vitesse. */
    int power ;
    double angle ; /*!<Vitesse. */
    int is_visible ; /*!< Variable qui indique la visibilité du sprite ou non. */

};
typedef struct Liste *liste ; 


/**
 * \brief Représentation du monde du jeu
*/
struct world_s{
    int terminer ;
    char** terrain;
    liste mur ;
    liste tour_terrain ;
    int colonne ;
    int ligne ;
    int powerPress;
    enum STATUS status ;
    enum PAGES page ;
    sprite_t ball ; /*!< balle. */
	sprite_t* tile; /*!<Tableau de tuile. */
    sprite_t hole; /*!<Troue. */
    sprite_t arrow ; /*!<Troue.*/
    sprite_t* buttons ;
};

/**
 * \brief Type qui correspond aux données du monde
 */
typedef struct world_s world_t;


/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/
struct textures_s{
    SDL_Texture** tile; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* ball; /*!< Texture liée à l'image du vaisseau. */
    SDL_Texture* hole; /*!< Texture liée à l'image des adversaires. */
    SDL_Texture* arrow;  /*!< Texture liée à l'image du missile. */
    SDL_Texture* back;
    SDL_Texture* menu ;
    SDL_Texture** buttons;


};

/**
 * \brief Type qui correspond aux textures du jeu
*/
typedef struct textures_s textures_t;









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

void display_arrow(world_t* world);

void handle_sprites_collision(sprite_t *sp2, sprite_t *sp1);

int wich_side_collide(sprite_t *sp2, sprite_t *sp1);

bool entre(int v1,int v2,int v3);
#endif