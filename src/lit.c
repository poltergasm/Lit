#include "lit.h"
#include "sdl/events.h"
#include "sdl/utils.h"

uint8_t load_main(lit *lit)
{
	if (getcwd(lit->path, sizeof(lit->path)) == NULL)
		return 1;

	strcat(lit->path, "\\main.lua");
	uint8_t status = luaL_loadfile(lit->L, lit->path);
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

	uint8_t ret = lua_pcall(lit->L, 0, 0, 0);
	if (ret != 0) {
		perror(lua_tostring(lit->L, -1));
		return 1;
	}

	return 0;
}

uint8_t load_lua(lit *lit)
{
	lit->L = luaL_newstate();
	if (!lit->L) {
		fprintf(stderr, "There was a problem loading the Lua engine\n");
		return 1;
	}

	luaL_openlibs(lit->L);
	load_main(lit);

	return 0;
}

uint8_t l_cleanup(lit *lit)
{
	lua_pop(lit->L, 1);
    lua_close(lit->L);

    return 0;
}

void func_check(lit *lit)
{
	lit->can_update = false;
	lit->can_draw = false;
	lua_getglobal (lit->L, "_update");
    if (lua_isfunction (lit->L, -1) == 1) lit->can_update = true;
    lua_getglobal (lit->L, "_draw");
    if (lua_isfunction (lit->L, -1) == 1) lit->can_draw = true;
}

void l_update(lit *lit, double dt)
{
	lua_getglobal(lit->L, "_update");
	lua_pushnumber(lit->L, dt);
	if (lua_pcall(lit->L, 1, 1, 0) != 0) {
		fprintf(stderr, "Problem running _update: %s\n",
			lua_tostring(lit->L, -1));
		exit(1);
	}
}

int main(int argc, char *argv[])
{
	lit lit; 
	load_lua(&lit);

	l_window lwin;
	lwin.title = "Lit Demo";
	lwin.x = SDL_WINDOWPOS_CENTERED;
	lwin.y = SDL_WINDOWPOS_CENTERED;
	lwin.width = 800;
	lwin.height = 600;
	lwin.fullscreen = false;

	l_init(&lit, &lwin);
	func_check(&lit);

	clock_t _t;
	int t = 0;
	double delta;
	
	while (lit.running) {
		lit_handle_events(&lit);

		if (lit.can_update) {
            for (t = 0; t < 60; t++) {
                _t = clock();
                l_update(&lit, delta);
                _t = clock() - _t;
                delta = ((double)_t)/CLOCKS_PER_SEC;
            }
        }
	}

	printf("We done here\n");
	l_cleanup(&lit);
	return 0;
}

