/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:35:42 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/26 14:07:15 by tbottini         ###   ########.fr       */
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

void		draw_part(t_wolf *doom, int *istart, int length, uint32_t color)
{
	int		i;

	i = 0;
	while (i < length)
	{
		doom->sdl.screen[*istart] = color;
		*istart += doom->sdl.size.x;
		i++;
	}
}

void		draw_part_texture(t_wolf *doom, t_ray ray, int *istart, int length)
{
	int		i;
	t_fvct2	ctexture;
	float	dty;
	int		it;

	ray_polarity(&ray);
	ctexture.x = (ray.hor < ray.ver) ? ray.inter_h.x : ray.inter_v.y;
	ctexture.x = (ctexture.x - (int)ctexture.x) * (doom->wall[ray.polar].w);
	ctexture.y = 0;
	dty = (doom->wall[ray.polar].h) / (float)length;
	if (length > doom->sdl.size.y)
	{
		ctexture.y = (((float)length - (float)doom->sdl.size.y) / 2);
		ctexture.y = ctexture.y / (float)length * doom->wall[ray.polar].h;
		length = doom->sdl.size.y - 1;
	}
	i = 0;
	while (i < length)
	{
		it = (int)ctexture.x + (int)ctexture.y * doom->wall[ray.polar].w;
		doom->sdl.screen[*istart] = doom->wall[ray.polar].txture[it];
		ctexture.y += dty;
		*istart += doom->sdl.size.x;
		i++;
	}
}

void		draw_column(t_wolf *doom, t_ray ray, int num)
{
	float	column_size;
	int		sky_size;
	int		i;
	int		iprint;
	float	dist;

	i = -1;
	dist = (ray.hor < ray.ver && ray.hor > -0.1) ? ray.hor : ray.ver;
	dist *= cos(fabs(doom->rot - ray.angle) * PI / 180.00);
	column_size = (doom->sdl.size.y * 0.8) / dist;
	sky_size = (doom->sdl.size.y - column_size) / 2.0;
	iprint = num;
	draw_part(doom, &iprint, sky_size, BLUE_SKY);
	draw_part_texture(doom, ray, &iprint, column_size);
	draw_part(doom, &iprint, sky_size, PINK_FLOOR);
}
