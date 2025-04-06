#ifndef CONSTANTS_H
#define CONSTANTS_H

#define FIXED_TIME_STEP (1.0f / 160.0f)
#define WINDOW_WIDTH 1700
#define WINDOW_HEIGHT 1000
#define WORLD_WIDTH 10000
#define WORLD_HEIGHT 2000

#define GROUND_THICKNESS 10.0
#define GROUND_COLOR (SDL_Color){139, 69, 19, 255} // Brown for a earthy path
#define WHITE_COLOUR (SDL_Color){255,255,255,255}

static const float PIXELS_PER_METER = 1000.0f;
static const float METERS_PER_PIXEL = 1.0f / PIXELS_PER_METER;
static const float PIXELS_PER_CM = 10.0f;
static const float CM_PER_PIXEL = 1.0f / PIXELS_PER_CM;
static const float CM_PER_METER = 100.0f;
static const float METERS_PER_CM = 1.0f / CM_PER_METER;
static const float KILOMETER = 1000000.0f;



// Movement flags
#define GRAVITY 980.0
#define JUMP_VELOCITY -600.0
#define PLAYER_SPEED 600.0
#define PLAYER_SPRINT_SPEED 1000.0


#define M_W         (1U << 0) // W
#define M_A         (1U << 1) 
#define M_S         (1U << 3)
#define M_D         (1U << 2)
#define M_SPACE     (1U << 4)
#define M_LSHIFT    (1U << 5)
#define M_LCTRL     (1U << 6)

// Action flags (renamed to avoid conflict)
#define ACTION_A    (1U << 0) // Previously A
#define ACTION_R    (1U << 1) // Previously A_R
#define ACTION_F    (1U << 2) // F
#define ACTION_I    (1U << 3) // I for camera lock 


// UI flags
#define UI_ESC      (1U << 0)
#define UI_M        (1U << 1) // Map

#endif