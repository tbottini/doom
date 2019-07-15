#include "doom_nukem.h"

/*
**	reinitialise la borne de l'arch sur les limites de la fenetres
*/
void		borne_reset(t_arch *arch)
{
	int			i;

	i = 0;
	while (i < arch->sdl->size.x)
	{
		arch->bound.b_up[i] = 0;
		arch->bound.b_down[i] = arch->sdl->size.y;
		arch->bound.zline[i] = 0;
		i++;
	}
	arch->bound.b_left = arch->cam->fov / 2.0;
	arch->bound.b_right = -arch->cam->fov / 2.0;
}

t_borne		*borne_init(t_borne *borne, int len)
{
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