/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:35:42 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/25 19:35:47 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ray_polarity(t_ray *ray)
{
	if (ray->ver < ray->hor)
	{
		ray->polar = (ray->angle > 90 && ray->angle < 270) ? 3 : 2;
	}
	else
	{
		ray->polar = (ray->angle > 180) ? 1 : 0;
	}
}

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

	ray_polarity(&ray);
	ctexture.x = (ray.hor < ray.ver) ? ray.inter_h.x : ray.inter_v.y;
	ctexture.x = (ctexture.x - (int)ctexture.x) * (wolf->wall[ray.polar].w);
	ctexture.y = 0;
	dty = (wolf->wall[ray.polar].h) / (float)length;
	if (length > wolf->sdl.size.y)
	{
		ctexture.y = (((float)length - (float)wolf->sdl.size.y) / 2);
		ctexture.y = ctexture.y / (float)length * wolf->wall[ray.polar].h;
		length = wolf->sdl.size.y - 1;
	}
	i = 0;
	while (i < length)
	{
		it = (int)ctexture.x + (int)ctexture.y * wolf->wall[ray.polar].w;
		wolf->sdl.screen[*istart] = wolf->wall[ray.polar].txture[it];
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
	draw_part(wolf, &iprint, sky_size, BLUE_SKY);
	draw_part_texture(wolf, ray, &iprint, column_size);
	draw_part(wolf, &iprint, sky_size, PINK_FLOOR);
}
