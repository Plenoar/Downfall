#include <stdio.h>
#include <SDL3/SDL.h>

#include "typedef.h"
#include "constants.h"
#include "camera.h"
#include "world.h"
#include "processinput.h"
#include "processuser.h"


static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

void init_world(WORLD *world) {
    world->width = WORLD_WIDTH;
    world->height = WORLD_HEIGHT;
    world->time_step = FIXED_TIME_STEP;
    world->time_elapsed = 0.0; // Add this if missing
    world->platform_count = 5; // Ground + 3 platforms
    world->platforms = malloc(sizeof(Platform) * world->platform_count);

    // x , y, width , height 
    world->platforms[0] = (Platform){0, WORLD_HEIGHT - GROUND_THICKNESS, WORLD_WIDTH, GROUND_THICKNESS, WHITE_COLOUR};
    // Example platforms
    world->platforms[1] = (Platform){1000, WORLD_HEIGHT - 100, 200, 20, WHITE_COLOUR};
    world->platforms[2] = (Platform){1500, WORLD_HEIGHT - 200, 150, 20, {0, 0, 255, 255}};
    world->platforms[3] = (Platform){2000, WORLD_HEIGHT - 300, 100, 20, {255, 0, 0, 255}};
    
    world->platforms[4] = (Platform){2500, WORLD_HEIGHT - 400, 200, 20, WHITE_COLOUR};
    // world->platforms[5] = (Platform){3000, WORLD_HEIGHT - 500, 250, 20, {255, 0, 0, 255}};

}

void UpdateWorld(WORLD *world, USER *user, CAMERA *camera, CLYPE *clype ,double *θ, double *θ1, double *θ2, double deltaTime) {
    ProcessUser(world,user, deltaTime); // Move user update here for fixed timestep
    UpdateCamera(*world, camera, user, (float)deltaTime);
    // NewUpdateCamera(*world, camera, user, (float)deltaTime);


    double θ_speed = 1.0;  // Radians per second
    double θ1_speed = 2.0;
    double θ2_speed = 4.0;
    *θ += θ_speed * deltaTime;
    *θ1 += θ1_speed * deltaTime;
    *θ2 += θ2_speed * deltaTime;
}
int main(void) 
{
    SDL_Init(SDL_INIT_VIDEO); 

    if (SDL_CreateWindowAndRenderer("Fourier Transformation Drawing", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) < 0) {
        printf("SDL_CreateWindowAndRenderer failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    WORLD world = {KILOMETER, KILOMETER, 0.0, FIXED_TIME_STEP};
    USER user = {
        .radius = 25.0,  // Half of the rendered 50x50 rect
        .height = 50.0,
        .x_vel = 0.0,
        .y_vel = 0.0,
        .x_pos = 100.0,  // Start at (100, 100)
        .y_pos = 100.0,
        .mouse_x = 0.0,
        .mouse_y = 0.0,
        .wheel = 0.0,
        .movement = 0,
        .actions = 0,
        .ui = 0
    };

    CLYPE clype = {2 * PIXELS_PER_METER, 1 * PIXELS_PER_METER};

    CAMERA camera = {
        .x = 0.0,
        .y = 0.0,
        .width = WINDOW_WIDTH,  // Initial view covers half the world
        .height = WINDOW_HEIGHT - 200,
        .lookahead = 100.0,
        .deadzone_x = 50.0,
        .deadzone_y = 25.0,
        .locked = 0
    };
    double θ = 0.0, θ1 = 0.0, θ2 = 0.0;
    
    init_world(&world);

    SDL_Event event;
    int running = 1;
    Uint64 lastCounter = SDL_GetPerformanceCounter();
    Uint64 frequency = SDL_GetPerformanceFrequency();
    double accumulator = 0.0;

    while (running) {
        Uint64 currentCounter = SDL_GetPerformanceCounter();
        double delta_time = (double)(currentCounter - lastCounter) / frequency;
        lastCounter = currentCounter;

        accumulator += delta_time;

        
        while (accumulator >= world.time_step) {
            world.time_elapsed += world.time_step;
            UpdateWorld(&world, &user, &camera,&clype, &θ, &θ1, &θ2, world.time_step);
            accumulator -= world.time_step;
        }
        
        RenderWorld(&world ,&user, renderer,&clype, θ, θ1, θ2, &camera);
        ProcessInput(event, &user, &camera, &running);

        // Calculate and display FPS
        double fps = (delta_time > 0.000001) ? 1.0 / delta_time : 0.0; // Prevent division by zero
        printf("Frame Time: %.6f sec | FPS: %.2f\n", delta_time, fps);
    }

    // Cleanup
    SDL_Quit();
    return 0;
}

// gcc -I C:/SDL3/x86_64-w64-mingw32/include -L C:/SDL3/x86_64-w64-mingw32/lib main.c camera.c processinput.c processuser.c world.c -lSDL3  -o main.exe
// ./main