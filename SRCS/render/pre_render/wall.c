/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 04:35:20 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 15:27:54 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "calcul.h"

extern inline int		is_door(t_arch *arch)
{
	return (arch->wall->status == OPEN_DOOR
		|| arch->wall->status == CLOSE_DOOR);
}

/*
**	trouve l'intersection entre le mur et un angle donne
**	renvoie le pourcentage de l'intersection par rapport au mur (debut pilier)
*/

double					wall_clipping(t_arch *arch, t_player *p
	, t_fvct2 *inter_local, double angle)
{
	t_fvct2				inter;
	t_fvct2				diff[2];
	t_affine			a_wall;
	t_affine			a_view;
	double				percent;

	diff[0] = fvct2_sub(arch->wall->pillar->p, *(t_fvct2*)&p->stat.pos);
	diff[1] = fvct2_sub(arch->wall->next->p, *(t_fvct2*)&p->stat.pos);
	a_view = (t_affine){tan(angle * PI180), 0, 0};
	if (diff[1].x == diff[0].x && diff[1].x == diff[0].x)
	{
		inter.x = diff[0].x;
		inter.y = diff[0].x * a_view.a;
		percent = (diff[1].y - inter.y) / (diff[1].y - diff[0].y);
	}
	else
	{
		a_wall = affine_points(diff[0], diff[1]);
		inter = interpolation_linear(a_wall, a_view);
		percent = (diff[1].x - inter.x) / (diff[1].x - diff[0].x);
	}
	*inter_local = player_local_pos(p, inter, angle);
	return (percent);
}
