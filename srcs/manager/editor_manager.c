#include "doom_nukem.h"

void	editor_free(t_editor *editor)
{
	if (editor->txture)
		SDL_DestroyTexture(editor->txture);
	if (editor->rend)
		SDL_DestroyRenderer(editor->rend);
	if (editor->win)
		SDL_DestroyWindow(editor->win);
}

int		editor_init(t_editor *editor)
{
	void	*tmp;
	int		pitch;

	if (!(editor->win = SDL_CreateWindow("Editor", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_HIDDEN)))
		return (0);
	if (!(editor->rend = SDL_CreateRenderer(editor->win, -1, 1)))
		return (0);
	editor->txture = SDL_CreateTexture(editor->rend,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	if (SDL_LockTexture(editor->txture, NULL, &tmp, &pitch))
		return (0);
	editor->screen = (uint32_t*)tmp;
	SDL_GetWindowSize(editor->win, &(editor->size.x), &(editor->size.y));
	return (1);
}
