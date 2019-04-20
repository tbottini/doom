#include "wolf3d.h"

float		iswall(t_wolf *wolf, t_fvct2 inter)
{
	//printf("test wolf->map[.y%d][.x%d]\n", (int)inter.y, (int)inter.x);
	if (inter.x < wolf->map_size.x && inter.y < wolf->map_size.y
		&& inter.x > -1 && inter.y > -1)
	{
		if (wolf->map[(int)inter.y][(int)inter.x] == '#' || wolf->map[(int)inter.y][(int)inter.x] == '*')
		{
			wolf->map[(int)inter.y][(int)inter.x] = '*';
			return (1);
		}
		return (0);
	}
	return (-1);
}

float		hor_detection(t_wolf *wolf, float angle)
{
	t_fvct2		ratio;
	t_fvct2		inter;
	t_fvct2		dist;
	float		ret;

	ratio.y = (angle < 180) ? 1 : -1;
	ratio.x = ratio.y / tan(angle * PI / 180);
	inter.y = (int)wolf->pos.y + ((angle < 180) ? 1 : 0);
	inter.x = wolf->pos.x + fabs(inter.y - wolf->pos.y) * ratio.x;
	inter.y += ((angle > 180) ? -1: 0);
	//printf("first inter hor .x %f .y %f\n", inter.x, inter.y);
	while ((ret = iswall(wolf, inter)) == 0)
	{
		inter.y += ratio.y;
		inter.x += ratio.x;
	}
	if (ret == 1)
	{
		dist.x = inter.x - wolf->pos.x;
		dist.y = inter.y - wolf->pos.y + ((angle > 180) ? 1 : 0);
		ret = sqrt(dist.x * dist.x + dist.y * dist.y) * cos((wolf->rot - angle) * PI / 180);
	}
	return (ret);
}

float		ver_detection(t_wolf *wolf, float angle)
{
	t_fvct2		ratio;
	t_fvct2		inter;
	t_fvct2		dist;
	float		ret;

	ratio.x = (angle < 90 || angle > 270) ? 1 : -1;
	ratio.y = ratio.x / tan((90 - angle) * PI / 180);
	inter.x = (int)wolf->pos.x + ((angle < 90 || angle > 270) ? 1 : 0);
	inter.y = wolf->pos.y + fabs(inter.x - wolf->pos.x) * ratio.y;
	inter.x += (angle < 90 || angle > 270) ? 0 : -1;
	while ((ret = iswall(wolf, inter)) == 0)
	{
		inter.y += ratio.y;
		inter.x += ratio.x;
	}
	if (ret == 1)
	{
		dist.x = (inter.x + ((angle > 90 && angle < 270) ? 1 : 0)) - wolf->pos.x;
		dist.y = inter.y - wolf->pos.y;
		ret = sqrt(dist.x * dist.x + dist.y * dist.y) * cos((wolf->rot - angle) * PI / 180);
	}
	return (ret);
}

void		draw_column(t_wolf *wolf, float dist, int num)
{
	float	column_size;
	int		i;
	int		iprint;
	int		imax;

	dist = (dist > 0.8) ? dist : 0.8;
	column_size = (wolf->sdl.size.y * 0.8) / dist;
	i = 0;
	imax = (wolf->sdl.size.y - column_size) / 2;
	iprint = num;
	while (i < imax)
	{
		wolf->sdl.screen[iprint] = color_rgb(0, 123, 255);
		i++;
		iprint += wolf->sdl.size.x;
	}
	imax = i + column_size;
	while (i < imax - 1)
	{
		wolf->sdl.screen[iprint] = color_rgb(255, 0, 0);
		i++;
		iprint += wolf->sdl.size.x;
	}
	while (i < wolf->sdl.size.y)
	{
		wolf->sdl.screen[iprint] = color_rgb(100, 100, 100);
		i++;
		iprint += wolf->sdl.size.x;
	}
}

void		raycasting(t_wolf *wolf)
{
	float	iangle;
	float	angle;
	int		i;
	t_fvct2	dist;

	i = 0;
	angle = wolf->rot + wolf->fov / 2;
	iangle = wolf->fov / (float)wolf->sdl.size.x;
	while (i < wolf->sdl.size.x - 1)
	{
		angle = angle_adaptater(angle);
		dist.x = hor_detection(wolf, angle);
		dist.y = ver_detection(wolf, angle);
		if ((int)dist.x != -1 && (int)dist.y != -1)
			draw_column(wolf, ((dist.x < dist.y) ? dist.x : dist.y), i);
		else if ((int)dist.x != -1)
			draw_column(wolf, dist.x, i);
		else if ((int)dist.y != -1)
			draw_column(wolf, dist.y, i);
		else
			draw_column(wolf, 10000000, i);
		angle -= iangle;
		i++;
	}
	SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.txture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl.rend);
}

void		raythrowing(t_wolf *wolf, int ag)
{
	t_fvct2	dist;
	int j = wolf->map_size.y - 2;

	dist.x = hor_detection(wolf, (float)ag);
	dist.y = ver_detection(wolf, (float)ag);
	printf("hor %f ver %f\n", dist.x, dist.y);
	while (j != -1)
	{
		ft_putendl(wolf->map[j]);
		j--;
	}
}
