

#ifndef LISTE_H
#define LISTE_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_fichiers.h"

/* Definitions des types */
typedef struct Liste *liste ; 
struct Liste {
  sprite_t premier ; 
  liste suivant ;
};



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
