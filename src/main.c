#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "fonctions_fichiers.h"
#include "objet.h"
#include "sdl2-ttf-light.h"
#include "constante.h"
#include "graphique.h"
#include "menu.h"
#include "gestion.h"
#include "event.h"
#include "fonctions_fichiers.h"

        







void init(SDL_Renderer **renderer,SDL_Window** fenetre,textures_t* texture,world_t* world){
    init_data(world);
    init_textures(*renderer,texture,world);

}







int main(int argc, char *argv[]){
    //INIT
    SDL_Renderer *renderer;
    SDL_Window* fenetre; // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre
    world_t world;
    textures_t textures;




    //___________________Initialisation des données/texture du menu______________________
    world.status = LANCEMENT ;
    world.page = INIT ;
    world.init_sauv = false ;
    textures.menu = NULL ;
    world.nb_niveau = nombres_niveau() ;
    if (world.nb_niveau == 0)
    {
        printf("Probleme aucun niveau de disponible") ;
        exit(1);
    }
    world.CoupsTot = 0 ;
    world.current_level = 1;
    init_ttf();
    init_renderer(&renderer,&fenetre,&world);
    textures.font = load_font("ressources/arial.ttf",100);
    world.pseudo = malloc(sizeof(char)*32) ;
    char_array_empty(world.pseudo);
    world.nbLettrePseudo = 0 ;
    textures.buttons = malloc(sizeof(textures_t)*6);
    textures.buttons[0] = charger_image_transparente("ressources/jouer_b.bmp",renderer,255,255,255) ;
    textures.buttons[1] = charger_image_transparente("ressources/jouer_r.bmp",renderer,255,255,255) ;
    textures.buttons[2] = charger_image_transparente("ressources/opt_b.bmp",renderer,255,255,255) ;
    textures.buttons[3] = charger_image_transparente("ressources/opt_r.bmp",renderer,255,255,255) ;
    textures.buttons[4] = charger_image_transparente("ressources/stop_b.bmp",renderer,255,255,255) ;
    textures.buttons[5] = charger_image_transparente("ressources/stop_r.bmp",renderer,255,255,255) ;
    world.buttons = malloc(sizeof(sprite_t)*6);
    textures.sauv = charger_image_transparente("ressources/sauv_v.bmp",renderer,77, 93, 70);
    textures.sauv_a = charger_image_transparente("ressources/sauv_r.bmp",renderer,77, 93, 70);
    textures.reprendre = charger_image_transparente("ressources/reprendre_v.bmp",renderer,77, 93, 70);
    textures.reprendre_a = charger_image_transparente("ressources/reprendre_r.bmp",renderer,77, 93, 70);
    textures.pause = charger_image_transparente("ressources/pause.bmp",renderer,255,255,255);
    textures.lancer = charger_image_transparente("ressources/repPartie_v.bmp",renderer,64,124 ,77);
    textures.lancer_a = charger_image_transparente("ressources/repPartie_r.bmp",renderer,64,124 ,77);
    textures.recommencer = charger_image_transparente("ressources/nouvPartie_v.bmp",renderer,64,124 ,77 );
    textures.recommencer_a = charger_image_transparente("ressources/nouvPartie_r.bmp",renderer,64,124 ,77 );
    world.pause.y = 595;
    world.pause.x = 0 ;
    world.pause.w = 1280 ;
    world.pause.h = 125;
    world.sauv.x = 440;
    world.sauv.w = 400 ;
    world.sauv.h = 100 ;
    world.sauv.y = world.pause.y + 14;
    world.reprendre.x = 874 ;
    world.reprendre.y = world.pause.y + 14;
    world.reprendre.w = 400 ;
    world.reprendre.h = 100 ;
    world.CoupsTot = 0 ;

    world.lancer.x =  200;
    world.lancer.y =  400;
    world.lancer.w =  400;
    world.lancer.h =  100;

    world.recommencer.x =  700;
    world.recommencer.y =  400;
    world.recommencer.w =  400;
    world.recommencer.h =  100;


    int scr = 0 ;
    for (size_t i = 0; i < 3; i++)
        {
        for (int j = 0; j < 2; j++)   
        {
            world.buttons[scr].x = 440 ;
            world.buttons[scr].y = 267 + i*150 ;
            if(scr%2 != 0)
            {
                world.buttons[scr].w = 440 ;
                world.buttons[scr].h = 110 ;
                
            }
            else{
                world.buttons[scr].w =  400; 
                world.buttons[scr].h =  100;
            }
            scr++ ;
        }
    }
    
    world.terminer = false ;


    world.init = false ;

    

//_________________________________________________________________________________________________________

    // Boucle principale
    while(!world.terminer){
        while (world.status == LANCEMENT)
        {
            SDL_RenderClear(renderer);
            update_lancement(renderer,&world,&textures);
            handle_events(&evenements,&world,&textures);
            SDL_RenderPresent(renderer);
        }
        if(!world.init){
            init(&renderer,&fenetre,&textures,&world);
            world.init = true ;
        }
        while (world.status == PAUSE)
        {
            gestion_pause(renderer,&world,&textures);
            handle_events(&evenements,&world,&textures);
            SDL_RenderPresent(renderer);
        }
        
        if (!world.terminer)
        {
            if (world.status == JOUER && !world.terminer)
            {
                SDL_RenderClear(renderer);
                refresh_graphics(renderer,&world,&textures);
                handle_events(&evenements,&world,&textures);
                update_data(&world,renderer,&textures);
                
            }
            if (world.status == FIN && !world.terminer)
            {
                SDL_RenderClear(renderer);
                update_fin(renderer,&world,&textures);
                handle_events(&evenements,&world,&textures);
                SDL_RenderPresent(renderer);/* code */
            }
            
  
        SDL_Delay(20);
        SDL_RenderPresent(renderer);
        } 
    }
    enregistre_score("sorties/score.txt",&world) ;
    // Libérer de la mémoire
    clean_data(&world,&textures) ;
    SDL_DestroyRenderer(renderer);

    // Quitter SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}