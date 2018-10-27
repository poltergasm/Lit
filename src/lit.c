#include "lit.h"
#include "funcs.h"
#include "sdl/events.h"
#include "sdl/utils.h"

uint8_t load_main()
{
	if (getcwd(lit.path, sizeof(lit.path)) == NULL)
		return 1;

	strcat(lit.path, "\\main.lua");
	// setup window
	lwin.title = "Lit";
	lwin.x = SDL_WINDOWPOS_CENTERED;
	lwin.y = SDL_WINDOWPOS_CENTERED;
	lwin.width = 800;
	lwin.height = 600;
	lwin.fullscreen = false;

	lua_pushcfunction(lit.L, l_set_title);
	lua_setglobal(lit.L, "_l_set_title");

	lua_pushcfunction(lit.L, l_set_color);
	lua_setglobal(lit.L, "_l_set_color");

	lua_pushcfunction(lit.L, l_set_background);
	lua_setglobal(lit.L, "_l_set_background");

	lua_pushcfunction(lit.L, l_print);
	lua_setglobal(lit.L, "_l_print");

	lua_pushcfunction(lit.L, l_get_time);
	lua_setglobal(lit.L, "_l_get_time");

	uint8_t status = luaL_loadfile(lit.L, lit.path);
	if (status != 0) {
		switch(status) {
			case 7:
				perror("Could not open main.lua!");
				break;
			default:
				perror("Unknown error");
				break;
		}

		return 1;
	}

	uint8_t ret = lua_pcall(lit.L, 0, 0, 0);
	if (ret != 0) {
		perror(lua_tostring(lit.L, -1));
		return 1;
	}

	return 0;
}

uint8_t load_lua()
{
	lit.L = luaL_newstate();
	if (!lit.L) {
		fprintf(stderr, "There was a problem loading the Lua engine\n");
		return 1;
	}

	luaL_openlibs(lit.L);
	load_main();

	return 0;
}

uint8_t l_cleanup()
{
	lua_close(lit.L);
    SDL_DestroyWindow(lit.window);
    SDL_DestroyRenderer(lit.renderer);
    //textures_destroy(engine);
    TTF_Quit();
    SDL_Quit();
    printf("Shutting down. All cleaned up.\n");
    return 0;
}

void func_check()
{
	lit.can_update = false;
	lit.can_draw = false;
	lua_getglobal (lit.L, "_update");
    if (lua_isfunction (lit.L, -1) == 1) lit.can_update = true;
    lua_getglobal (lit.L, "_draw");
    if (lua_isfunction (lit.L, -1) == 1) lit.can_draw = true;
    lua_getglobal (lit.L, "_init");
    if (lua_isfunction (lit.L, -1) == 1) lit.can_init = true;
}

void l_update(double dt)
{
	lua_getglobal(lit.L, "_update");
	lua_pushnumber(lit.L, dt);
	if (lua_pcall(lit.L, 1, 1, 0) != 0) {
		fprintf(stderr, "Problem running _update: %s\n",
			lua_tostring(lit.L, -1));
		exit(1);
	}
}

void leval(const char *expr)
{
	 lua_pushfstring(lit.L, "%s", expr);
	 luaL_loadstring(lit.L, lua_tostring(lit.L,-1));
	 lua_remove(lit.L,-2);
	 lua_pcall(lit.L,0,1,0);
}

int main(int argc, char *argv[])
{
	load_lua();

	func_check();
	leval(lua_win);

	/*lua_getglobal(lit.L, "lit.win._ptr");
	lua_pushlightuserdata(lit.L, &lwin);
	lua_pcall(lit.L, 1, 0, 0);*/

	lua_pop(lit.L, 1);
    

	l_init();

	// frame shit
	const int FPS = 60;
	const int frame_delay = 1000 / FPS;
	uint32_t frame_start;
	int frame_time;

	double delta;

	while (lit.running) {
		frame_start = SDL_GetTicks();

		lit_handle_events();
		if (lit.can_update) l_update(delta)
        if (lit.can_draw) l_render();

        frame_time = SDL_GetTicks() - frame_start;
    	if (frame_delay > frame_time) {
    		SDL_Delay(frame_delay - frame_time);
    	}
	}

	l_cleanup();
	return 0;
}

