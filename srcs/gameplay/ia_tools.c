/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 03:22:50 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 03:34:16 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		update_enemy_rotation(t_enemy *enemy, t_stat *s, t_fvct3 pos)
{
	s->rot.y = atan2(pos.x - s->pos.x, pos.y - s->pos.y);
	enemy->e1.x = s->pos.x + sin(s->rot.y - (90.0 * PI180)) * s->height / 4;
	enemy->e1.y = s->pos.y + cos(s->rot.y - (90.0 * PI180)) * s->height / 4;
	enemy->e2.x = s->pos.x + sin(s->rot.y + (90.0 * PI180)) * s->height / 4;
	enemy->e2.y = s->pos.y + cos(s->rot.y + (90.0 * PI180)) * s->height / 4;
}

/*
** returns true if point pos is between point target
** and both points m1 and m2, false otherwise
*/

bool		is_between(t_fvct3 pos, t_fvct3 target, t_fvct3 m1, t_fvct3 m2)
{
	double dist;

	dist = distance((t_fvct2){target.x, target.y}, (t_fvct2){pos.x, pos.y});
	if (dist < distance((t_fvct2){target.x, target.y}, (t_fvct2){m1.x, m1.y})
	&& dist < distance((t_fvct2){target.x, target.y}, (t_fvct2){m2.x, m2.y}))
		return (false);
	return (true);
}

/*
** returns 1 if target is visible from stat's point of view
*/

int			is_visible(t_stat *stat, t_stat *target,
t_sector *sector, int passed)
{
	int res;
	int i;

	i = -1;
	res = 0;
	if (passed > 10)
		return (1);
	while (++i < sector->len)
	{
		if (vector_intersect(stat->pos, target->pos,
		*(t_fvct3*)&sector->wall[i].pillar->p,
		*(t_fvct3*)&sector->wall[i].next->p))
		{
			return (sector->wall[i].status >= OPEN_DOOR
			&& sector->wall[i].link != sector
			&& is_between(stat->pos, target->pos,
			*(t_fvct3*)&sector->wall[i].pillar->p,
			*(t_fvct3*)&sector->wall[i].next->p)
			? is_visible(stat, target,
			sector->wall[i].link, passed + 1) : 0);
		}
	}
	return (1);
}

void		is_around_recur(t_doom *d, t_sector **passed,
t_sector *s, int *index)
{
	int i;

	i = 0;
	while (i < s->len)
	{
		if (s->wall[i].status >= OPEN_DOOR && s->wall[i].link
		&& !is_passed(s->wall[i].link, passed, *index))
			is_around(d, s->wall[i].link, passed, index);
		i++;
	}
}

void		is_around(t_doom *d, t_sector *s,
t_sector **passed, int *index)
{
	t_enemy		*t;
	t_enemy		*tmp2;

	t = s->enemys;
	while (t)
	{
		tmp2 = t->next;
		if (t->state == -1)
		{
			if (is_visible(&t->stat, &d->game.player.stat, t->stat.sector, 0))
				t->state = 0;
			set_txtr(&t->sprites, d->game.ui->enemy[(t->type - 1) * 6], 0);
		}
		else if (t->state != -1)
		{
			ai_active(d, t, s);
		}
		t = tmp2;
	}
	if (*index == d->game.len.nb_sects - 1)
		return ;
	passed[*index] = s;
	(*index)++;
	is_around_recur(d, passed, s, index);
}
