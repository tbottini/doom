#include "wolf3d.h"

double		iswall(t_wolf *wolf, t_fvct2 inter)
{
	if (inter.x < wolf->map_size.x && inter.y < wolf->map_size.y
		&& inter.x > -1 && inter.y > -1)
	{
		if (wolf->map[(int)inter.y][(int)inter.x] == '#')
			return (1);
		return (0);
	}
	return (wolf->map_size.x + wolf->map_size.y);
}


 void		raycasting(t_wolf *wolf)
 {
 	t_ray	ray;
 	int		i;

 	i = 0;
 	//ray.angle = wolf->rot + wolf->fov / 2;
 	//iangle = wolf->fov / (float)wolf->sdl.size.x;
 	wolf->d_scrn = (wolf->sdl.size.x / 2.0) / tan(wolf->fov * PI180 / 2.0);
 	while (i < wolf->sdl.size.x - 1)
 	{
 		ray.angle = atan(((wolf->sdl.size.x / 2.0) - i) / wolf->d_scrn) * TOANGLE;
 		ray.angle += wolf->rot;
 		ray.angle = angle_adaptater(ray.angle);
 		hor_detection(wolf, &ray);
 		ver_detection(wolf, &ray);
 		draw_column(wolf, ray, i);
 		//ray.angle -= iangle;
 		i++;
 	}
 	SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.txture, NULL, NULL);
 	SDL_RenderPresent(wolf->sdl.rend);
}
