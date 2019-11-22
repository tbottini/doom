/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:05:13 by akrache           #+#    #+#             */
/*   Updated: 2019/08/26 21:46:56 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

double			wall_bullet_clipping(t_pillar wall, t_pillar next, t_stat *stat)
{
	t_fvct2		inter;
	t_fvct2		diff;
	t_fvct2		diff2;
	double		coef;
	double		b;

	diff.x = wall.p.x - stat->pos.x;
	diff.y = wall.p.y - stat->pos.y;
	diff2.x = next.p.x - stat->pos.x;
	diff2.y = next.p.y - stat->pos.y;
	if (diff2.x - diff.x < 0.0001 && diff2.x - diff.x > -0.0001)
	{
		inter.x = diff.x;
		inter.y = diff.x * tan(stat->rot.y * PI180);
	}
	else
	{
		coef = (diff2.y - diff.y) / (diff2.x - diff.x);
		b = diff.y - diff.x * coef;
		inter.x = b / (tan(stat->rot.y * PI180) - coef);
		inter.y = coef * inter.x + b;
	}
	return (distance((t_fvct2){0.0, 0.0}, inter));
}

double			enemy_bullet_clipping(t_enemy *enemy, t_stat *stat)
{
	t_fvct2		inter;
	t_fvct2		diff;
	t_fvct2		diff2;
	double		coef;
	double		b;

	diff.x = enemy->e1.x - stat->pos.x;
	diff.y = enemy->e1.y - stat->pos.y;
	diff2.x = enemy->e2.x - stat->pos.x;
	diff2.y = enemy->e2.y - stat->pos.y;
	if (diff2.x - diff.x < 0.0001 && diff2.x - diff.x > -0.0001)
	{
		inter.x = diff.x;
		inter.y = diff.x * tan(stat->rot.y * PI180);
	}
	else
	{
		coef = (diff2.y - diff.y) / (diff2.x - diff.x);
		b = diff.y - diff.x * coef;
		inter.x = b / (tan(stat->rot.y * PI180) - coef);
		inter.y = coef * inter.x + b;
	}
	return (distance((t_fvct2){0.0, 0.0}, inter));
}

static int		bullet_can_pass(t_stat *stat, int i, t_sector *s, t_fvct3 ori)
{
	double		toto;
	t_fvct3		mo;
	t_fvct3		coord;
	t_sector	*next;

	next = s->wall[i].link;
	if (next && s->wall[i].status >= OPEN_DOOR)
	{
		toto = cos((stat->rot.x - 90.0) * PI180);
		toto = wall_bullet_clipping(*s->wall[i].pillar,
		*s->wall[i].next, stat) / (toto < G_EPSILON ? 1 : toto);
		mo.x = ori.x - stat->pos.x;
		mo.y = ori.y - stat->pos.y;
		mo.z = ori.y - stat->pos.z;
		coord = real_coord(stat->pos, toto, ori, stat);
		if ((coord.z < next->h_floor + next->h_ceil)
				&& (next->h_floor < coord.z))
			return (1);
	}
	return (0);
}

static void		possible_enemys(t_shoot *s, t_stat *stat,
t_fvct3 ori, t_sector *sector)
{
	t_enemy	*t;

	t = sector->enemys;
	while (s->i_e < 50 && t)
	{
		if (t->state != 4 && vector_intersect(ori, stat->pos, t->e1, t->e2))
		{
			s->enemys[s->i_e] = t;
			s->i_e++;
		}
		t = t->next;
	}
}

void			possible(t_shoot *shoot, t_stat *stat,
t_fvct3 ori, t_sector *s)
{
	int		i;

	i = -1;
	if (!s || is_passed(s, shoot->passed, shoot->index))
		return ;
	shoot->passed[shoot->index] = s;
	shoot->index++;
	while (shoot->i_w < 49 && ++i < s->len)
	{
		if (vector_intersect(ori, stat->pos,
		*(t_fvct3*)&s->wall[i].pillar->p, *(t_fvct3*)&s->wall[i].next->p))
		{
			if (!is_passed(s->wall[i].link, shoot->passed, shoot->index)
			&& bullet_can_pass(stat, i, s, ori))
				possible(shoot, stat, ori, s->wall[i].link);
			else if (s->wall[i].status < OPEN_DOOR)
			{
				shoot->walls[shoot->i_w] = &s->wall[i];
				shoot->i_w++;
			}
		}
	}
	possible_enemys(shoot, stat, ori, s);
}
