typedef struct _window {
	const char *title;
	int x;
	int y;
	int width;
	int height;
	uint8_t fullscreen;
} l_window;

void l_init(lit *lit, l_window *window)
{
	printf("* Lit initialized\n");
}