#ifndef PROCESS_INPUT_H
#define PROCESS_INPUT_H

#include "typedef.h"
#include<SDL3/SDL.h>

void ProcessInput(SDL_Event event, USER *user, CAMERA *camera , int *running);

#endif