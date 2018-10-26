const char *lua_win = "COL_BLACK=0 \
_G.lit = { \
	win = { \
		_ptr  = nil, \
		set_title = _l_set_title \
	}, \
	gfx = { \
		set_bg = _l_set_background \
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
	color_t old_color = lit.current_color;
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

