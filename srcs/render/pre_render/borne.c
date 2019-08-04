#include "render.h"

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
	arch->portal.b_up[i] = (uint32_t)trunc_int(surface.x, arch->portal.b_up[arch->px.x], arch->portal.b_down[arch->px.x] - 1);
	arch->portal.b_down[i] = (uint32_t)trunc_int(surface.y, arch->portal.b_up[arch->px.x], arch->portal.b_down[arch->px.x] - 1);
}

void		set_borne_horizontal(t_arch *arch)
{
	arch->portal.b_left = atan2((arch->sdl->size.x / 2) - arch->px.x, arch->cam->d_screen);
	arch->portal.b_right = atan2((arch->sdl->size.x / 2) - arch->px.y, arch->cam->d_screen);
	arch->portal.b_left *= TOANGLE;
	arch->portal.b_right *= TOANGLE;
}

/*
**	sauvegarde toute les configuration de borne dans une structure
**	dans une zone (la zone est les limite de px)
*/
t_borne		*borne_svg(t_arch *arch, t_borne *borne)
{
	int		len;

	len = arch->px.y - arch->px.x;
	borne->b_left = arch->portal.b_left;
	borne->b_right = arch->portal.b_right;


	//----borne->decal_portal = arch->portal.decal_portal;
	//----borne->depth_portal = arch->portal.depth_portal;

	borne->pillar = arch->portal.pillar;
	borne->next = arch->portal.next;
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
	arch->portal.b_left = borne->b_left;
	arch->portal.b_right = borne->b_right;
	while (start < arch->px.y)
	{
		arch->portal.b_up[start] = borne->b_up[i];
		arch->portal.b_down[start] = borne->b_down[i];
		arch->portal.zline[start] = borne->zline[i];
		start++;
		i++;
	}
	//-----arch->portal.decal_portal = borne->decal_portal;
	//-----arch->portal.depth_portal = borne->depth_portal;
	arch->portal.pillar = borne->pillar;
	arch->portal.next = borne->next;
	borne_free(borne);
}