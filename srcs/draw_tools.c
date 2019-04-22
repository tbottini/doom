#include "wolf3d.h"

void		draw_part(t_wolf *wolf, int *istart, int lenght, uint32_t color)
{
	int		i;

	i = 0;
	while (i < lenght)
	{
		wolf->sdl.screen[*istart] = color;
		*istart += wolf->sdl.size.x;
		i++;
	}
}

void		draw_column_texture(t_wolf *wolf, int *istart, int lenght)
{
	int		i;
	int		itexture;

	i = 0;
	while (i < lenght)
	{
		wolf->sdl.screen[*istart] = RED_WALL;
		*istart += wolf->sdl.size.x;
		i++;
	}
}

void		draw_column(t_wolf *wolf, float dist, int num)
{
	float	column_size;
	int		sky_size;
	int		i;
	int		iprint;

	i = -1;
	dist = (dist > 0.8) ? dist : 0.8;
	column_size = (wolf->sdl.size.y * 0.8) / dist;
	sky_size = (wolf->sdl.size.y - column_size) / 2;
	iprint = num;
	draw_part(wolf, &iprint, sky_size, BLUE_SKY);
	draw_part(wolf, &iprint, column_size, RED_WALL);
	draw_part(wolf, &iprint, wolf->sdl.size.y, PINK_FLOOR);
}