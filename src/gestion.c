#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "fonctions_fichiers.h"
#include "objet.h"
#include "sdl2-ttf-light.h"
#include "gestion.h"
#include "graphique.h"




void update_data(world_t* world,SDL_Renderer *renderer,textures_t* texture){
    if (world->status == JOUER)
    {
       // si la balle touche le trou 
       if(world->ball.x + ball_size > world->hole.x && world->ball.x < world->hole.x + world->hole.w && world->ball.y + ball_size > world->hole.y && world->ball.y < world->hole.y + world->hole.h){
            next_level(world,renderer,texture);
        }

        for (int i = 0; i < longueur(world->tour_terrain); i++){

            sprite_t tourMur = neme_elem(i,world->tour_terrain);
            
            if(sprites_collide(world->ball, tourMur)){
                
                printf("collision");
                // Calcule le centre du mur
                double tile_centerX = tourMur.x + tourMur.w / 2;
                double tile_centerY = tourMur.y + tourMur.h / 2;

                // Calcule le centre de la balle
                double ball_centerX = world->ball.x + world->ball.w / 2;
                double ball_centerY = world->ball.y + world->ball.h / 2;

                // Calcul le vecteur normal du mur
                double normalX = ball_centerX - tile_centerX;
                double normalY = ball_centerY - tile_centerY;

                // Normalise le vecteur normal (le redimensionne à une longueur de 1)
                double length = sqrt(normalX * normalX + normalY * normalY);
                normalX /= length;
                normalY /= length;

                // redirectionne le vecteur vitesse de la balle sur le vecteur normal du mur
                double dot_product = world->ball.dirX * normalX + world->ball.dirY * normalY;

                world->ball.dirX = world->ball.dirX - 2 * dot_product * normalX;
                world->ball.dirY = world->ball.dirY - 2 * dot_product * normalY;
                
            }

        }

        for (int i = 0; i < longueur(world->mur); i++){

            sprite_t mur = neme_elem(i,world->mur);
            
            if(sprites_collide(world->ball, mur)){

                // Calcule le centre du mur
                double tile_centerX = mur.x + mur.w / 2;
                double tile_centerY = mur.y + mur.h / 2;

                // Calcul le centre de la balle
                double ball_centerX = world->ball.x + world->ball.w / 2;
                double ball_centerY = world->ball.y + world->ball.h / 2;

                // Calcul le vecteur normal du mur
                double normalX = ball_centerX - tile_centerX;
                double normalY = ball_centerY - tile_centerY;

                // Normalise le vecteur normal (le redimensionne à une longueur de 1)
                double length = sqrt(normalX * normalX + normalY * normalY);
                normalX /= length;
                normalY /= length;

                // redirectionne le vecteur vitesse de la balle sur le vecteur normal du mur
                double dot_product = world->ball.dirX * normalX + world->ball.dirY * normalY;

                world->ball.dirX = world->ball.dirX - 2 * dot_product * normalX;
                world->ball.dirY = world->ball.dirY - 2 * dot_product * normalY;
                
            }

        }



        if (world->ball.power > 0)
        {
            for (int i = 0; i < longueur(world->mur); i++)
            {
                sprite_t mur = neme_elem(i,world->mur);
                if(sprites_collide(world->ball, mur)){
                    world->ball.x = mur.x + mur.w + 1;
                    world->ball.y = mur.y + mur.h + 1;
                    break;
                }
            }

            world->ball.x += world->ball.dirX;
            world->ball.y += world->ball.dirY;

            world->ball.dirX *= 0.99;
            world->ball.dirY *= 0.99;
            world->ball.power --;
        }
        if (world->powerPress == 0)
        {
            world->rect.w = 10 ; // si plus de power la barre indiquant le power reprend sa form initial
        }
    }
}

void init_data(world_t* world){
//---------------------Initialisation des sprites----------------------------------
    printf("init data \n");
    world->tir = false;
    world->arrow.angle = 0 ;
    world->ball.power = 0 ;
    world->powerPress = 5 ;
    world->ball.dirX = 0;
    world->ball.dirY = 0;
    world->nbCoups = 0 ;
    world->rect.x =30 ;
    world->rect.y =650;
    world->rect.w = 10;
    world->rect.h = 50;
    if (world->init_sauv)
    {
        lire_sauvgarde(world); // permet d'avoir le niveau actuel utile dans init_data_file
    }
    init_data_file(world);
    if (world->init_sauv)
    {
         lire_sauv_ball(world); //Dois être faite car initialement la position de la balle est définis dans la fonction init_data_file
    }
    
    

    

}
void next_level(world_t* world,SDL_Renderer *renderer,textures_t* texture){
    if (world->current_level + 1 > world->nb_niveau) // si il n'y a pas de niveau suivant
    {
        world->status = FIN ;
    }
    else{
        world->current_level++ ;
        world->CoupsTot += world->nbCoups ;
        init_data(world);
        init_textures(renderer,texture,world);
    }
    
}


