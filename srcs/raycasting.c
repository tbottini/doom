#include "wolf3d.h"

float		iswall(t_wolf *wolf, t_fvct2 inter)
{
	if (inter.x < wolf->map_size.x && inter.y < wolf->map_size.y
		&& inter.x > -1 && inter.y > -1)
	{
		if (wolf->map[(int)inter.y][(int)inter.x] == '#')
			return (1);
		return (0);
	}
	return (-1);
}

void		raycasting(t_wolf *wolf)
{
	t_ray	ray;
	float	iangle;
	int		i;

	i = 0;
	ray.angle = wolf->rot + wolf->fov / 2;
	iangle = wolf->fov / (float)wolf->sdl.size.x;

	while (i < wolf->sdl.size.x - 1)
	{
		ray.angle = angle_adaptater(ray.angle);
		hor_detection(wolf, &ray);
		ver_detection(wolf, &ray);
		if ((int)ray.hor != -1 && (int)ray.ver != -1)
			draw_column(wolf, ((ray.hor < ray.ver) ? ray.hor : ray.ver), i);
		else if ((int)ray.hor != -1)
			draw_column(wolf, ray.hor, i);
		else if ((int)ray.ver != -1)
			draw_column(wolf, ray.ver, i);
		else
			draw_column(wolf, 10000000, i);
		ray.angle -= iangle;
		i++;
	}
	SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.txture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl.rend);
}
