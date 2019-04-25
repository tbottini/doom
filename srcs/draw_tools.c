#include "wolf3d.h"

void		draw_part(t_wolf *wolf, int *istart, int length, uint32_t color)
{
	int		i;

	i = 0;
	while (i < length)
	{
		wolf->sdl.screen[*istart] = color;
		*istart += wolf->sdl.size.x;
		i++;
	}
}

void		draw_part_texture(t_wolf *wolf, t_ray ray, int *istart, int length)
{
	int		i;
	t_fvct2	ctexture;
	float	dty;
	int		it;
	int		c;

	c = 3;

	ctexture.x = (ray.hor < ray.ver) ? ray.inter_h.x : ray.inter_v.y;
	ctexture.x = (ctexture.x - (int)ctexture.x) * (wolf->wl_txture[c]->w);
	ctexture.y = 0;
	dty = (wolf->wl_txture[c]->h) / (float)length;
	if (length > wolf->sdl.size.y)
	{
		ctexture.y = (((float)length - (float)wolf->sdl.size.y) / 2) / (float)length * wolf->wl_txture[c]->h;
		length = wolf->sdl.size.y - 1;
	}
	i = 0;
	while (i < length)
	{
		it = (int)ctexture.x + (int)ctexture.y * wolf->wl_txture[c]->w;
		wolf->sdl.screen[*istart] = wolf->wall[c][it];
		ctexture.y += dty;
		*istart += wolf->sdl.size.x;
		i++;
	}
}

void		draw_column(t_wolf *wolf, t_ray ray, int num)
{
	float	column_size;
	int		sky_size;
	int		i;
	int		iprint;
	float	dist;

	i = -1;
	dist = (ray.hor < ray.ver) ? ray.hor : ray.ver;
	dist *= cos(fabs(wolf->rot - ray.angle) * PI / 180.00);
	column_size = (wolf->sdl.size.y * 0.8) / dist;
	sky_size = (wolf->sdl.size.y - column_size) / 2;
	iprint = num;
	// if (dist < 0.8)
	 //	draw_part_texture(wolf, ray, &iprint, column_size);
	draw_part(wolf, &iprint, sky_size, BLUE_SKY);
	draw_part_texture(wolf, ray, &iprint, column_size);
	draw_part(wolf, &iprint, sky_size, PINK_FLOOR);
}
