/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 11:46:33 by akrache           #+#    #+#             */
/*   Updated: 2019/07/27 20:38:58 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		update_enemy_rotation(t_enemy *enemy, t_fvct3 pos)
{
	enemy->stat.rot.y = atan2(pos.x - enemy->stat.pos.x, pos.y - enemy->stat.pos.y);
	enemy->e1.x = enemy->stat.pos.x + sin(enemy->stat.rot.y - (90.0 * PI180)) * enemy->stat.height / 4;
	enemy->e1.y = enemy->stat.pos.y + cos(enemy->stat.rot.y - (90.0 * PI180)) * enemy->stat.height / 4;
	enemy->e2.x = enemy->stat.pos.x + sin(enemy->stat.rot.y + (90.0 * PI180)) * enemy->stat.height / 4;
	enemy->e2.y = enemy->stat.pos.y + cos(enemy->stat.rot.y + (90.0 * PI180)) * enemy->stat.height / 4;
}

t_pillar	*closest_pillar(t_wall **walls, t_wall **hit, t_fvct3 pos, t_fvct3 target)
{
	(void)pos;
	(void)target;
	*hit = walls[0];//
	return (walls[0]->pillar);//a faire
}

/*
** returns the number of walls between stat's position and target
*/
int			is_visible(t_stat *stat, t_stat *target, t_wall **walls)//renvoyer tableau *t_wall[4] des murs touches
{
	int i;

	i = 0;
	(void)stat;
	(void)target;
	(void)walls;
	return (0); // a faire
}

void		ai_move(t_fvct2 pillar, t_wall *wall, t_enemy *enemy)
{
	(void)pillar;
	(void)wall;
	(void)enemy;
}

void		move_toward(t_enemy *enemy, t_player *player, t_wall **walls, int t)
{
	t_fvct3		npos;
	t_wall		*hit;
	t_pillar	*pill;
	int			tmp;

	npos.x = enemy->stat.pos.x + (sin(enemy->stat.rot.y) / 10.0) * (enemy->stat.speed / 35000.0);
	npos.y = enemy->stat.pos.y + (cos(enemy->stat.rot.y) / 10.0) * (enemy->stat.speed / 35000.0);
	//enemy->stat.pos.z = (npos.z <= enemy->stat.sector->h_floor) ? enemy->stat.sector->h_floor : npos.z; // update enemy z position
	if (!t)
	{
		if (enemy->stat.sector == player->stat.sector || (tmp = colli_teleport(&enemy->stat, enemy->stat.sector, npos, &hit)) == 1)
		{
			enemy->stat.pos.x = npos.x;
			enemy->stat.pos.y = npos.y;
		}
	}
	else
	{
		pill = closest_pillar(walls, &hit, enemy->stat.pos, player->stat.pos);
		ai_move(pill->p, hit, enemy);
	}
}

int			ai_action(Uint32 timestamp, t_enemy *enemy, t_player *player, int t)
{
	double dist;

	update_enemy_rotation(enemy, player->stat.pos);
	dist = distance((t_fvct2){enemy->stat.pos.x, enemy->stat.pos.y}, (t_fvct2){player->stat.pos.x, player->stat.pos.y});
	if (t == 0 && dist <= 10.0)
	{
		if (enemy->rts < timestamp)
		{
			player->stat.health -= enemy->dmg;
			enemy->rts = timestamp + 1000;
		}
		return (1);
	}
	return (0);
}

bool	is_passed(t_sector *sector, t_sector **passed, int index)
{
	int i;

	i = 0;
	while (i < index)
	{
		if (sector == passed[i])
			return (false);
		i++;
	}
	return (true);
}

int		is_around(t_doom *doom, t_sector *sector, t_sector **passed, int *index)
{
	t_enemy		*tmp;
	t_wall		*walls[3];
	double		nposz;
	int			t;
	int			i;

	tmp = sector->enemys;
	while (tmp)
	{
		if (tmp->stat.pos.z > tmp->stat.sector->h_floor && tmp->stat.sector->gravity.z < 0)
			tmp->stat.vel.z += tmp->stat.sector->gravity.z * 450.0;
		if ((nposz = tmp->stat.pos.z + tmp->stat.vel.z / 35000.0) <= tmp->stat.sector->h_floor)
		{
			tmp->stat.pos.z = tmp->stat.sector->h_floor;
			tmp->stat.vel.z = 0;
		}
		else
			tmp->stat.pos.z = nposz;
		if (doom->game.player.power != FREEZE && (t = is_visible(&tmp->stat, &doom->game.player.stat, walls)) <= 2)
		{
			if ((i = ai_action(doom->timestamp, tmp, &doom->game.player, t)) == 0)
				move_toward(tmp, &doom->game.player, walls, t);
		}
		tmp = tmp->next;
	}
	if (*index == doom->game.len.nb_sects - 1)
		return (0);
	passed[*index] = sector;
	(*index)++;
	i = 0;
	while (i < sector->len)
	{
		if (sector->wall[i].status >= OPEN_DOOR && sector->wall[i].link && !is_passed(sector->wall[i].link, passed, *index))
			is_around(doom, sector->wall[i].link, passed, index);
		i++;
	}
	return (0);
}

void	armandtificial_intelligence(t_doom *doom)
{
	int			index;
	t_sector	*passed[doom->game.len.nb_sects];

	index = 0;
	is_around(doom, doom->game.player.stat.sector, passed, &index);
}