void init_data_file(world_t* world){
    char* nomFichier = malloc(sizeof(char)*32) ;
    int col = 0;
    int ligne = 0 ;
    int srcpos = 0 ;
    sprintf(nomFichier, "niveaux/hole%d.txt",world->current_level);
    taille_fichier(nomFichier, &(ligne), &(col)); // Initialisation du nombres de tuile dans le monde
    world->colonne = col ;
    world->ligne = ligne ;
    printf("ligne : %i,col:%i \n",col,ligne);
    world->tile = malloc(sizeof(sprite_t)*(world->colonne+2)*(world->ligne+2)) ;
    world->mur = l_vide() ;
    world->tour_terrain = l_vide() ;
    world->terrain = lire_fichier(nomFichier);              
    for (int i = 0; i < world->ligne+2; i++) {
        for (int j = 0; j < world->colonne+2; j++) {      

            world->tile[srcpos].x = 32*j + DEC ;
            world->tile[srcpos].y = 32*i + HAUT ;
            world->tile[srcpos].w = 32 ;
            world->tile[srcpos].h = 32 ;
            world->tile[srcpos].angle = 0 ;
            world->tile[srcpos].v = 0 ;
            if (j==0 || i == 0 || j >world->colonne || i >world->ligne)
            {

                world->tour_terrain = ajouter_element(world->tile[srcpos],world->tour_terrain);
            }
            else{
                if ( world->terrain[i-1][j-1] == 'B') {
                    world->ball.x = 32*j + DEC;
                    world->ball.y = i*32 + HAUT;
                    world->ball.w = 10 ;
                    world->ball.h = 10 ;
                    world->ball.angle = 0 ;
                    world->ball.v = 10 ;
                }
                if (world->terrain[i-1][j-1] == 'O' ) {
                    world->hole.x = 32*j + DEC;
                    world->hole.y = i*32 + HAUT;
                    world->hole.w = 10 ;
                    world->hole.h = 10 ;
                    world->hole.angle = 0 ;
                    world->hole.v = 0 ;
                }
                
                if (world->terrain[i-1][j-1] == 'X' ){
                    world->mur = ajouter_element(world->tile[srcpos],world->mur);
                }
            }
            srcpos++ ;
            
        }
    }
    free(nomFichier);
}


//Fonction qui change le score entier en score en chaine de caractere
void int_to_char(char* score_txt,int score){
	if(score < 10){
		char temp = score + '0'; //le score est sur un seul chiffre
		score_txt[0] = temp ;
		score_txt[1] = '\0';
	}else{
		char temp = score/10 + '0'; //le score est sur 2 chiffres
		char temp2 = score%10 + '0';
		score_txt[0] = temp ;
		score_txt[1] = temp2;
		score_txt[2] = '\0';
	}
}
//fonction liberant la mémoire ds textures et liberant la mmoire dynamique
void clean_data(world_t* world , textures_t* texture){
    SDL_DestroyTexture(texture->arrow);
    SDL_DestroyTexture(texture->back);
    SDL_DestroyTexture(texture->menu);
    SDL_DestroyTexture(texture->pause);
    SDL_DestroyTexture(texture->sauv_a);
    SDL_DestroyTexture(texture->sauv);
    SDL_DestroyTexture(texture->lancer);
    SDL_DestroyTexture(texture->lancer_a);
    SDL_DestroyTexture(texture->reprendre);
    SDL_DestroyTexture(texture->reprendre_a);
    SDL_DestroyTexture(texture->recommencer);
    SDL_DestroyTexture(texture->recommencer_a);
    SDL_DestroyTexture(texture->quitte);
    SDL_DestroyTexture(texture->menu_fin);
    clean_font(texture->font) ;
    for (size_t i = 0; i < 6; i++)
    {
        SDL_DestroyTexture(texture->buttons[i]);
    }
    free(texture->buttons);
    desallouer_tab_2D(world->terrain,world->ligne);
    free(world->tile);
    free(world->buttons);
    free(world->pseudo);
    free(world->terrain);
    liberer_liste(world->mur);
    liberer_liste(world->tour_terrain);





}