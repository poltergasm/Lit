#ifndef _EVENTS_H_
#define _EVENTS_H_

void lit_handle_events(lit *lit)
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT:
            lit->running = false;
            break;

        default:
            break;
    }
}

#endif