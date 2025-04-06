#include <SDL3/SDL.h>
#include "typedef.h"
#include "constants.h"

void ProcessInput(SDL_Event event,USER *user, CAMERA *camera , int *running) {

    SDL_MouseButtonEvent mouse;
    
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

                user->mouse_x = x;
                user->mouse_y = y;

                break;
            }
            case SDL_EVENT_MOUSE_BUTTON_DOWN: 
            {
                // idk do something 
                if(mouse.button == SDL_BUTTON_LEFT )
                // do something 

                if(mouse.button == SDL_BUTTON_RIGHT )
                // no like do something for real 
                break;
            }

            case SDL_EVENT_KEY_DOWN: \
            {
                SDL_Keycode sym = event.key.key;

                // handling movements 
                if (sym == SDLK_W) user->movement |= M_W;
                if (sym == SDLK_A)user->movement|= M_A;
                if (sym == SDLK_S)user->movement |= M_S;
                if (sym == SDLK_D)user->movement|= M_D;
                if (sym == SDLK_SPACE)user->movement |= M_SPACE;
                if (sym == SDLK_LSHIFT)user->movement |= M_LSHIFT; 
                if (sym == SDLK_LCTRL)user->movement |= M_LCTRL; 
                
                // handling actions
                if (sym == SDLK_F)user->actions |= ACTION_F; 
                if (sym == SDLK_I)user->actions |= ACTION_I; 


                // handling ui
                if (sym == SDLK_M)user->ui |= UI_M;
                // well some uis cant just quit when the user lifts up their fingers so i need a workaround
                if (sym == SDLK_ESCAPE)user->ui |= UI_ESC;

                break;
            }
            case SDL_EVENT_KEY_UP:
            {
                SDL_Keycode sym = event.key.key; 
                if (sym == SDLK_W)user->movement &= ~M_W;
                if (sym == SDLK_A)user->movement &= ~M_A;
                if (sym == SDLK_S)user->movement &= ~M_S;
                if (sym == SDLK_D)user->movement &= ~M_D;
                if (sym == SDLK_SPACE)user->movement &= ~M_SPACE; // this is to clear the bit 
                if (sym == SDLK_LSHIFT)user->movement &= ~M_LSHIFT;  
                if (sym == SDLK_LCTRL)user->movement &= ~M_LCTRL; 
                 
                // handling actions
                if (sym == SDLK_F)user->actions &= ~ACTION_F;  
                if (sym == SDLK_I)user->actions &= ~ACTION_I; 
                
                //  handling uis 
                if (sym == SDLK_M)user->ui &= ~UI_M;
                
                break;
           }

           case SDL_EVENT_MOUSE_WHEEL: {
               if(user->actions & ACTION_I)
               {
                double zoom_factor = (event.wheel.y > 0) ? 0.9 : (event.wheel.y < 0) ? 1.1 : 1.0;
                if (zoom_factor == 1.0) break;
    
                double center_x = camera->x + camera->width / 2.0;
                double center_y = camera->y + camera->height / 2.0;
    
                double new_width = camera->width * zoom_factor;
                double new_height = camera->height * zoom_factor;
    
                const double min_width = 100.0;
                const double max_width = 10000.0;
                if (new_width < min_width) {
                    new_width = min_width;
                    new_height = min_width * ((double)WINDOW_HEIGHT / WINDOW_WIDTH);
                } else if (new_width > max_width) {
                    new_width = max_width;
                    new_height = max_width * ((double)WINDOW_HEIGHT / WINDOW_WIDTH);
                }
    
                camera->width = new_width;
                camera->height = new_height;
                camera->x = center_x - camera->width / 2.0;
                camera->y = center_y - camera->height / 2.0;
                break;

            }

        }
    }
}
}
