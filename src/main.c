#include <stdio.h>
#include <SDL3/SDL.h>
#include <math.h>

#include "constants.h"
#include "game_typedef.h"
#include "game_functions.h"
#include "game_physics.h"
#include "camera.h"

int running = 1;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *world_texture = NULL;

static void DestroyWorld(void);

int main(void) {
    WORLD world = {WORLD_WIDTH, WORLD_HEIGHT, 0.0f, FIXED_TIME_STEP};
    Player player = {40.0f, 40.0f, 0};
    CAMERA camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 100.0f, 50.0f, 25.0f, 0};

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("a means to an end", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    world.platform_count = 3;
    world.platforms[0] = (PLATFORM){500, 800, 300, 20};  
    world.platforms[1] = (PLATFORM){800, 600, 200, 20};  
    world.platforms[2] = (PLATFORM){300, 400, 250, 20};  

    Uint64 last_time = SDL_GetTicks();
    float accumulator = 0.0f;

    while (running) {
        Uint64 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time;

        accumulator += delta_time;

        ProcessInput(&player, &running);

        while (accumulator >= world.time_step) {
            world.time_elapsed += world.time_step;

            UpdatePlayer(&world, &player);
            UpdateCamera(world, &camera, &player, world.time_step); // Use fixed time step
            accumulator -= world.time_step;
        }

        render(world ,renderer, player, &camera);

        // Smarter delay to maintain consistent timing
        Uint64 frame_end = SDL_GetTicks();
        float frame_time = (frame_end - current_time) / 1000.0f;
        float sleep_time = world.time_step - frame_time;
        if (sleep_time > 0) {
            SDL_Delay((Uint32)(sleep_time * 1000));
        }
    }

    DestroyWorld();
    return 0;
}

static void DestroyWorld(void) {
    SDL_DestroyTexture(world_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}