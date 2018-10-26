#ifndef _LIT_H_
#define _LIT_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <unistd.h>
#include <time.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_Image.h"
#include "luajit.h"
#include <stdbool.h>
#include "utils.h"

typedef struct _lit {
	lua_State *L;
	char path[256];
	bool running;
	bool can_update;
	bool can_draw;
} lit;

uint8_t load_lua(lit *lit);
uint8_t load_main(lit *lit);
uint8_t end_lua(lit *lit);
void func_check(lit *lit);
void l_update(lit *lit, double dt);

void print(const char *fmt, ...);

#endif