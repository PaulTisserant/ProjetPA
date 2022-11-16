#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "liste.h"
#include "fonctions_fichiers.h"
/* IMPLEMENTATION DES OPERATIONS PRIMITIVES */

/* Constructeurs */


liste l_vide (){
    return NULL ;
}

liste cons (sprite_t x, liste L){
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

sprite_t prem (liste L){
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
    printf("\n[sprite.x : %i\nsprite.y : %i\nsprite.w : %i\nsprite.h : %i\nsprite.v : %i\nsprite.angle : %lf\nsprite.is_visible :%i]",prem(L).x,prem(L).y,prem(L).w,prem(L).h,prem(L).v,prem(L).angle,prem(L).is_visible);
    afficher_liste(reste(L));
  }
}

liste ajouter_element(sprite_t x,liste lst)
{
    if (est_vide(lst))
    {
        return(cons(x,lst)) ;
    }
    else
    {
        return(cons(prem(lst),ajouter_element(x,reste(lst)))) ; 
    }
}
sprite_t dernier ( liste lst){
    while (est_vide(reste(lst)) == false)
    {
        lst = reste(lst);
    }
    return lst->premier ;
}
liste neme_reste ( unsigned int n , liste lst ){
    for (int i = 0; i < n; i++)
    {
        lst = reste(lst) ;
    } 
    return lst ;
}
sprite_t neme_elem ( unsigned int n , liste lst ){
    for (int i = 0; i < n; i++)
    {
        lst = reste(lst) ;
    } 
    return lst->premier ;
}
unsigned int longueur(liste lst)
{
    int compt = 0 ;
    while (est_vide(lst) == false)
    {
        compt++ ;
        lst = reste(lst) ;
    }
    return compt ;
}