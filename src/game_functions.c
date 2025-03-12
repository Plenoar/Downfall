
#include "game_typedef.h"
#include<SDL3/SDL.h>


void UpdatePlayer(WORLD *world, Player *player) {
    float speed = (player->wasd & 32) ? 1000.0f : 600.0f;
    world->objects[0].vx = 0.0f;
    world->objects[0].vy = 0.0f;
    if (player->wasd & 1) world->objects[0].vy -= speed;  // W
    if (player->wasd & 4) world->objects[0].vy += speed;  // S
    if (player->wasd & 2) world->objects[0].vx -= speed;  // A
    if (player->wasd & 8) world->objects[0].vx += speed;  // D
    world->objects[0].x += world->objects[0].vx * world->time_step;
    world->objects[0].y += world->objects[0].vy * world->time_step;
    player->x_pos = world->objects[0].x;  // Sync player with object
    player->y_pos = world->objects[0].y;
}


void render(WORLD world, SDL_Renderer *renderer, Player player, CAMERA *camera) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw player with camera offset
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_FRect player_rect = {player.x_pos - camera->x, player.y_pos - camera->y, 50, 50};
    SDL_RenderFillRect(renderer, &player_rect);

    // Draw platforms with camera offset
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green platforms
    for (int i = 0; i < world.platform_count; i++) {
        SDL_FRect platform_rect = {world.platforms[i].x - camera->x, world.platforms[i].y - camera->y,
                                  world.platforms[i].width, world.platforms[i].height};
        SDL_RenderFillRect(renderer, &platform_rect);
    }

    SDL_RenderPresent(renderer);
}


void ProcessInput(Player *player, int *running)
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type) 
        {
            case SDL_EVENT_QUIT:
                *running =  0;
                break;

            case SDL_EVENT_MOUSE_REMOVED:

                break;

            case SDL_EVENT_KEYBOARD_REMOVED:

                break;

            case SDL_EVENT_MOUSE_MOTION: 
            {
                float x , y;
                SDL_GetMouseState(&x,&y);
                // needs update the mouse 
                break;
            }
            case SDL_EVENT_MOUSE_BUTTON_DOWN: 
            {
                // idk do something 
                break;
            }
            case SDL_EVENT_KEY_DOWN: {
                SDL_Keycode sym = event.key.key;
 
                    if (sym == SDLK_W) player->wasd |= 1;
                    if (sym == SDLK_A)player->wasd |= 2;
                    if (sym == SDLK_S)player->wasd |= 4;
                    if (sym == SDLK_D)player->wasd |= 8;
                    if (sym == SDLK_SPACE)player->wasd |= 16;
                    if (sym == SDLK_LSHIFT)player->wasd |= 32; // assigning 32 bit
                    // value for the sprint implementation , 32 in binary is  100000
                break;
            }
            case SDL_EVENT_KEY_UP:
            {
                SDL_Keycode sym = event.key.key; 
                    if (sym == SDLK_W)player->wasd &= ~1;
                    if (sym == SDLK_A)player->wasd &= ~2;
                    if (sym == SDLK_S)player->wasd &= ~4;
                    if (sym == SDLK_D)player->wasd &= ~8;
                    if (sym == SDLK_SPACE)player->wasd &= ~16; // this is to clear the bit 
                    if (sym == SDLK_LSHIFT)player->wasd &= ~32;  
            }
            break;
        }
    }
}

