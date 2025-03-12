#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include "game_typedef.h"


// Function declarations
void UpdatePlayer(WORLD *world , Player *player);
void ProcessInput(Player *player, int *running);
void render(WORLD world, SDL_Renderer *renderer, Player player, CAMERA *camera);



#endif // GAME_FUNCTIONS_H
