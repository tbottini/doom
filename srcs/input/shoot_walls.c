/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 21:41:46 by akrache           #+#    #+#             */
/*   Updated: 2019/06/27 19:35:33 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static double	bullet_clipping(t_wall wall, t_stat *stat)
{
	t_fvct2		inter;
	t_fvct2		diff;
	t_fvct2		diff2;
	double		coef_wall;
	double		b;

	diff.x = wall.pillar.p.x - stat->pos.x;
	diff.y = wall.pillar.p.y - stat->pos.y;
	diff2.x = wall.next->p.x - stat->pos.x;
	diff2.y = wall.next->p.y - stat->pos.y;
	if (diff2.x - diff.x < 0.0001 && diff2.x - diff.x > -0.0001)
	{
		inter.x = diff.x;
		inter.y = diff.x * tan(stat->rot.y * PI180);
	}
	else
	{
		coef_wall = (diff2.y - diff.y) / (diff2.x - diff.x);
		b = diff.y - diff.x * coef_wall;
		inter.x = b / (tan(stat->rot.y * PI180) - coef_wall);
		inter.y = coef_wall * inter.x + b;
	}
	return (distance((t_fvct2){0.0, 0.0}, inter));
}

static t_wall	*real_hit(t_wall **walls, t_stat *stat)
{
	t_wall	*hit;
	int		i;
	double	res;
	double	tmp;
	double	toto;

	i = 0;
	res = 987654321.0;
	hit = NULL;
	toto = cos((stat->rot.x - 90.0) * PI180);
	if (toto < G_EPSILON)
		toto = 1;
	while (walls[i])
	{
		if ((tmp = bullet_clipping(*walls[i], stat)) / toto < res)
		{
			res = tmp;
			hit = walls[i];
		}
		++i;
	}
	if (hit)
		hit->dist = res;
	return (hit);
}

t_wall			*possible_walls(t_wall **walls, t_stat *stat, t_fvct3 ori)
{
	int		i;
	int		j;
	int		index;

	j = -1;
	index = 0;
	while (index < 49 && ++j < stat->sector->len_sub)
	{
		i = -1;
		while (index < 49 && ++i < stat->sector->ssector[j].len)
		{
			if (vector_intersect(ori, stat->pos, *(t_fvct3*)&stat->sector->ssector[j].wall[i].pillar.p, *(t_fvct3*)&stat->sector->ssector[j].wall[i].next->p))
			{
				walls[index] = &stat->sector->ssector[j].wall[i];
				index++;
			}
		}
	}
	i = -1;
	while (index < 49 && ++i < stat->sector->len)
	{
		if (vector_intersect(ori, stat->pos, *(t_fvct3*)&stat->sector->wall[i].pillar.p, *(t_fvct3*)&stat->sector->wall[i].next->p))
		{
			walls[index] = &stat->sector->wall[i];
			index++;
		}
	}
	walls[index] = NULL;
	return (real_hit(walls, stat));
}

void			apply_wall(t_wall *wall, t_stat *stat, t_fvct3 mo)
{
	t_fvct3 aim;

	aim.x = stat->pos.x + wall->dist * (mo.x / RADIUS);
	aim.y = stat->pos.y + wall->dist * (mo.y / RADIUS);
	aim.z = stat->pos.z + wall->dist * (mo.z / RADIUS);
	(void)wall;//apply texture on wall
	printf("SUPER COORD : x = %f | y = %f | z = %f\n", aim.x, aim.y, aim.z);
	printf("distance || %f ||\n\n", wall->dist);
}
