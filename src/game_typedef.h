#ifndef GAME_TYPEDEF_H
#define GAME_TYPEDEF_H

typedef struct 
{
    float x, y;     // Position in world coordinates
    float vx, vy;   // Velocity components
    float width, height; // Size of object
} OBJECT;

typedef struct
{
    float x, y;     // Position
    float width, height; // Size
} PLATFORM;

typedef struct 
{   

    float x_pos; // x postition 
    float y_pos; // y position 
    unsigned char wasd; // bit manipulation for events 
}Player;

typedef struct
{
    float width ;
    float height ;
    float time_elapsed;
    float time_step; 
    Player player;
    OBJECT objects[100];
    PLATFORM platforms[10]; // Up to 10 platforms
    int platform_count; 
}WORLD;

typedef struct {
    float x, y;       // Camera position
    float width, height;  // Camera viewport size
    float lookahead;   // How much the camera looks ahead
    float deadzone_x;  // Dead zone width (prevents jittery movement)
    float deadzone_y;  // Dead zone height
    int locked;        // If the camera should stay fixed
} CAMERA;

#endif 