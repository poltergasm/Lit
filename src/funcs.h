const char *lua_win = "COL_BLACK=0;COL_DARK_RED=1;COL_DARK_BLUE=2 \
COL_DARK_GRAY=3;COL_BROWN=4;COL_DARK_GREEN=5;COL_RED=6;COL_LIGHT_GRAY=7 \
COL_LIGHT_BLUE=8;COL_ORANGE=9;COL_BLUE_GRAY=10;COL_LIGHT_GREEN=11;COL_PEACH=12 \
COL_CYAN=13;COL_YELLOW=14;COL_WHITE=15 \
_G.lit = { \
	win = { \
		_ptr  = nil, \
		set_title = _l_set_title \
	}, \
	gfx = { \
		set_bg = _l_set_background, \
		set_color = _l_set_color, \
		print = _l_print \
	}, \
	timer = { \
		get_time = _l_get_time \
	} \
}";

color_t get_color(int n)
{
	switch(n) {
		case 0: return col_black;
		case 1: return col_dark_red;
		case 2: return col_dark_blue;
		case 3: return col_dark_gray;
		case 4: return col_brown;
		case 5: return col_dark_green;
		case 6: return col_red;
		case 7: return col_light_gray;
		case 8: return col_light_blue;
		case 9: return col_orange;
		case 10: return col_blue_gray;
		case 11: return col_light_green;
		case 12: return col_peach;
		case 13: return col_cyan;
		case 14: return col_yellow;
		case 15: return col_white;
		default: return col_black;
	}
}

SDL_Color mkcolor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_Color c = {r, g, b, a};

    return c;
}

static int l_set_color(lua_State *L)
{
	uint8_t c = lua_tonumber(L, 1);
	color_t col = get_color(c);
	SDL_SetRenderDrawColor(lit.renderer, col.r, col.g, col.b, col.a);
	return 0;
}

static int l_set_background(lua_State *L)
{
	int n = lua_tonumber(L, 1);
	color_t c = get_color(n);
	color_t old_color = lgfx.current_color;
	printf("Setting background to %d, %d, %d\n", c.r, c.g, c.b);
	SDL_SetRenderDrawColor(lit.renderer, c.r, c.g, c.b, c.a);
	SDL_RenderClear(lit.renderer);
	return 1;
}

static int l_set_title(lua_State *L)
{
	const char *s = lua_tostring(L, 1);
	lwin.title = s;
	SDL_SetWindowTitle(lit.window, s);
	lua_pushstring(L, s);
	return 1;
}

static int l_print(lua_State *L)
{
	const char *text = lua_tostring(L, 1);
	int x = lua_tonumber(L, 2);
	int y = lua_tonumber(L, 3);
	int cn = lua_tonumber(L, 4);
	color_t c = get_color(cn);
	SDL_Color col = mkcolor(c.r, c.g, c.b, c.a);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(
		lgfx.font,
		text,
		col
	);
	SDL_Texture* message = SDL_CreateTextureFromSurface(
		lit.renderer,
		surfaceMessage
	);
	
	int tw,th;
	TTF_SizeText(lgfx.font, text, &tw, &th);

	SDL_Rect message_rect;
	message_rect.x = x;
	message_rect.y = y;
	message_rect.w = tw;
	message_rect.h = th;
	SDL_RenderCopy(lit.renderer, message, NULL, &message_rect);
	SDL_DestroyTexture(message);
	SDL_FreeSurface(surfaceMessage);
	return 0;
}

static int l_get_time(lua_State *L)
{
	lua_pushnumber(L, (int)time(NULL));
	return 1;
}