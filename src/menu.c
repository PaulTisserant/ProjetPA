#include "fonctions_fichiers.h"
#include "objet.h"
#include <SDL2/SDL.h>
#include "sdl2-ttf-light.h"
#include "constante.h"
#include "graphique.h"
#include "objet.h"
#include "menu.h"


int update_lancement(SDL_Renderer *renderer, world_t *world,textures_t *textures){


    if (world->status == LANCEMENT)
    {
       switch (world->page)
       {
       case INIT:
              
                
                if (textures->menu == NULL)
                {
                    textures->menu = charger_image("menu.bmp",renderer);
                }
                
                
                apply_texture(textures->menu,renderer,0,0,1280,720,0);


        break;
       case OPTION:
                if (textures->menu == NULL)
                {
                    printf("nullopt");
                    textures->menu = charger_image("option.bmp",renderer);
                }
                apply_texture(textures->menu,renderer,0,0,1280,720,0);

       default:
        break;
       } 


    }
    
    int posx = 0 ;
    int posy = 0 ;       
    SDL_GetMouseState(&posx,&posy); 
    if (world->page == INIT)
    {
        if (pointeur_collision(world->buttons[0])){
            apply_texture(textures->buttons[1],renderer,world->buttons[1].x,world->buttons[1].y,world->buttons[1].w,world->buttons[1].h,0);
        }
        else{
            apply_texture(textures->buttons[0],renderer,world->buttons[0].x,world->buttons[0].y,world->buttons[0].w,world->buttons[0].h,0);
        }
        if (pointeur_collision(world->buttons[2])){
            apply_texture(textures->buttons[3],renderer,world->buttons[3].x,world->buttons[3].y,world->buttons[3].w,world->buttons[3].h,0);
        
        }
        else{
            apply_texture(textures->buttons[2],renderer,world->buttons[2].x,world->buttons[2].y,world->buttons[2].w,world->buttons[2].h,0);
        }
        if (pointeur_collision(world->buttons[4])){
            apply_texture(textures->buttons[5],renderer,world->buttons[5].x,world->buttons[5].y,world->buttons[5].w,world->buttons[5].h,0);

        }
        else{
            apply_texture(textures->buttons[4],renderer,world->buttons[4].x,world->buttons[4].y,world->buttons[4].w,world->buttons[4].h,0);
            
        }
    }
}

void gestion_pause(SDL_Renderer *renderer, world_t *world,textures_t *textures){
    if(world->status == PAUSE){
        apply_texture(textures->pause,renderer,world->pause.x,world->pause.y,world->pause.w ,world->pause.h,0.0 );
        if(pointeur_collision(world->sauv)){
            apply_texture(textures->sauv_a,renderer,world->sauv.x,world->sauv.y,world->sauv.w ,world->sauv.h,0.0 );
        }
        else{
            apply_texture(textures->sauv,renderer,world->sauv.x,world->sauv.y,world->sauv.w ,world->sauv.h,0.0 );
        }
        if (pointeur_collision(world->reprendre))
        {
            apply_texture(textures->reprendre_a,renderer,world->reprendre.x,world->reprendre.y,world->reprendre.w ,world->reprendre.h,0.0 );
        }
        else{
            apply_texture(textures->reprendre,renderer,world->reprendre.x,world->reprendre.y,world->reprendre.w ,world->reprendre.h,0.0 );

        }

    }
}