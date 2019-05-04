/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:35:42 by tbottini          #+#    #+#             */
/*   Updated: 2019/05/04 21:27:42 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		draw_part_texture(t_doom *doom, t_ray ray, int *istart, int length)
{
//	int		i;
//	t_fvct2	ctexture;
//	float	dty;
//	int		it;
//
//	ray_polarity(&ray);
//	ctexture.x = (ray.hor < ray.ver) ? ray.inter_h.x : ray.inter_v.y;
//	ctexture.x = (ctexture.x - (int)ctexture.x) * (doom->wall[ray.polar].w);
//	ctexture.y = 0;
//	dty = (doom->wall[ray.polar].h) / (float)length;
//	if (length > doom->sdl.size.y)
//	{
//		ctexture.y = (((float)length - (float)doom->sdl.size.y) / 2);
//		ctexture.y = ctexture.y / (float)length * doom->wall[ray.polar].h;
//		length = doom->sdl.size.y - 1;
//	}
//	i = 0;
//	while (i < length)
//	{
//		it = (int)ctexture.x + (int)ctexture.y * doom->wall[ray.polar].w;
//		doom->sdl.screen[*istart] = doom->wall[ray.polar].txture[it];
//		ctexture.y += dty;
//		*istart += doom->sdl.size.x;
//		i++;
//	}
}
