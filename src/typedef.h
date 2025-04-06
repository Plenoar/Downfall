#ifndef TYPEDEF_H
#define TYPEDEF_H

#include<stdint.h>
#include<SDL3/SDL.h>

typedef struct 
{   
    double radius;
    double height;

    double x_vel; // user x velocity
    double y_vel;  
    
    double last_stop_x;
    double last_stop_y;

    double x_pos; // user x postition 
    double y_pos; // y position 
    // unsigned char wasd; // bit manipulation for events , deprecated method, doesnt scale nicely      
    // for handling mouse events 
    float mouse_x , mouse_y;
    double wheel;


    // for handling keyboard events 
    uint32_t movement;
    uint32_t actions;
    uint32_t ui;

}USER;

typedef struct 
{
    double x_vel;
    double y_vel; 

    double x_pos;
    double y_pos;

}CLYPE;

typedef struct {
    double x, y;       // Camera position
    double width, height;  // Camera viewport size
    double lookahead;   // How much the camera looks ahead
    double deadzone_x;  // Dead zone width (prevents jittery movement)
    double deadzone_y;  // Dead zone height
    int locked;        // If the camera should stay fixed
} CAMERA;

typedef struct {
    double x, y;          // Top-left position
    double width, height; // Size
    SDL_Color color;      // Visual distinction
} Platform;

typedef struct
{
    double width ;
    double height ;
    double time_elapsed;
    double time_step; 
    Platform *platforms;
    int platform_count;
}WORLD;


typedef struct 
{
    double x,y;
    double radius;

}CIRCLE;



#endif 