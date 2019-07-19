/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 18:06:16 by akrache           #+#    #+#             */
/*   Updated: 2019/07/19 15:18:27 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int orientation(t_fvct3 p, t_fvct3 q, t_fvct3 r)
{
	double val;

	val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0)
		return (0);
	return (val > 0) ? 1 : 2;
}

int			can_pass(t_stat *stat, int i)
{
	t_sector *next;

	next = stat->sector->wall[i].link;
	printf("can pass ?\n");
	if (stat->sector->wall[i].status >= OPEN_DOOR)
	{
		if ((stat->pos.z + stat->height < next->h_floor + next->h_ceil) && (next->h_floor <= stat->pos.z + STEP))
		{
			stat->sector = next;
			if (stat->pos.z <= next->h_floor)
				stat->pos.z = next->h_floor;
			printf("new pos z = %f\n", stat->pos.z);
			return (1);
		}
	}
	return (0);
}

int vector_intersect(t_fvct3 p1, t_fvct3 q1, t_fvct3 p2, t_fvct3 q2)
{
	if (orientation(p1, q1, p2) != orientation(p1, q1, q2)
		&& orientation(p2, q2, p1) != orientation(p2, q2, q1))
		return (1);
	return (0);
}

t_wall		*collisionV21(t_stat *stat, t_fvct3 ori, t_fvct3 pos, t_wall *w)
{
	int		i;

	if (w)
		return (vector_intersect(ori, pos, *(t_fvct3*)&w->pillar->p, *(t_fvct3*)&w->next->p) ? w : 0);
	i = -1;
	while (++i < stat->sector->len)
	{
		if (vector_intersect(ori, pos, *(t_fvct3*)&stat->sector->wall[i].pillar->p,
			*(t_fvct3*)&stat->sector->wall[i].next->p))
				return (&stat->sector->wall[i]);
	}
	return (NULL);
}

int			colli_teleport(t_stat *stat, t_fvct3 ori, t_fvct3 pos)
{
	int		i;

	i = -1;
	while (++i < stat->sector->len)
	{
		if (vector_intersect(ori, pos, *(t_fvct3*)&stat->sector->wall[i].pillar->p,
			*(t_fvct3*)&stat->sector->wall[i].next->p))
		{
			if (!can_pass(stat, i))
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

t_wall		*collision(t_stat *stat, t_fvct3 pos, t_wall *w)
{
	t_fvct3		tmp;

	tmp.x = pos.x;
	tmp.y = pos.y + PADDING;
	pos.x += PADDING;
	if ((w = collisionV21(stat, pos, tmp, w)))
		return (w);
	tmp.y -= PADDING2;
	if ((w = collisionV21(stat, pos, tmp, w)))
		return (w);
	pos.x -= PADDING2;
	if ((w = collisionV21(stat, pos, tmp, w)))
		return (w);
	tmp.y += PADDING2;
	if ((w = collisionV21(stat, pos, tmp, w)))
		return (w);
	return (NULL);
}
