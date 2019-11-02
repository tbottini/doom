/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 21:02:06 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 15:43:01 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

extern inline bool	column_is_printable(t_arch *arch, t_prop *prop)
{
	return (arch->px.x > prop->px.x
			&& arch->px.x < prop->px.y
			&& prop->pos.z + 1.0 > 0
			&& prop->pos.z < arch->sector->h_ceil);
}

void				props_draw_column(t_prop *props, t_arch *a
	, t_fvct2 s)
{
	int				i;
	t_fvct2			hei;
	int				padding_render;
	t_needle		needle;

	i = 0;
	while (i <= a->wall->nb_props)
	{
		if (column_is_printable(a, &props[i]))
		{
			hei.x = (a->sector->h_ceil - 1 - (props[i].pos.z
				- a->sector->h_floor)) / a->sector->h_ceil;
			hei.y = (props[i].pos.z - a->sector->h_floor) / a->sector->h_ceil;
			padding_render = (s.y - s.x) * hei.x;
			needle.surface.x = s.x + (s.y - s.x) * hei.x;
			needle.surface.y = s.y - (s.y - s.x) * hei.y;
			needle.numcol = a->px.x + needle.surface.x * a->sdl->size.x;
			draw_part_prop(a, &needle, (t_vct2){s.x, s.y}, &props[i]);
			break ;
		}
		i++;
	}
}
