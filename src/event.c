#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "fonctions_fichiers.h"
#include "objet.h"
#include "constante.h"
#include "event.h"
void handle_events(SDL_Event *evenements,world_t *world,textures_t *textures){
    
    while(   SDL_PollEvent( evenements ) ){ 

        if(world->status == JOUER){
            
            switch(evenements->type)
            {
                case SDL_QUIT:
                    world->terminer = true; 
                break;
                case SDL_KEYDOWN:
                    switch(evenements->key.keysym.sym) {

                        case SDLK_q:
                            world->terminer = true; 
                        break; 

                        case SDLK_r:
                            world->ball.x = 378; 
                            world->ball.y = 292;
                        break; 

                        case SDLK_SPACE:
                            if(world->powerPress < 20) {
                                world->powerPress ++;
                            }
                        break;
                        case SDLK_p:
                            world->status = PAUSE ;
                            printf("p");
                        break;
                    }
                break;
                case SDL_KEYUP:

                    switch(evenements->key.keysym.sym) {

                        case SDLK_SPACE:
                            world->tir = false;
                            world->ball.power = world->powerPress;
                            world->ball.dirX = cos(world->arrow.angle * PI / 180) * world->ball.power;
                            world->ball.dirY = sin(world->arrow.angle * PI / 180) * world->ball.power;
                            world->powerPress = 0;
                            world->nbCoups++ ;
                        break; 

                    }
                break;  
                case SDL_MOUSEBUTTONDOWN:  
                        if (evenements->button.button == SDL_BUTTON_LEFT){
                            display_arrow(world);
                        }   
                break;    
            
            }
        }
        if (world->status == PAUSE)
        {
            switch (evenements->type)
            {
            case SDL_KEYDOWN:
                switch(evenements->key.keysym.sym) {
                    case SDLK_ESCAPE:
                        printf("Jouer");
                        world->status = JOUER ;
                        break;


                }
            break;
             case SDL_MOUSEBUTTONDOWN:
                if (evenements->button.button == SDL_BUTTON_LEFT)
                {
                    if(pointeur_collision(world->reprendre)){

                        world->status = JOUER ;

                    }
                    if(pointeur_collision(world->sauv)){
                        enregistrer_world_s("Sauvegarde.txt",world);
                        world->status = LANCEMENT ;
                    }
                }

            }
        }
        if(world->status == LANCEMENT){
            switch(evenements->type)
            {
                case SDL_KEYDOWN:
                    switch(evenements->key.keysym.sym) {

                        case SDLK_ESCAPE:
                            if (world->page != INIT)
                            {
                            textures->menu = NULL ;
                            world->page = INIT ;
                            }
                            else{
                                world->terminer = true ;
                                world->status = JOUER ;
                            }
                        break;
                        case SDLK_RETURN :
                        if (world->page == OPTION)
                        {
                            textures->menu = NULL ;
                            world->page = INIT ;
                        }
                        break;
                        case SDLK_BACKSPACE:
                            free(world->pseudo);
                            world->pseudo = malloc(sizeof(char)*32);
                            world->nbLettrePseudo = 0 ;
                            
                        break;

                    }
                break;
                case SDL_TEXTINPUT :
                        if (world->page == OPTION)
                        {
                            
                            strcat( world->pseudo,evenements->text.text);
                            printf("%s\n", evenements->text.text);
                            world->nbLettrePseudo++ ;
                        }
                        

                break;
                case SDL_MOUSEBUTTONDOWN:
                    if (evenements->button.button == SDL_BUTTON_LEFT)
                    {

                        int posx_e = 0 ;
                        int posy_e = 0 ;       
                        SDL_GetMouseState(&posx_e,&posy_e); 
                        if (world->page == INIT)
                        {
                            if (entre(world->buttons[0].x,posx_e,world->buttons[0].x+world->buttons[0].w) && entre(world->buttons[0].y,posy_e,world->buttons[0].y+world->buttons[0].h)){
                                textures->menu = NULL ;
                                world->page = LANCE_GAME ;
                            }
                            if (entre(world->buttons[2].x,posx_e,world->buttons[2].x+world->buttons[2].w) && entre(world->buttons[2].y,posy_e,world->buttons[2].y+world->buttons[2].h)){
                            textures->menu = NULL ;
                            world->page = OPTION ;                    
                            }
                            if (entre(world->buttons[4].x,posx_e,world->buttons[4].x+world->buttons[4].w) && entre(world->buttons[4].y,posy_e,world->buttons[4].y+world->buttons[4].h)){
                                printf("finn");
                                world->terminer = true ;
                                world->status = JOUER ;
                            }
                        }
                        if (world->page == LANCE_GAME)
                        {
                            if (pointeur_collision(world->lancer)){
                                world->status = JOUER ;
                            }
                            if (pointeur_collision(world->recommencer))
                            {
                                world->status = JOUER ;
                            }
                        }
                        
                        
                    }
                break;
                    
            }
        }

        
    }
}
