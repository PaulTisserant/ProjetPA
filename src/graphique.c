#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "fonctions_fichiers.h"
#include "graphique.h"
#include "objet.h"
#include <SDL2/SDL.h>
#include "sdl2-ttf-light.h"
#include "gestion.h"
void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){

        apply_texture(textures->back,renderer,0,0,1280,720,0);
        if (world->status == JOUER){
            for (int i = 0; i < (world->colonne+2)*(world->ligne+2); i++) {
                apply_texture(textures->tile[i],renderer,world->tile[i].x,world->tile[i].y,world->tile[i].w,world->tile[i].h,0);
            }
            apply_texture(textures->ball,renderer,world->ball.x,world->ball.y,world->ball.w,world->ball.h,0);
            apply_texture(textures->hole,renderer,world->hole.x,world->hole.y,world->hole.w,world->hole.h,0);
            apply_texture(textures->arrow,renderer,world->arrow.x,world->arrow.y,world->arrow.w,world->arrow.h,world->arrow.angle);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            char* score = malloc(sizeof(char)*3) ;
            char* max_lvl = malloc(sizeof(char)*3) ;
            char* cur_lvl = malloc(sizeof(char)*3) ;
            char* max_score = malloc(sizeof(char)*4);
            
            int_to_char(score,world->nbCoups) ;
            int_to_char(max_lvl,world->nb_niveau) ;
            int_to_char(cur_lvl,world->current_level) ;
            int_to_char(max_score,world->CoupsTot) ;
            apply_text(renderer,30,100,200,40,"Nombre de TIR :",textures->font);
            apply_text(renderer,100,150,50,70,score,textures->font);

            apply_text(renderer,30,200,200,40,"Nombre total de TIR :",textures->font);
            apply_text(renderer,100,250,50,70,max_score,textures->font);

            apply_text(renderer,600,50,25,35,cur_lvl,textures->font);
            apply_text(renderer,630,50,25,35,"/",textures->font);
            apply_text(renderer,660,50,25,35,max_lvl,textures->font);

            SDL_RenderFillRect(renderer, &world->rect);
            //printf("world->arrow.angle : %lf",world->arrow.angle);
        }
}
void init_textures(SDL_Renderer *renderer,textures_t* texture,world_t* world){
    printf("init textures \n");
    texture->ball = charger_image_transparente("ball.bmp",renderer,0,255,255);
    texture->hole = charger_image_transparente("hole.bmp",renderer,0,255,255);
    texture->arrow = charger_image("arrow.bmp",renderer);
    texture->back = charger_image("background.bmp",renderer);
    texture->tile = malloc(sizeof(textures_t)*(world->colonne+2)*(world->ligne+2));
    //Initialisation des textures du terrain
    SDL_Texture*  wall =charger_image("wood.bmp",renderer);
    SDL_Texture*  grass =charger_image("grass.bmp",renderer);
    SDL_Texture*  block =charger_image("block.bmp",renderer);
    SDL_Texture*  water =charger_image("water.bmp",renderer);
    texture->menu_fin = charger_image("menu_fin.bmp",renderer);
    int srcpos = 0 ;
    for (int i = 0; i < world->ligne+2; i++) {
        for (int j = 0; j < world->colonne+2; j++) {

            if (j==0 || i == 0 || i >world->ligne || j>world->colonne)
            {
                texture->tile[srcpos] = block;
            }
            else{
                if (world->terrain[i-1][j-1] == ' ' || world->terrain[i-1][j-1] == 'O' || world->terrain[i-1][j-1] == 'B') {

                    texture->tile[srcpos] = grass;

                }
                if (world->terrain[i-1][j-1] == 'X') {
                    texture->tile[srcpos] = wall;
                }
                if (world->terrain[i-1][j-1] == 'W') {
                    texture->tile[srcpos] = water;
                }
            }
            srcpos++ ;
        }
    }   




     
    printf("Init texture terminer");

}
void init_renderer(SDL_Renderer **renderer,SDL_Window** fenetre,world_t* world){
    printf("init renderer \n");

    if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
        printf("Erreur d’initialisation de la SDL:  %s",SDL_GetError());
        SDL_Quit();
    }


    // Créer la fenêtre
    SDL_CreateWindowAndRenderer(1280, 720, SDL_WINDOW_SHOWN, fenetre, renderer);

    if(fenetre == NULL) // En cas d’erreur
    {
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
    }


    
}