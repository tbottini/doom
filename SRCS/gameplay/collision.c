/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 18:06:16 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 02:29:44 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int			can_pass(t_stat *stat, int i, t_wall **port)
{
	t_sector	*next;

	next = stat->sector->wall[i].link;
	if (next && stat->sector->wall[i].status >= OPEN_DOOR)
	{
		if ((stat->pos.z + stat->height < next->h_floor + next->h_ceil)
			&& (next->h_floor <= stat->pos.z + STEP))
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
			return (!(collision(next, stat->pos, NULL)) ? 1 : 2);
		}
		return (-1);
	}
	*port = &stat->sector->wall[i];
	return (0);
}

t_wall		*colli_walls(t_sector *sector, t_fvct3 ori, t_fvct3 pos, t_wall *w)
{
	int		i;

	if (w)
	{
		return (vector_intersect(ori, pos, *(t_fvct3*)&w->pillar->p,
		*(t_fvct3*)&w->next->p) ? w : 0);
	}
	i = -1;
	while (++i < sector->len)
	{
		if (!ISPORTAL(sector->wall[i].status)
			&& vector_intersect(ori, pos, *(t_fvct3*)&sector->wall[i].pillar->p,
			*(t_fvct3*)&sector->wall[i].next->p))
			return (&sector->wall[i]);
	}
	return (NULL);
}

int			colli_port(t_stat *stat, t_sector *sector, t_fvct3 ori, t_wall **w)
{
	int		i;

	i = -1;
	while (++i < sector->len)
	{
		if (vector_intersect(ori, stat->pos,
			*(t_fvct3*)&sector->wall[i].pillar->p,
			*(t_fvct3*)&sector->wall[i].next->p))
			return (can_pass(stat, i, w));
	}
	return (0);
}

t_wall		*collision(t_sector *sector, t_fvct3 pos, t_wall *w)
{
	t_fvct3		tmp;

	tmp.x = pos.x;
	tmp.y = pos.y + PADDING;
	pos.x += PADDING;
	if ((w = colli_walls(sector, pos, tmp, w)))
		return (w);
	tmp.y -= PADDING2;
	if ((w = colli_walls(sector, pos, tmp, w)))
		return (w);
	pos.x -= PADDING2;
	if ((w = colli_walls(sector, pos, tmp, w)))
		return (w);
	tmp.y += PADDING2;
	if ((w = colli_walls(sector, pos, tmp, w)))
		return (w);
	return (NULL);
}
