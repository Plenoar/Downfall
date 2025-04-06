#include "typedef.h"
#include <SDL3/SDL.h>
#include "constants.h"

#define CAMERA_SMOOTH_FACTOR 0.1f  // Dead zone smoothing
#define CAMERA_LOOKAHEAD_FACTOR 0.05f  // Lookahead smoothing
#define CAMERA_FPS_NORMALIZE 60.0f  // Normalize to 60 FPS

void UpdateCamera(WORLD world, CAMERA *camera, USER *user, float deltaTime) {
    if (camera->locked) return;

    // Define dead zone boundaries (centered on camera)
    float deadzone_left = camera->x + (camera->width - camera->deadzone_x) / 2;
    float deadzone_right = camera->x + (camera->width + camera->deadzone_x) / 2;
    float deadzone_top = camera->y + (camera->height - camera->deadzone_y) / 2;
    float deadzone_bottom = camera->y + (camera->height + camera->deadzone_y) / 2;

    // Adjust camera if user exits dead zone
    float smooth = CAMERA_SMOOTH_FACTOR * deltaTime * CAMERA_FPS_NORMALIZE;
    if (user->x_pos < deadzone_left) {
        camera->x -= (deadzone_left - user->x_pos) * smooth;
    } else if (user->x_pos > deadzone_right) {
        camera->x += (user->x_pos - deadzone_right) * smooth;
    }
    if (user->y_pos < deadzone_top) {
        camera->y -= (deadzone_top - user->y_pos) * smooth;
    } else if (user->y_pos > deadzone_bottom) {
        camera->y += (user->y_pos - deadzone_bottom) * smooth;
    }

    // Apply lookahead based on movement direction
    float lookahead_target = (user->movement & M_A) ? -camera->lookahead :
                            (user->movement & M_D) ? camera->lookahead : 0;
    float target_x = user->x_pos - camera->width / 2 + lookahead_target;
    float lookahead_smooth = CAMERA_LOOKAHEAD_FACTOR * deltaTime * CAMERA_FPS_NORMALIZE;
    camera->x += (target_x - camera->x) * lookahead_smooth;

    // Clamp to world bounds
    camera->x = SDL_max(0, SDL_min(world.width - camera->width, camera->x));
    camera->y = SDL_max(0, SDL_min(world.height - camera->height, camera->y));
}