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

int		sdl_set_status(t_doom *doom, int status)
{
	SDL_SetRelativeMouseMode(SDL_FALSE);
	doom->ui.curr_btn = NULL;
	if (status == 0)
	{
		doom->ui.m_status = 0;
		SDL_SetRelativeMouseMode(SDL_TRUE);
		change_music(&doom->sound, doom->sound.on, 5000);
		draw_menu(doom);
	}
	else if (status == 1)
	{
		doom->ui.m_status = 1;
		doom->ui.curr_btn_controller = -2;
		//doom_clear_map(doom); // TODO Add map data free;
		fire_on_off(doom->sdl.screen, doom->sdl.size, 1);
		change_music(&doom->sound, 0, 18000);
		draw_menu(doom);
	}
	else if (status == 2)
	{
		doom->ui.m_status = 2;
		doom->ui.curr_btn_controller = -3;
		load_map_btns(doom);
		draw_menu(doom);
	}
	else if (status == 3)
	{
		doom->ui.m_status = 3;
		doom->ui.curr_btn_controller = -1;
		draw_menu(doom);
	}
	return (status);
}

int		sdl_init(t_sdl *sdl, const char *title)
{
	void	*tmp;
	int		pitch;

	sdl->size.x = WIDTH;
	sdl->size.y = HEIGHT;
	if (!(sdl->win = SDL_CreateWindow(title, 0, 0, WIDTH, HEIGHT, 32)))
		return (0);
	if (!(sdl->rend = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_SOFTWARE)))
		return (0);
	SDL_SetWindowMinimumSize(sdl->win, MINWIDTH, MINHEIGHT);
	SDL_SetWindowMaximumSize(sdl->win, MAXWIDTH, MAXHEIGHT);
	sdl->txture = SDL_CreateTexture(sdl->rend,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	if (SDL_LockTexture(sdl->txture, NULL, &tmp, &pitch))
		return (0);
	sdl->screen = (Uint32*)tmp;
	if (!(sdl->format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888)))
		return (0);
	return (1);
}
