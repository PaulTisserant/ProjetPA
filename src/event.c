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
                            //gestion de la puissance du tir
                            if(world->powerPress < 20) {
                                world->powerPress ++;
                                world->rect.w+=5 ;

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
                            //gestion du tir
                            world->tir = false;
                            world->ball.power = world->powerPress;
                            world->ball.dirX = cos(world->arrow.angle * PI / 180) * world->ball.power;
                            world->ball.dirY = sin(world->arrow.angle * PI / 180) * world->ball.power;
                            world->powerPress = 0;
                            world->nbCoups++ ;
                            world->CoupsTot++ ;

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
                        enregistrer_world_s("sorties/Sauvegarde.txt",world);
                        textures->menu = NULL ;
                        world->status = LANCEMENT ;
                        world->page = INIT ;
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
                            //suprssion du pseudo
                            free(world->pseudo);
                            world->pseudo = malloc(sizeof(char)*32);
                            world->nbLettrePseudo = 0 ;
                            
                        break;

                    }
                break;
                case SDL_TEXTINPUT :
                        if (world->page == OPTION)
                        {
                            
                            strcat( world->pseudo,evenements->text.text); // concatene le pseudo avec le texte entree par l'utilisateur
                            printf("%s\n", evenements->text.text);
                            world->nbLettrePseudo++ ;
                        }
                        

                break;
                case SDL_MOUSEBUTTONDOWN:
                    if (evenements->button.button == SDL_BUTTON_LEFT)
                    {


                        if (world->page == INIT)
                        {
                            if (pointeur_collision(world->buttons[0])){
                                textures->menu = NULL ;
                                world->page = LANCE_GAME ;
                            }
                            if (pointeur_collision(world->buttons[2])){
                            textures->menu = NULL ;
                            world->page = OPTION ;                    
                            }
                            if (pointeur_collision(world->buttons[4])){
                                world->terminer = true ;
                                world->status = JOUER ;
                            }
                        }
                        if (world->page == LANCE_GAME)
                        {
                            if (pointeur_collision(world->lancer)){
                                world->init_sauv = true ;
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
        if (world->status == FIN)
        {
            switch (evenements->type)
            {
            case SDL_KEYDOWN:
                switch(evenements->key.keysym.sym) {
                    case SDLK_RETURN :
                    //fin du jeu
                    world->terminer = true ;
                    break;
                }
            break;
            }   
    }
}
}
