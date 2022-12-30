#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "fonctions_fichiers.h"
#include "objet.h"
#include "sdl2-ttf-light.h"

#ifndef EVENT_H
#define EVENT_H

void handle_events(SDL_Event *evenements,world_t *world,textures_t *textures);

#endif