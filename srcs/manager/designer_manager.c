#include "doom_nukem.h"

void		borne_reset(t_arch *arch)
{
	int			i;
	uint64_t	*borne_up;
	uint64_t	*borne_down;
	int			max;

	max = arch->sdl->size.x / 4;
	borne_up = (uint64_t*)arch->borne_up;
	borne_down = (uint64_t*)arch->borne_down;
	i = 0;
	while (i < max)
	{
		borne_up[i] = 0;
		borne_down[i] = arch->sdl->size.y - 1;
		i++;
	}
	i *= 4;
	while (i < arch->sdl->size.x)
	{
		borne_up[i] = 0;
		i++;
	}
	arch->borne.x = arch->cam->fov / 2.0;
	arch->borne.y = -arch->cam->fov / 2.0;
}

void				zline_reset(t_arch *arch)
{
	int				i;

	i = 0;
	while (i < arch->sdl->size.x)
	{
		arch->zline[i] = 0;
		i++;
	}
}

void				architect_reset(t_arch *arch)
{
	borne_reset(arch);
	zline_reset(arch);
}

int			designer_init(t_arch *designer, t_sdl *sdl, t_camera *cam)
{
	size_t	curseur;

	designer->zline = (double*)malloc(sizeof(double) * 2550);
	if (!designer->zline)
		return (0);
	curseur = sdl->size.x * (sdl->size.y - 1);
	designer->sdl = sdl;
	designer->cam = cam;
	designer->borne_down = (uint16_t*)malloc(sizeof(uint16_t) * sdl->size.x);
	if (!designer->borne_down)
		return (0);
	designer->borne_up = (uint16_t*)malloc(sizeof(uint16_t) * sdl->size.x);
	if (!designer->borne_up)
		return (0);
	zline_reset(designer);
	return (1);
}
