#include "doom_nukem.h"

int			designer_init(t_designer *designer, t_sdl *sdl, t_camera *cam)
{
	size_t	x;
	size_t	curseur;

	designer->zline = (double*)malloc(sizeof(double) * 2550);
	if (!designer->zline)
		return (0);
	curseur = sdl->size.x * (sdl->size.y - 1);
	x = 0;
	while (x < WIDTH)
	{
		designer->top[x] = &sdl->screen[x];
		designer->bot[x] = &sdl->screen[curseur + x];
		x++;
	}
	designer->sdl = sdl;
	designer->cam = cam;
	zline_reset(designer);
	return (1);
}