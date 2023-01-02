#ifndef GESTION_H
#define GESTION_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "fonctions_fichiers.h"
#include "objet.h"
#include "sdl2-ttf-light.h"


void apply_friction(world_t* world) ;
bool check_tile_collision(sprite_t ball, sprite_t mur);
void init_data_file(world_t* world);
void init_data(world_t* world);
void int_to_char(char* score_txt,int score);
void update_data(world_t* world,SDL_Renderer *renderer,textures_t* texture) ;
void next_level(world_t* world,SDL_Renderer *renderer,textures_t* texture);
#endif