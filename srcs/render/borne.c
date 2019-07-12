#include "doom_nukem.h"

int			trunc_int(int value, int min, int max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	return (value);
}

void		set_borne_vertical(t_arch *arch, t_vct2 surface, int i)
{
	arch->borne_up[i] = trunc_int(surface.x, 0, arch->px.y - 1);
	arch->borne_down[i] = trunc_int(surface.y, 0, arch->px.y - 1);
}

void		set_borne_horizontal(t_arch *arch)
{
	arch->borne.x = atan2((arch->sdl->size.x / 2) - arch->px.x, arch->cam->d_screen);
	arch->borne.y = atan2((arch->sdl->size.x / 2) - arch->px.y, arch->cam->d_screen);
}

