#include <stdio.h>
#include <SDL3/SDL.h>
#include <math.h>

#define FIXED_TIME_STEP (1.0f / 160.0f) // 160 updates per second
#define WINDOW_WIDTH 1700
#define WINDOW_HEIGHT 1000
#define WORLD_WIDTH 10000  // Reduced from KILOMETER for practicality
#define WORLD_HEIGHT 2000

static const float PIXELS_PER_METER = 1000.0f;
static const float METERS_PER_PIXEL = 1.0f / PIXELS_PER_METER;
static const float PIXELS_PER_CM = 10.0f;
static const float CM_PER_PIXEL = 1.0f / PIXELS_PER_CM;
static const float CM_PER_METER = 100.0f;
static const float METERS_PER_CM = 1.0f / CM_PER_METER;
static const float KILOMETER = 1000000.0f;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *world_texture = NULL;

int running = 1;

typedef struct {
    float x, y;     // Position in world coordinates
    float vx, vy;   // Velocity components
    float width, height; // Size of object
} OBJECT;

typedef struct {
    float x, y;     // Position
    float width, height; // Size
} PLATFORM;

typedef struct {
    float x_pos;    // x position
    float y_pos;    // y position
    unsigned char wasd; // Bit manipulation for events
} Player;

typedef struct {
    float width;
    float height;
    float time_elapsed;
    float time_step;
    Player player;
    OBJECT objects[100];
    PLATFORM platforms[10]; // Up to 10 platforms
    int platform_count;     // Number of platforms
} WORLD;

typedef struct {
    float x, y;       // Camera position
    float width, height;  // Camera viewport size
    float lookahead;   // How much the camera looks ahead
    float deadzone_x;  // Dead zone width
    float deadzone_y;  // Dead zone height
    int locked;        // If the camera should stay fixed
} CAMERA;

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
void UpdateCamera(WORLD world, CAMERA *camera, Player *player, float deltaTime) {
    if (camera->locked) return;

    float deadzone_left = camera->x + (camera->width - camera->deadzone_x) / 6;
    float deadzone_right = camera->x + (camera->width + camera->deadzone_x) / 4;
    float deadzone_top = camera->y + (camera->height - camera->deadzone_y) / 2;
    float deadzone_bottom = camera->y + (camera->height + camera->deadzone_y) / 2;

    // Horizontal movement with dead zone
    if (player->x_pos < deadzone_left) {
        camera->x -= (deadzone_left - player->x_pos) * 0.3f * deltaTime * 60.0f;
    } else if (player->x_pos > deadzone_right) {
        camera->x += (player->x_pos - deadzone_right) * 0.3f * deltaTime * 60.0f;
    }

    // Lookahead: Adjust camera based on movement direction
    float lookahead_target = (player->wasd & 2) ? -camera->lookahead : (player->wasd & 8) ? camera->lookahead : 0;
    float target_x = player->x_pos - camera->width / 2 + lookahead_target;
    camera->x += (target_x - camera->x) * 0.1f * deltaTime * 60.0f;

    // Vertical movement with dead zone
    if (player->y_pos < deadzone_top) {
        camera->y -= (deadzone_top - player->y_pos) * 0.3f * deltaTime * 60.0f;
    } else if (player->y_pos > deadzone_bottom) {
        camera->y += (player->y_pos - deadzone_bottom) * 0.3f * deltaTime * 60.0f;
    }

    // Clamp camera to world bounds
    camera->x = SDL_max(0, SDL_min(world.width - camera->width, camera->x));
    camera->y = SDL_max(0, SDL_min(world.height - camera->height, camera->y));
}

void UpdatePhysics(WORLD *world) {
    // Apply gravity
    float player_bottom = world->player.y_pos + 50; // Player's bottom edge
    int on_ground = 0;

    // Check collision with platforms
    for (int i = 0; i < world->platform_count; i++) {
        PLATFORM *plat = &world->platforms[i];
        if (player_bottom >= plat->y && world->player.y_pos <= plat->y &&
            world->player.x_pos + 50 >= plat->x && world->player.x_pos <= plat->x + plat->width) {
            world->player.y_pos = plat->y - 50; // Snap player to platform top
            on_ground = 1;
            break;
        }
    }

    // Apply gravity if not on ground
    if (!on_ground) {
        world->player.y_pos += 9.81f * world->time_step * PIXELS_PER_METER; // Realistic gravity
    } 
}

static void DestroyWorld(void) {
    SDL_DestroyTexture(world_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(void) {
    WORLD world = {WORLD_WIDTH, WORLD_HEIGHT, 0.0f, FIXED_TIME_STEP};
    Player player = {25.0f, 10.0f, 0}; // Start at (25, 10) 
    CAMERA camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 50.0f, 500.0f, 250.0f, 0}; // Match window size

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("a means to an end", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    // Create world texture for static elements
    world_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                     WORLD_WIDTH, WORLD_HEIGHT);
    SDL_SetRenderTarget(renderer, world_texture);
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Light blue background
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);

    // Initialize platforms
    world.platform_count = 4; // Number of platforms
    world.platforms[0] = (PLATFORM){500, 800, 300, 20};  // Ground platform
    world.platforms[1] = (PLATFORM){800, 600, 200, 20};  // Mid-level platform
    world.platforms[2] = (PLATFORM){300, 400, 250, 20};  // Higher platform
    world.platforms[3] = (PLATFORM){1200, 700, 150, 20}; // Another platform

    // Center camera on player initially

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
            UpdatePhysics(&world);
            UpdatePlayer(&world, &player);
            UpdateCamera(world, &camera, &player, world.time_step);
            accumulator -= world.time_step;
        }

        // Render with camera
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
