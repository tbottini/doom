#include "doom_nukem.h"
#include "debug.h"

t_arch *arch_debug_extern;

void		borne_reset(t_arch *arch)
{
	int			i;

	i = 0;
	while (i < arch->sdl->size.x)
	{
		arch->portal.b_up[i] = 0;
		arch->portal.b_down[i] = arch->sdl->size.y;
		i++;
	}
	arch->portal.b_left = arch->cam->fov / 2.0;
	arch->portal.b_right = -arch->cam->fov / 2.0;
}

void				zline_reset(t_arch *arch)
{
	int				i;

	i = 0;
	while (i < arch->sdl->size.x)
	{
		arch->portal.zline[i] = 0;
		i++;
	}
}

void				architect_reset(t_arch *arch)
{
	borne_reset(arch);
	zline_reset(arch);
}

void 				arch_free(t_arch *arch)
{
	borne_free(&arch->portal);
}

int			arch_init(t_arch *arch, t_sdl *sdl, t_camera *cam)
{
	size_t	curseur;


	if (!borne_init(&arch->portal, sdl->size.x))
		return (0);
	curseur = sdl->size.x * (sdl->size.y - 1);
	arch->sdl = sdl;
	arch->cam = cam;

	arch->wall = NULL;
	arch->depth_portal = 0;
	arch->zoom = 10;
	zline_reset(arch);
	arch_debug_extern = arch;
	return (1);
}
