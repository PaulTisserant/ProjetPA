
#ifndef OBJET_H
#define OBJET_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include "constante.h"




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
    double dirX;
    double dirY;
    double angle ; /*!< Angle de rotation. */
    int is_visible ; /*!< Variable qui indique la visibilité du sprite ou non. */

};
/* Definitions des types */
typedef struct Liste *liste ; 
struct Liste {
  sprite_t premier ; 
  liste suivant ;
};


/**
 * \brief Représentation du monde du jeu
*/
struct world_s{
    bool tir;
    int terminer ;
    char** terrain;
    liste mur ;
    liste tour_terrain ;
    int colonne ;
    int ligne ;
    int powerPress;
    int nbCoups ;
    enum STATUS status ;
    enum PAGES page ;
    sprite_t ball ; /*!< balle. */
	sprite_t* tile; /*!<Tableau de tuile. */
    sprite_t hole; /*!<Troue. */
    sprite_t arrow ; /*!<Troue.*/
    sprite_t* buttons ;
    sprite_t sauv ;
    sprite_t pause ;
    sprite_t reprendre ;
    sprite_t quitte ;
    SDL_Rect rect ;
    sprite_t lancer ;
    sprite_t recommencer ;
    char* pseudo ;
    int nbLettrePseudo;
    bool init ;
    int nb_niveau ;
    int current_level;
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
    SDL_Texture* pause ;
    SDL_Texture* sauv_a;
    SDL_Texture* sauv ;
    SDL_Texture* lancer ;
    SDL_Texture* lancer_a ;
    SDL_Texture* reprendre ;
    SDL_Texture* reprendre_a ;
    SDL_Texture* recommencer ;
    SDL_Texture* recommencer_a ;
    SDL_Texture* quitte ;
    TTF_Font* font ;
   


};

/**
 * \brief Type qui correspond aux textures du jeu
*/
typedef struct textures_s textures_t;








/* SIGNATURES DES OPERATIONS PRIMITIVES */

// constructeurs
liste l_vide () ;
liste cons (sprite_t x, liste L) ;

// accès
bool est_vide (liste L) ;
sprite_t prem (liste L) ;
liste reste (liste L) ;
void liberer_liste (liste L) ;

/* SIGNATURE FONCTION NON PRIMITIVES */
void afficher_liste (liste L) ;

liste ajouter_element(sprite_t x,liste lst);
sprite_t dernier ( liste lst);
liste neme_reste ( unsigned int n , liste lst );
sprite_t neme_elem ( unsigned int n , liste lst );
unsigned int longueur(liste lst);
#endif 
