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


void apply_friction(world_t* world) {
}

// Function to check if the ball needs to bounce off a tile
bool check_tile_collision(sprite_t ball, sprite_t mur) {
  // Check if the ball is intersecting the tile
  if (ball.x + ball.dirX < mur.x + mur.w &&
      ball.x + ball.dirX + ball.w > mur.x &&
      ball.dirY + ball.dirY < mur.y + mur.h &&
      ball.y + ball.dirY + ball.h > mur.y) {
    return true;
  }
  return false;
}

void update_data(world_t* world, SDL_Renderer *renderer,textures_t* texture){
    if (world->status == JOUER)
    {
       // si la balle touche le trou 
       if(world->ball.x + ball_size > world->hole.x && world->ball.x < world->hole.x + world->hole.w && world->ball.y + ball_size > world->hole.y && world->ball.y < world->hole.y + world->hole.h){
            next_level(world,renderer,texture) ;
        }

        //print power
        printf("%d\n", world->ball.power);
        

        if (!world->tir)
        {
            world->ball.dirX = -world->ball.power * cos(world->ball.angle);
            world->ball.dirY = world->ball.power * -sin(world->ball.angle);   
        } 
        



        for (int i = 0; i < longueur(world->mur); i++)
        {

            sprite_t mur = neme_elem(i,world->mur);
            
            if(sprites_collide(world->ball, mur)){
                
                printf("COLLISION\n");
                double normalX;
                double normalY;
                
                normalX = world->ball.x - (mur.x + mur.w / 2);
                normalY = world->ball.y - (mur.y + mur.h / 2);

                // Calculate the angle of incidence
                double angle_incidence = atan2(world->ball.dirY, world->ball.dirX);

                // Calculate the angle of reflection
                double angle_reflection = 2 * atan2(normalY, normalX) - angle_incidence;

                // Calculate the new x and y components of the velocity
                world->ball.dirX = world->ball.power * cos(angle_reflection);
                world->ball.dirY = world->ball.power * sin(angle_reflection);
                break;
                
                /*
                double normalX = (world->ball.x + world->ball.dirX + world->ball.w / 2) - (mur.x + mur.w / 2);
                double normalY = (world->ball.y+ world->ball.dirY + world->ball.h / 2) - (mur.y+ mur.h / 2);

                // Check if the world->ball is colliding with the mur in the x-direction
                if (normalX > 0 && normalX < mur.w / 2) {
                    world->ball.dirX = -world->ball.dirX;
                }

                // Check if the world->ball is colliding with the mur in the y-direction
                if (normalY > 0 && normalY < mur.h / 2) {
                    world->ball.dirY = -world->ball.dirY;
                }
                */
            }

        }

        //print dirX et dirY
        printf("%f\n", world->ball.dirX);
        printf("%f\n", world->ball.dirY);

        if (world->ball.dirX > 0 || world->ball.dirY > 0)
        {
            if (!world->tir)
            {
                world->ball.x -= world->ball.dirX;
                world->ball.y -= world->ball.dirY;
                world->ball.power --; 


            }else{
                world->ball.x += world->ball.dirX;
                world->ball.y += world->ball.dirY;
                world->ball.power --;
            }
        }
        if (world->powerPress == 0)
        {
            world->rect.w = 10 ;
        }
        
    }
}
void init_new(world_t* world){

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

    init_data_file(world);


    

}
void next_level(world_t* world,SDL_Renderer *renderer,textures_t* texture){
    if (world->current_level + 1 > world->nb_niveau)
    {
        printf("fin du jeu");
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
    sprintf(nomFichier, "hole%d.txt",world->current_level);
    taille_fichier(nomFichier, &(ligne), &(col)); // Initialisation du nombres de tuile dans le monde
    world->colonne = col ;
    world->ligne = ligne ;
    printf("ligne : %i,col:%i",col,ligne);
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
