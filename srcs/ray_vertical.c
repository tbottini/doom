/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_vertical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:35:27 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/25 21:01:59 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		init_ray_ver(t_wolf *w, t_ray *r)
{
	if (r->angle < 90 || r->angle > 270)
	{
		r->ratio.x = 1;
		r->ratio.y = r->ratio.x / tan((90 - r->angle) * PI180);
		r->inter_v.x = (int)w->pos.x + 1;
		r->inter_v.y = w->pos.y + fabs(r->inter_v.x - w->pos.x) * r->ratio.y;
		return ;
	}
	r->ratio.x = -1;
	r->ratio.y = r->ratio.x / tan((90 - r->angle) * PI180);
	r->inter_v.x = (int)w->pos.x - 1;
	r->inter_v.y = w->pos.y + fabs(r->inter_v.x - w->pos.x + 1) * r->ratio.y;
}

float		ver_detection(t_wolf *wolf, t_ray *ray)
{
	t_fvct2		dist;

	init_ray_ver(wolf, ray);
	while ((ray->ver = iswall(wolf, ray->inter_v)) == 0)
	{
		ray->inter_v.y += ray->ratio.y;
		ray->inter_v.x += ray->ratio.x;
	}
	if (ray->ver == 1)
	{
		dist.y = ray->inter_v.y - wolf->pos.y;
		dist.x = ray->inter_v.x - wolf->pos.x;
		if (ray->angle > 90 && ray->angle < 270)
			dist.x++;
		ray->ver = sqrt(dist.x * dist.x + dist.y * dist.y);
	}
	return (ray->ver);
}
