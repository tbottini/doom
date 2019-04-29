/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:35:34 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/26 15:13:00 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double		iswall(t_wolf *doom, t_fvct2 inter)
{
	if (inter.x < doom->map_size.x && inter.y < doom->map_size.y
		&& inter.x >= 0.0 && inter.y >= 0.0)
	{
		if (doom->map[(int)inter.y][(int)inter.x] == '#')
			return (1);
		return (0);
	}
	return (INT_MAX);
}

void		raycasting(t_wolf *doom)
{
	t_ray	ray;
	int		i;

	i = 0;
	doom->d_scrn = (doom->sdl.size.x / 2.0) / tan(doom->fov * PI180 / 2.0);
	while (i < doom->sdl.size.x)
	{
		ray.angle = atan(((doom->sdl.size.x / 2.0) - i) / doom->d_scrn);
		ray.angle = angle_adaptater(ray.angle * TOANGLE + doom->rot);
		hor_detection(doom, &ray);
		ver_detection(doom, &ray);
		draw_column(doom, ray, i);
		i++;
	}
	SDL_RenderCopy(doom->sdl.rend, doom->sdl.txture, NULL, NULL);
	SDL_RenderPresent(doom->sdl.rend);
}
