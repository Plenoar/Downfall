#include<stdio.h>
#include<SDL3/SDL.h>
#include<math.h>
#define COLOR_SUN 0x1fffff23

typedef struct 
{   
    double position[2];
    double velocity[2];
    double dimension;
    unsigned char wasd;
    
}Player;

typedef struct 
{
    int objects[1000]; 
    double length;
    double height;

}World;

typedef struct 
{
    double x , y ;
    float coordinate;

}Object;


typedef struct {
    float x;
    float y;
    float radius;
} Circle;    


void createCircle(SDL_Surface *surface, Circle c, Uint32 color) {
    float radius_squared = pow(c.radius ,2);
    for (float x = c.x-c.radius; x<= c.x+c.radius; x++)
        {

            for(float y = c.y-c.radius; y<= c.y+c.radius; y++)
            {
                float distance_squared = pow(x-c.x,2) + pow(y-c.y,2);
                if (distance_squared < radius_squared)
                {
                    SDL_Rect pixel = (SDL_Rect){x,y,1,1};
                    SDL_FillSurfaceRect(surface,&pixel,color);
                } 
            }
        }
    }
void createPlatform(SDL_Surface *surface) {

    for (int i = 0; i < 18; i++) {
        SDL_Rect rect = {i * 100.0f + 1, 900.0f, 70.0f, 35.0f};
        SDL_FillSurfaceRect(surface, &rect, COLOR_SUN);
    }
}
int main(void)
{

    SDL_Init(SDL_INIT_VIDEO);
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }


    SDL_Window* window =  SDL_CreateWindow("the grace of death", 1700,1000 , 0  );
        if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = SDL_GetWindowSurface(window);
        if (surface == NULL) {
        fprintf(stderr, "SDL_GetWindowSurface Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    Circle c = {10,10,100}; 


    int running = 1;
    SDL_Event event;

    while (running)
    {   
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = 0;
            }
            if (event.type == SDL_EVENT_MOUSE_MOTION)
            {
                float x , y;
                SDL_GetMouseState(&x, &y);
                c.x = x;
                c.y = y;   

                createCircle(surface, c, COLOR_SUN);  // the objects which are to be used in the game      
                createPlatform(surface);
                
                SDL_UpdateWindowSurface(window);
                SDL_ClearSurface(surface,0,0,0,0);                
                
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}


