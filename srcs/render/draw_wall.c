#include "doom_nukem.h"

void		draw_part(t_doom doom, int *istart, int length, uint32_t color)
{
	int		i;

	i = 0;
	while (i < length)
	{
		doom.sdl.screen[*istart] = color;
		*istart += doom.sdl.size.x;
		i++;
	}
}

void		draw_wall(t_doom doom, int px, float dist)
{
	float	column_size;
	int		sky_size;
	int		i;
	int		iprint;

	i = -1;
	//printf("dist =====%f=====\n", dist);
	//printf("px   =====%d=====\n", px);
	iprint = px;

	draw_part(doom, &iprint, 100, INT_MAX);
	//dist *= cos(fabs(wolf->rot - ray.angle) * PI / 180.00);
	column_size = doom.sdl.size.y / dist;
	sky_size =  (doom.sdl.size.y - (int)column_size) / 2;
	iprint = px;
	printf("column_size=====%d/%d====\n", (int)column_size, doom.sdl.size.y);
	printf("column_id  -----%d------\n", px);
	draw_part(doom, &iprint, sky_size, BLUE_SKY);
	draw_part(doom, &iprint, column_size, INT_MAX);
	sky_size += ((doom.sdl.size.y - (int)column_size) % 2);
	draw_part(doom, &iprint, sky_size, PINK_FLOOR);
}
