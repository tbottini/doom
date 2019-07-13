#include "doom_nukem.h"

void		borne_reset(t_arch *arch)
{
	int			i;

	i = 0;
	while (i < arch->sdl->size.x)
	{
		arch->borne_up[i] = 0;
		arch->borne_down[i] = arch->sdl->size.y;
		//printf("arch->borne %d\n", arch->borne_down[i]);
		//arch->borne_up[i] = arch->sdl->size.y / 4;
		//arch->borne_down[i] = arch->sdl->size.y / 2 + arch->sdl->size.y / 4;
		i++;
	}
	arch->borne.x = arch->cam->fov / 2.0;
	arch->borne.y = -arch->cam->fov / 2.0;

	//arch->borne.x = 15;
	//arch->borne.y = -15;
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

int designer_free(t_arch *designer)
{
	free(designer->zline);
	return (1);
}

int			designer_init(t_arch *designer, t_sdl *sdl, t_camera *cam)
{
	size_t	curseur;

	designer->zline = (double*)malloc(sizeof(double) * sdl->size.x);
	if (!designer->zline)
		return (0);
	curseur = sdl->size.x * (sdl->size.y - 1);
	designer->sdl = sdl;
	designer->cam = cam;
	designer->borne_down = (uint32_t*)malloc(sizeof(uint32_t) * sdl->size.x);
	if (!designer->borne_down)
		return (0);
	designer->borne_up = (uint32_t*)malloc(sizeof(uint32_t) * sdl->size.x);
	if (!designer->borne_up)
		return (0);
	zline_reset(designer);
	return (1);
}
