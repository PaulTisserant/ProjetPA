#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "objet.h"
#include <stdbool.h>

void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures);
void init_textures(SDL_Renderer *renderer,textures_t* texture,world_t* world);
void init_renderer(SDL_Renderer **renderer,SDL_Window** fenetre,world_t* world);
#endif