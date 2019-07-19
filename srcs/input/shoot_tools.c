/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:05:13 by akrache           #+#    #+#             */
/*   Updated: 2019/07/19 12:12:03 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static double	wall_bullet_clipping(t_pillar wall, t_pillar next, t_stat *stat)
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

static double	enemy_bullet_clipping(t_enemy *enemy, t_stat *stat)
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

static void			enemy_hitbox(t_enemy *enemy, double angle)
{
	enemy->e1.x = sin((angle - 90.0) * PI180) * (enemy->stat.width / 2);
	enemy->e1.y = cos((angle - 90.0) * PI180) * (enemy->stat.width / 2);
	enemy->e2.x = sin((angle + 90.0) * PI180) * (enemy->stat.width / 2);
	enemy->e2.y = cos((angle + 90.0) * PI180) * (enemy->stat.width / 2);
}

static void		super_super_real_hit(t_super *super, t_stat *stat, double toto)
{
	int		i;
	double	res;
	double	tmp;

	i = -1;
	res = 987654321.0;
	while (super->enemys[++i])
	{
		if ((tmp = enemy_bullet_clipping(super->enemys[i], stat)) / toto < res)
		{
			res = tmp;
			super->ehit = super->enemys[i];
		}
	}
	super->edist = res;
}

void		super_real_hit(t_super *super, t_stat *stat)
{
	int		i;
	double	res;
	double	tmp;
	double	toto;

	res = 987654321.0;
	toto = cos((stat->rot.x - 90.0) * PI180);
	if (toto < G_EPSILON)
		toto = 1;
	i = -1;
	while (super->walls[++i])
	{
		if ((tmp = wall_bullet_clipping(*super->walls[i]->pillar, *super->walls[i]->next, stat)) / toto < res)
		{
			res = tmp;
			super->whit = super->walls[i];
		}
	}
	super->wdist = res;
	super_super_real_hit(super, stat, toto);
}

static int	bullet_can_pass(t_stat *stat, int i, t_sector *sector, t_fvct3 ori)
{
	double		toto;
	t_fvct3		mo;
	t_fvct3		coord;
	t_sector	next;

	next = *sector->wall[i].link;
	if (sector->wall[i].status >= OPEN_DOOR)
	{
		toto = cos((stat->rot.x - 90.0) * PI180);
		toto = wall_bullet_clipping(*sector->wall[i].pillar, *sector->wall[i].next, stat) / (toto < G_EPSILON ? 1 : toto);
		mo.x = ori.x - stat->pos.x;
		mo.y = ori.y - stat->pos.y;
		mo.z = ori.y - stat->pos.z;
		coord = real_coord(stat->pos, toto, ori);
		if ((coord.z < next.h_floor + next.h_ceil) && (next.h_floor < coord.z))
			return (1);
	}
	return (0);
}

void		possible_enemys(t_super *super, t_stat *stat, t_fvct3 ori, t_sector *sector)
{
	t_enemy	*tmp;

	tmp = sector->enemys;
	while (super->i_e < 50 && tmp)
	{
		enemy_hitbox(tmp, stat->rot.y);
		if (vector_intersect(ori, stat->pos, tmp->e1, tmp->e2))
		{
			super->enemys[super->i_e] = tmp;
			super->i_e++;
		}
		tmp = tmp->next;
	}
	super->enemys[super->i_e] = NULL;
}

void		possible(t_super *super, t_stat *stat, t_fvct3 ori, t_sector *sector)
{
	int		i;

	i = -1;
	if (!sector)
		return ;
	while (super->i_w < 49 && ++i < sector->len)
	{
		if (vector_intersect(ori, stat->pos, *(t_fvct3*)&sector->wall[i].pillar->p, *(t_fvct3*)&sector->wall[i].next->p))
		{
			if (bullet_can_pass(stat, i, sector, ori))
				possible(super, stat, ori, sector->wall[i].link);
			else
			{
				super->walls[super->i_w] = &sector->wall[i];
				super->i_w++;
			}
		}
	}
	super->walls[super->i_w] = NULL;
	possible_enemys(super, stat, ori, sector);
}
