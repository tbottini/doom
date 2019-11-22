/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 04:31:03 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 04:41:05 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	kick_button(t_stat *stat, t_fvct3 d, Uint32 timestamp)
{
	t_wall	*wallhit;
	int		x;

	if (!(wallhit = colli_walls(stat->sector, stat->pos, d, NULL)))
		return ;
	x = -1;
	while (++x < wallhit->nb_props)
	{
		if (in_hitbox(&wallhit->props[x].hitbox, stat->pos, stat->height / 2))
		{
			if (wallhit->props[x].type == MINWPROPSPOS)
			{
				wallhit->props[x].func(&wallhit->props[x]);
				if (wallhit->props[x].wall)
					wallhit->props[x].wall->ots = timestamp;
			}
		}
	}
}

void		kick(Uint32 timestamp, t_sound *sound, t_player *pl, t_stat *s)
{
	t_fvct3	d;
	t_enemy	*tmp;
	t_enemy	*tmp2;

	tmp = s->sector->enemys;
	d.x = s->pos.x + RANGE * sin(s->rot.x * PI180) * cos(s->rot.y * PI180);
	d.y = s->pos.y + RANGE * sin(s->rot.x * PI180) * sin(s->rot.y * PI180);
	d.z = s->pos.z + -(RANGE * cos(s->rot.x * PI180)) + (s->height / 2);
	while (tmp)
	{
		tmp2 = tmp->next;
		if (vector_intersect(d, s->pos, tmp->e1, tmp->e2))
		{
			injure_enemy(tmp, pl->weapons[0].dmg, d);
			Mix_PlayChannel(2, sound->tab_effect[6], 0);
			pl->timeact = timestamp;
			pl->occupied = timestamp + 1000;
			return ;
		}
		tmp = tmp2;
	}
	kick_button(s, d, timestamp);
	pl->act = false;
	pl->timeact = timestamp;
	pl->occupied = timestamp + 1000;
}

void		shoot(Uint32 timestamp, t_sound *sound, t_player *player, int nbs)
{
	if (player->occupied < timestamp)
	{
		if (player->hand->id == FIST)
			kick(timestamp, sound, player, &player->stat);
		else if (player->hand->clip == 0)
			reload(timestamp, player, player->hand, sound);
		else
		{
			bullet(&player->stat, player->hand->dmg, nbs);
			player->act = false;
			player->timeact = timestamp;
			if (player->hand->id == SHOTGUN)
				Mix_PlayChannel(2, sound->tab_effect[8], 0);
			else
				Mix_PlayChannel(2, sound->tab_effect[7], 0);
			player->hand->clip--;
			if (player->hand->rate)
				player->occupied = timestamp + 150;
			else
				player->occupied = timestamp + 500;
		}
	}
}

void		enemy_real_hit(t_shoot *s, t_stat *stat, double t, t_fvct3 mo)
{
	int		i;
	double	res;
	double	tmp;
	t_fvct3	p;

	i = -1;
	res = 987654321.0;
	while (s->enemys[++i])
	{
		if ((tmp = enemy_bullet_clipping(s->enemys[i], stat)) / t < res)
		{
			p = real_coord(stat->pos, tmp, mo, stat);
			if (p.z < s->enemys[i]->stat.sector->h_floor
			+ s->enemys[i]->stat.height)
			{
				res = tmp;
				s->ehit = s->enemys[i];
			}
		}
	}
	s->edist = res;
}

void		wall_real_hit(t_shoot *shoot, t_stat *stat, t_fvct3 mo)
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
	while (shoot->walls[++i])
	{
		if ((tmp = wall_bullet_clipping(*shoot->walls[i]->pillar,
		*shoot->walls[i]->next, stat)) / toto < res)
		{
			res = tmp;
			shoot->whit = shoot->walls[i];
		}
	}
	shoot->wdist = res;
	enemy_real_hit(shoot, stat, toto, mo);
}
