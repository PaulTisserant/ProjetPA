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
#define ball_size 10

void update_data(world_t* world){
    if (world->status == JOUER)
    {
        /* code */


        for (int i = 0; i < longueur(world->tour_terrain); i++)
        {
            sprite_t tourmur = neme_elem(i,world->tour_terrain) ;
            //if(handle_sprites_collision(&(world->ball),&mur) == 1){
                //world->terminer = true ;
            //};

            int newX = world->ball.x + world->ball.power;
            int newY = world->ball.y;
            //si on augmente x (prochaine frame) et qu'il y aura une collision alors on inverse x 
            if (newX + ball_size > tourmur.x && newX < tourmur.x + tourmur.w && newY + ball_size > tourmur.y && newY < tourmur.y + tourmur.h)
            {
                world->ball.dirX *= -1;
                world->tir = true;
                
                world->ball.power-- ;
                
            }

            newX = world->ball.x;
            newY = world->ball.dirY + world->ball.power;
            //si on augmente y (prochaine frame) et qu'il y aura une world->tir alors on inverse y
            if (newX + ball_size > tourmur.x && newX < tourmur.x + tourmur.w && newY + ball_size > tourmur.y && newY < tourmur.y + tourmur.h)
            {
                world->ball.dirY *= -1;
                world->tir = true;
                world->ball.power-- ;

            }

            newX = world->ball.x - world->ball.power;
            newY = world->ball.y;
            //si on diminue x (prochaine frame) et qu'il y aura une world->tir alors on inverse y 
            if (newX + ball_size > tourmur.x && newX < tourmur.x + tourmur.w && newY + ball_size > tourmur.y && newY < tourmur.y + tourmur.h)
            {
                world->ball.dirY *= -1;
                world->tir = true;
                world->ball.power-- ;
            }

            newX = world->ball.x;
            newY = world->ball.dirY - world->ball.power;
            //si on diminue y (prochaine frame) et qu'il y aura une world->tir alors on inverse x
            if (newX + ball_size > tourmur.x && newX < tourmur.x + tourmur.w && newY + ball_size > tourmur.y && newY < tourmur.y + tourmur.h)
            { 
                world->ball.dirX *= -1;
                world->tir = true;   
                world->ball.power-- ;      
            }
        }



        if (!world->tir)
        {
            world->ball.dirX = -world->ball.power * cos(world->ball.angle);
            world->ball.dirY = world->ball.power * -sin(world->ball.angle);
            printf("%ld\n", world->ball.angle);
        } 
        



        for (int i = 0; i < longueur(world->mur); i++)
        {
            sprite_t mur = neme_elem(i,world->mur) ;
            //if(handle_sprites_collision(&(world->ball),&mur) == 1){
                //world->terminer = true ;
            //};

            int newX = world->ball.x + world->ball.power;
            int newY = world->ball.y;
            //si on augmente x (prochaine frame) et qu'il y aura une collision alors on inverse x 
            if (newX + ball_size > mur.x && newX < mur.x + mur.w && newY + ball_size > mur.y && newY < mur.y + mur.h)
            {
                world->ball.dirX *= -1;
                world->tir = true;
                
                world->ball.power-- ;
                
            }

            newX = world->ball.x;
            newY = world->ball.dirY + world->ball.power;
            //si on augmente y (prochaine frame) et qu'il y aura une world->tir alors on inverse y
            if (newX + ball_size > mur.x && newX < mur.x + mur.w && newY + ball_size > mur.y && newY < mur.y + mur.h)
            {
                world->ball.dirY *= -1;
                world->tir = true;
                world->ball.power-- ;

            }

            newX = world->ball.x - world->ball.power;
            newY = world->ball.y;
            //si on diminue x (prochaine frame) et qu'il y aura une world->tir alors on inverse y 
            if (newX + ball_size > mur.x && newX < mur.x + mur.w && newY + ball_size > mur.y && newY < mur.y + mur.h)
            {
                world->ball.dirY *= -1;
                world->tir = true;
                world->ball.power-- ;
            }

            newX = world->ball.x;
            newY = world->ball.dirY - world->ball.power;
            //si on diminue y (prochaine frame) et qu'il y aura une world->tir alors on inverse x
            if (newX + ball_size > mur.x && newX < mur.x + mur.w && newY + ball_size > mur.y && newY < mur.y + mur.h)
            { 
                world->ball.dirX *= -1;
                world->tir = true;   
                world->ball.power-- ;      
            }
        }


        // il faut stocker la nouvelle direction pour que dans les prochaines frame la direction ne soit plus celle de la fleche 
        // une fois la balle arretée il faudrat reprendre la direction de la fleche 
        printf("x: %ld \n",world->ball.dirX);
        printf("y :%ld\n",world->ball.dirY);
        if (world->ball.power > 0)
        {
        world->ball.x -= world->ball.dirX * 0.8;
        world->ball.y -= world->ball.dirY * 0.8;
        }
        




    
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

                        case SDLK_r:
                            world->ball.x = 378; 
                            world->ball.y = 292;
                        break; 
                        
                        case SDLK_SPACE:
                            pressed = true;
                            if(world->powerPress < 20) {
                                world->powerPress ++;
                            }
                        break;  
                        case SDLK_ESCAPE:
                            world->status = PAUSE ;
                            printf("escape");
                        break;   
                    }
                break;
                case SDL_KEYUP:

                    switch(evenements->key.keysym.sym) {

                        case SDLK_SPACE:
                            world->tir = false;
                            world->ball.power = 0;
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
                    case SDLK_o:
                     printf("options \n");
                     textures->menu = NULL ;
                     world->page = OPTION ;
                    break;
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
                            world->status = JOUER ;
                        }
                        if (entre(world->buttons[2].x,posx_e,world->buttons[2].x+world->buttons[2].w) && entre(world->buttons[2].y,posy_e,world->buttons[2].y+world->buttons[2].h)){
                        textures->menu = NULL ;
                        world->page = OPTION ;                    
                        }
                        if (entre(world->buttons[4].x,posx_e,world->buttons[4].x+world->buttons[4].w) && entre(world->buttons[4].y,posy_e,world->buttons[4].y+world->buttons[4].h)){
                            world->terminer = true ;
                            world->status = JOUER ;
                        }
                    }
                    
                }
            break;
                
        }


                        

        }
    }
}
        
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
        if (entre(world->buttons[0].x,posx,world->buttons[0].x+world->buttons[0].w) && entre(world->buttons[0].y,posy,world->buttons[0].y+world->buttons[0].h)){
            apply_texture(textures->buttons[1],renderer,world->buttons[1].x,world->buttons[1].y,world->buttons[1].w,world->buttons[1].h,0);
        }
        else{
            apply_texture(textures->buttons[0],renderer,world->buttons[0].x,world->buttons[0].y,world->buttons[0].w,world->buttons[0].h,0);
        }
        if (entre(world->buttons[2].x,posx,world->buttons[2].x+world->buttons[2].w) && entre(world->buttons[2].y,posy,world->buttons[2].y+world->buttons[2].h)){
            apply_texture(textures->buttons[3],renderer,world->buttons[3].x,world->buttons[3].y,world->buttons[3].w,world->buttons[3].h,0);
        
        }
        else{
            apply_texture(textures->buttons[2],renderer,world->buttons[2].x,world->buttons[2].y,world->buttons[2].w,world->buttons[2].h,0);
        }
        if (entre(world->buttons[4].x,posx,world->buttons[4].x+world->buttons[4].w) && entre(world->buttons[4].y,posy,world->buttons[4].y+world->buttons[4].h)){
            apply_texture(textures->buttons[5],renderer,world->buttons[5].x,world->buttons[5].y,world->buttons[5].w,world->buttons[5].h,0);

        }
        else{
            apply_texture(textures->buttons[4],renderer,world->buttons[4].x,world->buttons[4].y,world->buttons[4].w,world->buttons[4].h,0);
            
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
    int col = 0;
    int ligne = 0 ;
    int srcpos = 0 ;
    taille_fichier("hole.txt", &(ligne), &(col)); // Initialisation du nombres de tuile dans le monde
    world->colonne = col ;
    world->ligne = ligne ;
    printf("ligne : %i,col:%i",col,ligne);
    world->tile = malloc(sizeof(sprite_t)*(world->colonne+2)*(world->ligne+2)) ;
    world->mur = l_vide() ;
    world->tour_terrain = l_vide() ;
    world->terrain = lire_fichier("hole.txt");              
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
void init_lancement(SDL_Renderer* renderer,world_t* world,textures_t* texture){
    
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

    world.buttons = malloc(sizeof(sprite_t)*6);
    textures.buttons = malloc(sizeof(textures_t)*6);
    
    textures.buttons[0] = charger_image_transparente("jouer_b.bmp",renderer,255,255,255) ;
    textures.buttons[1] = charger_image_transparente("jouer_r.bmp",renderer,255,255,255) ;
    textures.buttons[2] = charger_image_transparente("opt_b.bmp",renderer,255,255,255) ;
    textures.buttons[3] = charger_image_transparente("opt_r.bmp",renderer,255,255,255) ;
    textures.buttons[4] = charger_image_transparente("stop_b.bmp",renderer,255,255,255) ;
    textures.buttons[5] = charger_image_transparente("stop_r.bmp",renderer,255,255,255) ;
    
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

    

    


    // Boucle principale
    while(!world.terminer){
        while (world.status == LANCEMENT)
        {
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
            handle_events(&evenements,&world,&textures);
            SDL_RenderPresent(renderer);
        }
        
        if (!world.terminer)
        {
        SDL_RenderClear(renderer);
        refresh_graphics(renderer,&world,&textures);
        handle_events(&evenements,&world,&textures);
        update_data(&world);
        SDL_Delay(20);
        //SDL_RenderCopyEx(renderer, arrow,&SrcR_arrow,&DestR_arrow,angle * 180/3.14159,NULL,SDL_FLIP_NONE);

  

        SDL_RenderPresent(renderer);
        }
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