#include "doom_nukem.h"

void	sdl_free(t_sdl *sdl)
{
	if (sdl->txture)
		SDL_DestroyTexture(sdl->txture);
	if (sdl->rend)
		SDL_DestroyRenderer(sdl->rend);
	if (sdl->win)
		SDL_DestroyWindow(sdl->win);
	if (sdl->format)
		SDL_FreeFormat(sdl->format);
}

int		sdl_init(t_sdl *sdl, const char *title)
{
	void	*tmp;
	int		pitch;

	sdl->size.x = WIDTH;
	sdl->size.y = HEIGHT;
	if (!(sdl->win = SDL_CreateWindow(title, 0, 0, WIDTH, HEIGHT, 32)))
		return (0);
	if (!(sdl->rend = SDL_CreateRenderer(sdl->win, -1, 1)))
		return (0);
	SDL_SetWindowMinimumSize(sdl->win, MINWIDTH, MINHEIGHT);
	sdl->txture = SDL_CreateTexture(sdl->rend,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	if (SDL_LockTexture(sdl->txture, NULL, &tmp, &pitch))
		return (0);
	sdl->screen = (uint32_t*)tmp;
	if (!(sdl->format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888)))
		return (0);
	return (1);
}
