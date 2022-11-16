#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "liste.h"
/* IMPLEMENTATION DES OPERATIONS PRIMITIVES */

/* Constructeurs */

liste l_vide (){
    return NULL ;
}

liste cons (int x, liste L){
    liste M ;
    /* Réservation de la mémoire nécessaire et désignation d'une adresse */
    M = malloc (sizeof (struct Liste)) ;
    M->premier = x ;
    M->suivant = L ;
    return M ;
}

/* Accès */
bool est_vide (liste L){
    return L == NULL ;
}

int prem (liste L){
  if (est_vide (L)){
    printf ("Calcul de prem sur liste vide !\n") ;
    exit (0) ;
  }
  return L->premier ;
}

liste reste (liste L){
  return L->suivant ;
}

void liberer_liste (liste L){
    if (!est_vide(L)){
      liberer_liste (reste (L)) ;
      free (L);
    }
}

void afficher_liste (liste L){
  if (!est_vide(L)){
    printf("%i ", prem(L));
    afficher_liste(reste(L));
  }
}
