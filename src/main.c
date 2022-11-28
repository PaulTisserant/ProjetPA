#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "liste.h"
#include "fonctions_fichiers.h"
#include <SDL2/SDL.h>

#define DEG 0.0174533
#define DEC 250
#define HAUT 100
void update_data(world_t* world){
    if (world->status = JOUER)
    {
        /* code */
    
    
        for (int i = 0; i < longueur(world->tour_terrain); i++)
        {
            sprite_t tourMur = neme_elem(i,world->tour_terrain) ;
            handle_sprites_collision(&(world->ball),&tourMur);
        }

        for (int i = 0; i < longueur(world->mur); i++)
        {
            sprite_t mur = neme_elem(i,world->mur) ;
            handle_sprites_collision(&(world->ball),&mur);
        }



        world->ball.x -= -world->ball.power * cos(world->ball.angle);
        world->ball.y -= world->ball.power *  -sin(world->ball.angle);


    
        if(world->ball.power > 0){
            world->ball.power -- ;
        }
    }
}
void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){
        apply_texture(textures->back,renderer,0,0,1280,720,0);
        if (world->status == JOUER){
            for (int i = 0; i < (world->colonne+2)*(world->ligne+2); i++) {
                apply_texture(textures->tile[i],renderer,world->tile[i].x,world->tile[i].y,world->tile[i].w,world->tile[i].h,0);
            }
            apply_texture(textures->ball,renderer,world->ball.x,world->ball.y,world->ball.w,world->ball.h,0);
            apply_texture(textures->hole,renderer,world->hole.x,world->hole.y,world->hole.w,world->hole.h,0);
            apply_texture(textures->arrow,renderer,world->arrow.x,world->arrow.y,world->arrow.w,world->arrow.h,world->arrow.angle);
            //printf("world->arrow.angle : %lf",world->arrow.angle);
        }
}

void handle_events(SDL_Event *evenements,world_t *world,textures_t *textures){
    bool pressed = false;
    
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
                        
                        case SDLK_SPACE:
                            pressed = true;
                            if(world->powerPress < 20) {
                                world->powerPress ++;
                            }
                        break;     
                    }
                break;
                case SDL_KEYUP:

                    switch(evenements->key.keysym.sym) {

                        case SDLK_SPACE:
                            for (int i = 0; i < world->powerPress; i++)
                            {
                                world->ball.power += 1;
                            } 
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
        else{
            switch(evenements->type)
            {
                case SDL_KEYDOWN:
                    switch(evenements->key.keysym.sym) {
                        case SDLK_a:
                        printf("JOUER \n");
                        world->status = JOUER ;
                        break;

                    }



                            

            }
        }
    }
}
        

void apply_lancement(SDL_Renderer *renderer, world_t *world,textures_t *textures){
    if (world->status == LANCEMENT)
    {
       switch (world->page)
       {
       case INIT:
                if (textures->menu == NULL)
                {
                    printf("null");
                    textures->menu = charger_image("menu.bmp",renderer);
                }
                
                
                apply_texture(textures->menu,renderer,0,0,1280,720,0);
        break;
       case OPTION:
       default:
        break;
       } 


    }
    




}
void init_data(world_t* world){
//---------------------Initialisation des sprites----------------------------------
    printf("init data \n");

    world->arrow.angle = 0 ;
    world->ball.power = 0 ;
    world->powerPress = 5 ;
    world->terminer = false ;
    int col = 0;
    int ligne = 0 ;
    int srcpos = 0 ;
    taille_fichier("hole2.txt", &(ligne), &(col)); // Initialisation du nombres de tuile dans le monde
    world->colonne = col ;
    world->ligne = ligne ;
    printf("ligne : %i,col:%i",col,ligne);
    world->tile = malloc(sizeof(sprite_t)*(world->colonne+2)*(world->ligne+2)) ;
    world->mur = l_vide() ;
    world->tour_terrain = l_vide() ;
    world->terrain = lire_fichier("hole2.txt");              
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
                    world->ball.w = 20 ;
                    world->ball.h = 20 ;
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
            }
            /*
            world->tile[srcpos].x = 32*j ;
            world->tile[srcpos].x = 32*i ;
            world->tile[srcpos].w = 32 ;
            world->tile[srcpos].h = 32 ;
            world->tile[srcpos].angle = 0 ;
            world->tile[srcpos].v = 0 ; 
            */
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
    world.status = LANCEMENT ;
    world.page = INIT ;
    textures.menu = NULL ;
    init_renderer(&renderer,&fenetre,&world);

    while (world.status == LANCEMENT)
    {
        apply_lancement(renderer,&world,&textures);
        handle_events(&evenements,&world,&textures);
        SDL_RenderPresent(renderer);

    }
    

    init(&renderer,&fenetre,&textures,&world);
    SDL_DestroyTexture(textures.menu);

    // Boucle principale
    while(!world.terminer){
        SDL_RenderClear(renderer);
        refresh_graphics(renderer,&world,&textures);
        handle_events(&evenements,&world,&textures);
        update_data(&world);
        Uint64 currentTick = SDL_GetPerformanceCounter();
        Uint64 lastTick = 0;
        double deltaTime = 0;
        int power = 0 ;
        lastTick = currentTick;
        currentTick = SDL_GetPerformanceCounter();
        deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency() );
        SDL_Delay(20);
        //SDL_RenderCopyEx(renderer, arrow,&SrcR_arrow,&DestR_arrow,angle * 180/3.14159,NULL,SDL_FLIP_NONE);

  

        SDL_RenderPresent(renderer);
    }


    // Libérer de la mémoire
    SDL_DestroyTexture(textures.hole);
    SDL_DestroyTexture(textures.ball);
    SDL_DestroyRenderer(renderer);

    // Quitter SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}