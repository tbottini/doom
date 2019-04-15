#include "wolf3d.h"

void			*sdldata_quit(t_sdldata **data)
{
	t_sdldata *sdl;

	sdl = *data;
	if (sdl->texture)
		SDL_DestroyTexture(sdl->texture);
	if (sdl->renderer)
		SDL_DestroyRenderer(sdl->renderer);
	if (sdl->window)
		SDL_DestroyWindow(sdl->window);
	if (*data)
		free(*data);
	return (NULL);
}

t_sdldata		*sdldata_init(t_sdldata *sdl, uint32_t x, uint32_t y)
{
	sdl->size.x = (int)x;
	sdl->size.y = (int)y;
	sdl->open = 1;
	return (sdl);
}

t_sdldata		*sdldata_start(char *title, uint32_t x, uint32_t y)
{
	t_sdldata	*sdl;
	void		*tmp;
	int			pitch;

	sdl = (t_sdldata *)malloc(sizeof(t_sdldata));
	if (!sdl)
		return (NULL);
	sdl->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_SHOWN);
	if (!sdl->window)
		return (sdldata_quit(&sdl));
	sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
		SDL_RENDERER_SOFTWARE);
	if (!sdl->renderer)
		return (sdldata_quit(&sdl));
	sdl->texture = SDL_CreateTexture(sdl->renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, x, y);
	if (!sdl->texture)
		return (sdldata_quit(&sdl));
	SDL_LockTexture(sdl->texture, NULL, &tmp, &pitch);
	if (!tmp)
		return (sdldata_quit(&sdl));
	sdl->screen = (uint32_t*)tmp;
	sdldata_init(sdl, x, y);
	return (sdl);
}

void		sdl_showscreen(t_sdldata *sdl)
{
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
}