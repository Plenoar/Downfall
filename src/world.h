#ifndef WORLD_H
#define WORLD_H

#include <SDL3/SDL.h>
#include "typedef.h"
#include "constants.h"

int CreateWorld(SDL_Window *window,SDL_Renderer *renderer);
void InitializeWorld(WORLD *world);
void UpdateWorld(WORLD *world, USER *user, CAMERA *camera, CLYPE *clype ,double *θ, double *θ1, double *θ2, double deltaTime);
void WorldToScreen(const CAMERA *camera, double wx, double wy, double *sx, double *sy);
void DrawCircle(SDL_Renderer *renderer, CIRCLE circle, SDL_Color color);
void RenderWorld(WORLD *world,USER *user, SDL_Renderer *renderer,CLYPE *clype, double θ, double θ1, double θ2, CAMERA *camera);
int DestroyWorld(WORLD *world);


#endif