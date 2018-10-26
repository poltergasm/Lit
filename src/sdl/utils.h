typedef struct _window {
	const char *title;
	int x;
	int y;
	int width;
	int height;
	bool fullscreen;
} l_window;

void l_init(lit *lit, l_window *window)
{
	printf("* Lit initialized\n");
}