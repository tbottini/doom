/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 11:46:33 by akrache           #+#    #+#             */
/*   Updated: 2019/07/25 17:34:32 by akrache          ###   ########.fr       */
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

void	ai_action(t_enemy *enemy, int t)
{
	(void)enemy;
	(void)t;
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

int		is_around(t_sector *sector, t_stat *stat, t_sector **passed, int *index)
{
	t_enemy		*tmp;
	int			t;
	int			i;

	tmp = sector->enemys;
	while (tmp)
	{
		if ((t = is_visible(&tmp->stat, stat)) <= 3)
			ai_action(tmp, t);
		tmp = tmp->next;
	}
	passed[*index] = sector;
	(*index)++;
	i = 0;
	while (i < sector->len)
	{
		if (sector->wall[i].status >= OPEN_DOOR && sector->wall[i].link && !is_passed(sector->wall[i].link, passed, *index))
			is_around(sector->wall[i].link, stat, passed, index);
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

void	armandtificial_intelligence(t_game *game, t_sector *sector, t_player *player)
{
	int			index;
	t_sector	*passed[game->len.nb_sects];

	index = 0;
	is_around(sector, &player->stat, passed, &index);
}