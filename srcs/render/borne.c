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
	arch->bound.b_up[i] = (uint32_t)trunc_int(surface.x, 0, arch->bound.b_up[arch->px.x] - 1);
	arch->bound.b_down[i] = (uint32_t)trunc_int(surface.y, 0, arch->bound.b_down[arch->px.x] - 1);
}

void		set_borne_horizontal(t_arch *arch)
{
	arch->bound.b_left = atan2((arch->sdl->size.x / 2) - arch->px.x, arch->cam->d_screen);
	arch->bound.b_right = atan2((arch->sdl->size.x / 2) - arch->px.y, arch->cam->d_screen);
	arch->bound.b_left *= TOANGLE;
	arch->bound.b_right *= TOANGLE;
}

/*
**	sauvegarde toute les configuration de borne dans une structure
**	dans une zone (la zone est les limite de px)
*/
t_borne		*borne_svg(t_arch *arch, t_borne *borne)
{
	int		len;

	len = arch->px.y - arch->px.x;
	borne->b_left = arch->bound.b_left;
	borne->b_right = arch->bound.b_right;
	borne->decal_portal = arch->bound.decal_portal;
	borne->decal_portal = arch->bound.depth_portal;
	borne_init(borne, len);
	return (borne);
}

/*
**	recharge une borne dans la borne arch
*	(une borne anciennement sauvegarde...)
*/
void		borne_load(t_arch *arch, t_borne *borne, int start)
{
	int		i;

	i = 0;
	arch->bound.b_left = borne->b_left;
	arch->bound.b_right = borne->b_right;
	while (start < arch->px.y)
	{
		arch->bound.b_up[start] = borne->b_up[i];
		arch->bound.b_down[start] = borne->b_down[i];
		arch->bound.zline[start] = borne->zline[i];
		start++;
		i++;
	}
	arch->bound.decal_portal = borne->decal_portal;
	arch->bound.depth_portal = borne->depth_portal;
	borne_free(borne);
}