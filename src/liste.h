#include <stdbool.h>
#ifndef LISTE_H
#define LISTE_H

/* Definitions des types */

typedef struct Liste *liste ; 

struct Liste {
  int premier ; 
  liste suivant ;
};

/* SIGNATURES DES OPERATIONS PRIMITIVES */

// constructeurs
liste l_vide () ;
liste cons (int x, liste L) ;

// accès
bool est_vide (liste L) ;
int prem (liste L) ;
liste reste (liste L) ;
void liberer_liste (liste L) ;

/* SIGNATURE FONCTION NON PRIMITIVES */
void afficher_liste (liste L) ;


#endif 
