#ifndef _EVENTS_H_
#define _EVENTS_H_

void lit_handle_events()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        lit.running = false;
    } else if (event.type == SDL_KEYDOWN) {
    	switch(event.key.keysym.sym) {
    		case SDLK_RIGHT:
    			isPressing[0] = 1;
    			break;
    		case SDLK_LEFT:
    			isPressing[1] = 1;
    			break;
    		case SDLK_UP:
    			isPressing[2] = 1;
    			break;
    		case SDLK_DOWN:
    			isPressing[3] = 1;
    			break;
    		case SDLK_x:
    			isPressing[4] = 1;
    			break;
    		case SDLK_z:
    			isPressing[5] = 1;
    			break;
    	}
    }

    if (event.type == SDL_KEYUP) {
    	switch(event.key.keysym.sym) {
    		case SDLK_RIGHT:
    			key_pressed = 0;
    			isPressing[0] = 0;
    			break;
    		case SDLK_LEFT:
    			key_pressed = 1;
    			isPressing[1] = 0;
    			break;
    		case SDLK_UP:
    			key_pressed = 2;
    			isPressing[2] = 0;
    			break;
    		case SDLK_DOWN:
    			key_pressed = 3;
    			isPressing[3] = 0;
    			break;
    		case SDLK_x:
    			key_pressed = 4;
    			isPressing[4] = 0;
    			break;
    		case SDLK_z:
    			key_pressed = 5;
    			isPressing[5] = 0;
    			break;
    	}
    }
}

#endif