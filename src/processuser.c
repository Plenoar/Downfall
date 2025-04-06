#include "typedef.h"
#include "constants.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include<stdlib.h>

#define GRAVITY 980.0  // cm/s² (realistic gravity)
#define JUMP_VELOCITY -600.0  // Initial upward velocity for jump
#define PLAYER_SPEED 600.0  // Normal speed
#define PLAYER_SPRINT_SPEED 1000.0  // Sprint speed with LShift

void ProcessUser(WORLD *world, USER *user, double deltaTime) {
    double speed = (user->movement & M_LSHIFT) ? PLAYER_SPRINT_SPEED : PLAYER_SPEED;

    // Horizontal movement
    user->x_vel = 0.0;
    if (user->movement & M_A) user->x_vel = -speed;
    if (user->movement & M_D) user->x_vel = speed;

    // Apply gravity
    user->y_vel += GRAVITY * deltaTime;

    // Update position
    double new_x = user->x_pos + user->x_vel * deltaTime;
    double new_y = user->y_pos + user->y_vel * deltaTime;

    // Ground and platform collision
    double bound_x = WORLD_WIDTH - user->radius;
    double bound_y = WORLD_HEIGHT - user->radius;
    int on_ground = 0;

    // Check ground collision
    if (new_y + user->radius > WORLD_HEIGHT) {
        new_y = WORLD_HEIGHT - user->radius;
        user->y_vel = 0;
        on_ground = 1;
    }

    // Check platform collisions
    for (int i = 0; i < world->platform_count; i++) {
        Platform *p = &world->platforms[i];
        if (new_x + user->radius > p->x && 
            new_x - user->radius < p->x + p->width &&
            new_y + user->radius > p->y && 
            new_y - user->radius < p->y + p->height) {
            if (user->y_vel > 0 && user->y_pos + user->radius <= p->y) { // Falling onto platform
                new_y = p->y - user->radius;
                user->y_vel = 0;
                on_ground = 1;
            }
        }
    }

    // Jump logic (only when on ground)
    if (user->movement & M_SPACE && on_ground) {
        user->y_vel = JUMP_VELOCITY;
        printf("Jumping\n");
    }

    // Clamp to world bounds
    new_x = SDL_max(0, SDL_min(bound_x, new_x));
    new_y = SDL_max(0, SDL_min(bound_y, new_y));

    // Update user position
    user->x_pos = new_x;
    user->y_pos = new_y;

    // Reset velocity if hitting horizontal bounds
    if (user->x_pos == 0 || user->x_pos == bound_x) user->x_vel = 0;
}