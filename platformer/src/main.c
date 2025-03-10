#include <stdio.h>
#include<SDL3/SDL.h>
#include <math.h>



#define FIXED_TIME_STEP (1.0f / 160.0f) // 160 updates per second
//This means each update happens every 0.00625 seconds (6.25ms).

int running = 1;

#define WINDOW_WIDTH 1700
#define WINDOW_HEIGHT 1000

const float PIXELS_PER_METER = 1000.0f;   // 1 meter = 1000 pixels
const float METERS_PER_PIXEL = 1.0f / PIXELS_PER_METER; // 1 pixel = 0.001 meters

const float PIXELS_PER_CM = 10.0f;    // 1 cm = 10 pixels
const float CM_PER_PIXEL = 1.0f / PIXELS_PER_CM; // 1 pixel = 0.1 cm

const float CM_PER_METER = 100.0f;   // 1 meter = 100 cm
const float METERS_PER_CM = 1.0f / CM_PER_METER; // 1 cm = 0.01 meters

const float KILOMETER = 1000000.0f; // 1,000,000 pixels per kilometer

typedef struct 
{
    float x, y;     // Position in world coordinates
    float vx, vy;   // Velocity components
    float width, height; // Size of object
} OBJECT;

typedef struct
{
    float width ;
    float height ;
    float time_elapsed;
    float time_step; 
    OBJECT objects[100];
}WORLD;

typedef struct 
{   

    float x_pos; // x postition 
    float y_pos; // y position 
    unsigned char wasd; // bit manipulation for events 
}Player;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

// function declarations 
void UpdatePhysics(WORLD *world, Player *player);
void ProcessInput(Player *player, int *running);
void render(SDL_Renderer *renderer, Player player);
static void Pause();
static void DestroyWorld(void);

int main(void)
{
    WORLD world = {KILOMETER, KILOMETER, 0.0f, FIXED_TIME_STEP};
    Player player = {0.0f, 0.0f , 0};
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("a means to an end ",WINDOW_WIDTH,WINDOW_HEIGHT,0,&window,&renderer);

    
    Uint64 last_time = SDL_GetTicks();
    float accumulator = 0.0f;

    while (running)
    {
        Uint64 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time;

        accumulator += delta_time;

        ProcessInput(&player, &running);

        while (accumulator >= world.time_step)
        {
            world.time_elapsed += world.time_step;

            UpdatePhysics(&world,&player);

            accumulator -= world.time_step;
            
        }
            // update the surface 
            render(renderer , player);

        // Smarter delay to maintain consistent timing
        Uint64 frame_end = SDL_GetTicks();
        float frame_time = (frame_end - current_time) / 1000.0f;
        float sleep_time = world.time_step - frame_time;
        if (sleep_time > 0)
        {
            SDL_Delay((Uint32)(sleep_time * 1000));
        }

    }
    DestroyWorld();
    return 0;
}

void UpdatePhysics(WORLD *world,Player *player)
{
    float speed = (player->wasd & 32) ? 1500.0f : 1000.0f;
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

void render(SDL_Renderer *renderer, Player player)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_FRect rect = {player.x_pos, player.y_pos, 50, 50};
    SDL_RenderFillRect(renderer, &rect);
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
                Pause();
                break;

            case SDL_EVENT_KEYBOARD_REMOVED:
                Pause();
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

static void Pause()
{
    // hold up the pause window 
}

static void DestroyWorld(void)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


