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
	arch->borne.x *= TOANGLE;
	arch->borne.y *= TOANGLE;
}

/*
**	sauvegarde toute les configuration de borne dans une structure
**	dans une zone (la zone est les limite de px)
*/
t_borne		*borne_svg(t_arch *arch, t_borne *borne)
{
	int		len;

	len = arch->px.y - arch->px.x;
	borne->b_left = arch->borne.x;
	borne->b_right = arch->borne.y;
	borne->b_down = (uint32_t*)malloc(sizeof(uint32_t) * len);
	if (!borne->b_down)
		return (NULL);
	borne->b_up = (uint32_t*)malloc(sizeof(uint32_t) * len);
	if (!borne->b_up)
	{
		free(borne->b_down);
		return (NULL);
	}
	borne->zline = (double*)malloc(sizeof(double) * len);
	if (!borne->zline)
	{
		free(borne->b_down);
		free(borne->b_up);
		return (NULL);
	}
	return (borne);
}

void		borne_free(t_borne *borne)
{
	free(borne->b_down);
	free(borne->b_up);
	free(borne->zline);
}

void		borne_load(t_arch *arch, t_borne *borne, int start)
{
	int		i;

	i = 0;
	arch->borne.x = borne->b_left;
	arch->borne.y = borne->b_right;
	while (start < arch->px.y)
	{
		arch->borne_up[start] = borne->b_up[i];
		arch->borne_down[start] = borne->b_down[i];
		arch->zline[start] = borne->zline[i];
		start++;
		i++;
	}
	borne_free(borne);
}