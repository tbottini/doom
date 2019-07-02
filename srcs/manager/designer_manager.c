#include "doom_nukem.h"

int			designer_init(t_arch *designer, t_sdl *sdl, t_camera *cam)
{
	size_t	curseur;

	designer->zline = (double*)malloc(sizeof(double) * 2550);
	if (!designer->zline)
		return (0);
	curseur = sdl->size.x * (sdl->size.y - 1);
	designer->sdl = sdl;
	designer->cam = cam;
	//designer->borne.x = cam->fov / 2.0;
	//designer->borne.y = -cam->fov / 2.0;
	designer->borne.x = 45;
	designer->borne.y = -45;
	zline_reset(designer);
	return (1);
}
