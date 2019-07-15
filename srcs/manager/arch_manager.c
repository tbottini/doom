#include "doom_nukem.h"

void		borne_reset(t_arch *arch)
{
	int			i;

	i = 0;
	while (i < arch->sdl->size.x)
	{
		arch->bound.b_up[i] = 0;
		arch->bound.b_down[i] = arch->sdl->size.y;
		//printf("arch->borne %d\n", arch->bound.b_down[i]);
		//arch->bound.b_up[i] = arch->sdl->size.y / 4;
		//arch->bound.b_down[i] = arch->sdl->size.y / 2 + arch->sdl->size.y / 4;
		i++;
	}
	arch->bound.b_left = arch->cam->fov / 2.0;
	arch->bound.b_right = -arch->cam->fov / 2.0;

	//arch->bound.b_left = 15;
	//arch->bound.b_right = -15;
}

void				zline_reset(t_arch *arch)
{
	int				i;

	i = 0;
	while (i < arch->sdl->size.x)
	{
		arch->bound.zline[i] = 0;
		i++;
	}
}

void				architect_reset(t_arch *arch)
{
	borne_reset(arch);
	zline_reset(arch);
}

int arch_free(t_arch *arch)
{
	free(arch->bound.zline);
	return (1);
}

int			arch_init(t_arch *arch, t_sdl *sdl, t_camera *cam)
{
	size_t	curseur;

	arch->bound.zline = (double*)malloc(sizeof(double) * sdl->size.x);
	if (!arch->bound.zline)
		return (0);
	curseur = sdl->size.x * (sdl->size.y - 1);
	arch->sdl = sdl;
	arch->cam = cam;
	arch->bound.b_down = (uint32_t*)malloc(sizeof(uint32_t) * sdl->size.x);
	if (!arch->bound.b_down)
		return (0);
	arch->bound.b_up = (uint32_t*)malloc(sizeof(uint32_t) * sdl->size.x);
	if (!arch->bound.b_up)
		return (0);
	zline_reset(arch);
	return (1);
}
