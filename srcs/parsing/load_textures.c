#include "doom_nukem.h"


//static t_wall	load_texture(t_doom *doom, const char *file)
//{
//	SDL_RWops	*rwop;
//	SDL_Surface	*surf;
//	SDL_Surface	*tmp;
//	t_wall		wall;
//
//	rwop = SDL_RWFromFile(file, "rb");
//	if (!(tmp = IMG_LoadXPM_RW(rwop)))
//	{
//		ft_printf("IMG_LoadXPM_RW: %s\n", IMG_GetError());
//		prog_quit(doom);
//	}
//	if (!(surf = SDL_ConvertSurface(tmp, doom->sdl.format, 0)))
//	{
//		ft_printf("SDL_ConvertSurface: failed\n");
//		prog_quit(doom);
//	}
//	SDL_FreeSurface(tmp);
//	SDL_RWclose(rwop);
//	wall.txture = surf->pixels;
//	wall.surf = surf;
//	wall.w = surf->w;
//	wall.h = surf->h;
//	return (wall);
//}
