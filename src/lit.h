#ifndef _LIT_H_
#define _LIT_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <unistd.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "luajit.h"
#include "utils.h"

//colors
typedef struct _color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} color_t;

color_t col_black = {20, 12, 28, 255};
color_t col_dark_red = {68, 36, 52, 255};
color_t col_dark_blue = {48, 52, 109, 255};
color_t col_dark_gray = {78, 74, 78, 255};
color_t col_brown = {133, 76, 48, 255};
color_t col_dark_green = {52, 101, 36, 255};
color_t col_red = {208, 70, 72, 255};
color_t col_light_gray = {117, 113, 97, 255};
color_t col_light_blue = {89, 125, 206, 255};
color_t col_orange = {210, 125, 44, 255};
color_t col_blue_gray = {133, 149, 161, 255};
color_t col_light_green = {109, 170, 44, 255};
color_t col_peach = {210, 170, 153, 255};
color_t col_cyan = {109, 194, 202, 255};
color_t col_yellow = {218, 212, 94, 255};
color_t col_white = {222, 238, 214, 255};

typedef struct _lit {
	lua_State *L;
	char path[256];
	bool running;
	bool can_update;
	bool can_draw;
	bool can_init;
	bool fullscreen;
	SDL_Renderer *renderer;
	SDL_Window *window;
} Lit;

typedef struct _graphics {
	color_t current_color;
	TTF_Font* font;
	SDL_Color color;
} l_graphics;

typedef struct _window {
	const char *title;
	int x;
	int y;
	int width;
	int height;
	bool fullscreen;
} l_window;

typedef struct _texture {
	SDL_Texture *texture;
    bool flipped;
    const char *path;
} texture_t;

typedef struct _quad {
	SDL_Rect rect;
} l_quad_t;

enum SND_TYPE { Chunk = 1, Music = 2 };

typedef struct _sound {
	enum SND_TYPE type;
	int idx;
} l_sound_t;

int NUM_MUSIC = 1;
int NUM_CHUNK = 1;
int NUM_SND   = 1;
l_sound_t sounds[100];
Mix_Music *l_music[50] = {NULL};
Mix_Chunk *l_chunk[50] = {NULL};

int NUM_TEXTURES = 1;
int NUM_QUADS = 1;
texture_t l_textures[256] = {NULL};
l_quad_t l_quads[256];

Lit lit;
static l_window lwin;
static l_graphics lgfx;

int key_pressed = -1;
int isPressing[6] = { 0 };

uint8_t load_lua();
uint8_t load_main();
uint8_t end_lua();
void l_update(int dt);
static int l_set_title(lua_State *L);
void print(const char *fmt, ...);

#endif