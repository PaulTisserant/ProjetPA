#ifndef MENU_H
#define MENU_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "fonctions_fichiers.h"
#include "objet.h"
#include <SDL2/SDL.h>
#include "sdl2-ttf-light.h"
#include "constante.h"
#include "graphique.h"
#include "objet.h"






int update_lancement(SDL_Renderer *renderer, world_t *world,textures_t *textures);
void gestion_pause(SDL_Renderer *renderer, world_t *world,textures_t *textures);
#endif