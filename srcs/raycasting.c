/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:35:34 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/25 21:03:55 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	wolf->d_scrn = (wolf->sdl.size.x / 2.0) / tan(wolf->fov * PI180 / 2.0);
	while (i < wolf->sdl.size.x - 1)
	{
		ray.angle = atan(((wolf->sdl.size.x / 2.0) - i) / wolf->d_scrn);
		ray.angle = angle_adaptater(ray.angle * TOANGLE + wolf->rot);
		hor_detection(wolf, &ray);
		ver_detection(wolf, &ray);
		draw_column(wolf, ray, i);
		i++;
	}
	SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.txture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl.rend);
}
