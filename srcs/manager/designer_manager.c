#include "doom_nukem.h"

int			designer_init(t_designer *designer, t_sdl sdl)
{
	size_t	x;
	size_t	curseur;

	curseur = sdl.size.x * (sdl.size.y - 1);
	x = 0;
	while (x < WIDTH)
	{
		designer->top[x] = &sdl.screen[x];
		designer->bot[x] = &sdl.screen[curseur + x];
		x++;
	}
	return (1);
}