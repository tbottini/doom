/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 11:46:33 by akrache           #+#    #+#             */
/*   Updated: 2019/07/25 18:59:01 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** returns the number of walls between stat's position and target
*/
int		is_visible(t_stat *stat, t_stat *target)
{
	(void)stat;
	(void)target;
	return (0);
}

void	ai_action(Uint32 timestamp, t_enemy *enemy, t_player *player, int t)
{
	double dist;

	update_enemy_rotation(enemy, player->stat.pos);
	dist = distance((t_fvct2){enemy->stat.pos.x, enemy->stat.pos.y}, (t_fvct2){player->stat.pos.x, player->stat.pos.y});
	if (t == 0 && dist <= 10.0 && enemy->rts < timestamp)
	{
			//shoot at player
			enemy->rts = timestamp + 1000;
	}
	else
		;//move toward player
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
	int			t;
	int			i;

	tmp = sector->enemys;
	while (tmp)
	{
		if ((t = is_visible(&tmp->stat, &doom->game.player.stat)) <= 2)
			ai_action(doom->timestamp, tmp, &doom->game.player, t);
		tmp = tmp->next;
	}
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

void	update_enemy_rotation(t_enemy *enemy, t_fvct3 pos)
{
	enemy->stat.rot.y = atan2(pos.x - enemy->stat.pos.x, pos.y - enemy->stat.pos.y);
	enemy->e1.x = enemy->stat.pos.x + sin(enemy->stat.rot.y - 90.0) * enemy->stat.height / 4;
	enemy->e1.y = enemy->stat.pos.y + cos(enemy->stat.rot.y - 90.0) * enemy->stat.height / 4;
	enemy->e2.x = enemy->stat.pos.x + sin(enemy->stat.rot.y + 90.0) * enemy->stat.height / 4;
	enemy->e2.y = enemy->stat.pos.y + cos(enemy->stat.rot.y + 90.0) * enemy->stat.height / 4;
}

void	armandtificial_intelligence(t_doom *doom)
{
	int			index;
	t_sector	*passed[doom->game.len.nb_sects];

	index = 0;
	is_around(doom, doom->game.player.stat.sector, passed, &index);
}