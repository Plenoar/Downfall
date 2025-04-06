
#include <SDL3/SDL.h>
#include <math.h>
#include "typedef.h"
#include "constants.h"
#include <stdlib.h>
#include<stdlib.h>

void worldToScreen(const CAMERA *camera, double wx, double wy, double *sx, double *sy) {
    double scale_x = (double)WINDOW_WIDTH / camera->width;
    double scale_y = (double)WINDOW_HEIGHT / camera->height;
    double scale = scale_x; // Use isotropic scaling to preserve circle shapes
    *sx = (wx - camera->x) * scale;
    *sy = (wy - camera->y) * scale;
}

void DrawCircle(SDL_Renderer *renderer, CIRCLE circle, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    
    int x = (int)circle.radius;
    int y = 0;
    int err = 0;

    int center_x = (int)circle.x;
    int center_y = (int)circle.y;

    while (x >= y) {
        SDL_RenderPoint(renderer, center_x + x, center_y + y);
        SDL_RenderPoint(renderer, center_x + y, center_y + x);
        SDL_RenderPoint(renderer, center_x - y, center_y + x);
        SDL_RenderPoint(renderer, center_x - x, center_y + y);
        SDL_RenderPoint(renderer, center_x - x, center_y - y);
        SDL_RenderPoint(renderer, center_x - y, center_y - x);
        SDL_RenderPoint(renderer, center_x + y, center_y - x);
        SDL_RenderPoint(renderer, center_x + x, center_y - y);

        y += 1;
        if (err <= 0) {
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}


void RenderWorld(WORLD *world,USER *user, SDL_Renderer *renderer,CLYPE *clype, double θ, double θ1, double θ2, CAMERA *camera) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    double scale = (double)WINDOW_WIDTH / camera->width;
    // Render the ground line
    // double ground_y = WORLD_HEIGHT - GROUND_THICKNESS / 2.0;
    // double sx1, sy1, sx2, sy2;
    // worldToScreen(camera, 0, ground_y, &sx1, &sy1);          // Left edge
    // worldToScreen(camera, WORLD_WIDTH, ground_y, &sx2, &sy2); // Right edge
    // SDL_SetRenderDrawColor(renderer, GROUND_COLOR.r, GROUND_COLOR.g, GROUND_COLOR.b, GROUND_COLOR.a);
    // SDL_FRect ground_rect = {
    //     sx1, 
    //     sy1 - (GROUND_THICKNESS * scale / 2.0), 
    //     sx2 - sx1, 
    //     GROUND_THICKNESS * scale
    // };

    
    // Draw player
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    double px, py;
    worldToScreen(camera, user->x_pos, user->y_pos, &px, &py);
    SDL_FRect player_rect = {px - 25 * scale, py - 25 * scale, 50 * scale, 50 * scale};
    SDL_RenderFillRect(renderer, &player_rect);

    // Main circle
    CIRCLE circle_world = {3 * PIXELS_PER_METER, 1.5 * PIXELS_PER_METER, 1000};
    double sx, sy;
    worldToScreen(camera, circle_world.x, circle_world.y, &sx, &sy);
    CIRCLE circle_screen = {sx, sy, circle_world.radius * scale};
    DrawCircle(renderer, circle_screen, WHITE_COLOUR);

    // Circle 1
    double a_world = circle_world.x + (circle_world.radius * cos(θ));
    double b_world = circle_world.y + (circle_world.radius * sin(θ));
    double a_screen, b_screen;
    worldToScreen(camera, a_world, b_world, &a_screen, &b_screen);
    CIRCLE circle1_screen = {a_screen, b_screen, 200 * scale};
    DrawCircle(renderer, circle1_screen, WHITE_COLOUR);
    SDL_RenderLine(renderer, (int)sx, (int)sy, (int)a_screen, (int)b_screen);

    // Circle 2
    double c_world = a_world + (200 * cos(θ1));
    double d_world = b_world + (200 * sin(θ1));
    double c_screen, d_screen;
    worldToScreen(camera, c_world, d_world, &c_screen, &d_screen);
    CIRCLE circle2_screen = {c_screen, d_screen, 100 * scale};
    DrawCircle(renderer, circle2_screen, WHITE_COLOUR);
    SDL_RenderLine(renderer, (int)a_screen, (int)b_screen, (int)c_screen, (int)d_screen);

    // Circle 3
    double e_world = c_world + (100 * cos(θ2));
    double f_world = d_world + (100 * sin(θ2));
    double e_screen, f_screen;
    worldToScreen(camera, e_world, f_world, &e_screen, &f_screen);
    CIRCLE circle3_screen = {e_screen, f_screen, 50 * scale};
    DrawCircle(renderer, circle3_screen, WHITE_COLOUR);
    SDL_RenderLine(renderer, (int)c_screen, (int)d_screen, (int)e_screen, (int)f_screen);

    for (int i = 0; i < world->platform_count; i++) {
        Platform *p = &world->platforms[i];
        double sx, sy;
        worldToScreen(camera, p->x, p->y, &sx, &sy);
        SDL_FRect platform_rect = {sx, sy, p->width * scale, p->height * scale};
        SDL_SetRenderDrawColor(renderer, p->color.r, p->color.g, p->color.b, p->color.a);
        SDL_RenderFillRect(renderer, &platform_rect);
    }
    SDL_RenderPresent(renderer);
}


void DestroyWorld(WORLD *world) {

    free(world->platforms);
    SDL_Quit();

}


