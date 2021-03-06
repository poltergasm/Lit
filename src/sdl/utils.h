
void l_init()
{
	// include initial font
	if (TTF_Init() == -1) {
		fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}
	
	lgfx.font = TTF_OpenFont("assets/font.ttf", 32);
	if (lgfx.font == NULL) {
		fprintf(stderr, "There was a problem opening the font: %s\n", TTF_GetError());
		exit(3);
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0) {
		if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
			fprintf(stderr, "Failed to initialise SDL_Image\n");
			exit(4);
		}

		int flags = 0;
		if (lit.fullscreen)
			flags = SDL_WINDOW_FULLSCREEN;

		printf("* Lit initialized\n");
		lit.window = SDL_CreateWindow(
			lwin.title,
			lwin.x,
			lwin.y,
			lwin.width,
			lwin.height,
			flags
		);

		if (lit.window != NULL) {
			lit.renderer = SDL_CreateRenderer(lit.window, -1, SDL_RENDERER_SOFTWARE);
			
			if (lit.renderer != NULL) {
				SDL_SetRenderDrawColor(lit.renderer, 0, 0, 0, 255);
				SDL_SetRenderDrawBlendMode(lit.renderer, SDL_BLENDMODE_BLEND);
			} else {
				perror("Failed to create renderer");
				exit(1);
			}
		} else {
			perror("Failed to create window");
			exit(1);
		}

		// if we made it this far then we're good to go
		lit.running = true;

		// set the initial color
		lgfx.current_color = col_black;
		SDL_SetRenderDrawColor(lit.renderer, col_black.r, col_black.g, col_black.b, col_black.a);
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void l_render()
{
    SDL_RenderClear(lit.renderer);
	lua_getglobal(lit.L, "_draw");
	if (lua_pcall(lit.L, 0, 1, 0) != 0) {
		fprintf(stderr, "Problem calling _draw: %s\n", lua_tostring(lit.L, -1));
		exit(1);
	}
    SDL_RenderPresent(lit.renderer);
}