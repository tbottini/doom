/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 18:06:16 by akrache           #+#    #+#             */
/*   Updated: 2019/07/25 20:32:01 by akrache          ###   ########.fr       */
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

int			can_pass(t_stat *stat, int i, t_wall **port)
{
	t_sector *next;

	next = stat->sector->wall[i].link;
	if (next && stat->sector->wall[i].status >= OPEN_DOOR)
	{
		if ((stat->pos.z + stat->height < next->h_floor + next->h_ceil) && (next->h_floor <= stat->pos.z + STEP))
		{
			if (!collision(next, stat->pos, NULL))
			{
				stat->sector = next;
				if (stat->pos.z <= next->h_floor)
					stat->pos.z = next->h_floor;
				if (!stat->crouch && stat->height == H_CROUCH)
				{
					stat->height = H_NORMAL;
					stat->speed = WALK;
				}
				*port = NULL;
				return (1);
			}
		}
		return (-1);
	}
	*port = &stat->sector->wall[i];
	return (0);
}

/*
** Returns 1 if the segments [p1, q1] and [p2, q2] intersect, 0 Otherwise
*/
int			vector_intersect(t_fvct3 p1, t_fvct3 q1, t_fvct3 p2, t_fvct3 q2)
{
	if (orientation(p1, q1, p2) != orientation(p1, q1, q2)
		&& orientation(p2, q2, p1) != orientation(p2, q2, q1))
		return (1);
	return (0);
}

t_wall		*collisionV21(t_sector *sector, t_fvct3 ori, t_fvct3 pos, t_wall *w)
{
	int		i;

	if (w)
		return (vector_intersect(ori, pos, *(t_fvct3*)&w->pillar->p, *(t_fvct3*)&w->next->p) ? w : 0);
	i = -1;
	while (++i < sector->len)
	{
		if (!ISPORTAL(sector->wall[i].status) && vector_intersect(ori, pos, *(t_fvct3*)&sector->wall[i].pillar->p,
			*(t_fvct3*)&sector->wall[i].next->p))
				return (&sector->wall[i]);
	}
	return (NULL);
}

int			colli_teleport(t_stat *stat, t_sector *sector, t_fvct3 ori, t_wall **wall)
{
	int		i;

	i = -1;
	while (++i < sector->len)
	{
		if (vector_intersect(ori, stat->pos, *(t_fvct3*)&sector->wall[i].pillar->p,
			*(t_fvct3*)&sector->wall[i].next->p))
		{
			return (can_pass(stat, i, wall));
		}
	}
	return (0);
}

t_wall		*collision(t_sector *sector, t_fvct3 pos, t_wall *w)
{
	t_fvct3		tmp;

	tmp.x = pos.x;
	tmp.y = pos.y + PADDING;
	pos.x += PADDING;
	if ((w = collisionV21(sector, pos, tmp, w)))
		return (w);
	tmp.y -= PADDING2;
	if ((w = collisionV21(sector, pos, tmp, w)))
		return (w);
	pos.x -= PADDING2;
	if ((w = collisionV21(sector, pos, tmp, w)))
		return (w);
	tmp.y += PADDING2;
	if ((w = collisionV21(sector, pos, tmp, w)))
		return (w);
	return (NULL);
}
