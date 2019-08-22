/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 08:09:36 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 08:10:10 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		free_enemys(t_enemy *enemy)
{
	if (!(enemy))
		return ;
	if (enemy->next)
		free_enemys(enemy->next);
	free(enemy);
}

t_enemy		*pushfront_enemy(t_sector *sector, t_enemy *enemy)
{
	t_enemy *tmp;

	if (!(sector) || !(enemy))
		return (NULL);
	if (enemy->prev)
		enemy->prev->next = NULL;
	if (enemy->next)
		enemy->next->prev = NULL;
	if (sector->enemys)
	{
		tmp = sector->enemys;
		tmp->prev = enemy;
		enemy->next = tmp;
		enemy->prev = NULL;
		sector->enemys = enemy;
		return (enemy);
	}
	sector->enemys = enemy;
	enemy->next = NULL;
	enemy->prev = NULL;
	return (enemy);
}

void		del_enemy(t_sector *sector, t_enemy *enemy)
{
	t_enemy *tmp;
	t_enemy *prev;

	tmp = sector->enemys;
	prev = NULL;
	while (tmp && tmp != enemy)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp && tmp == enemy)
	{
		if (prev)
			prev->next = tmp->next;
		else if (tmp->next)
			sector->enemys = tmp->next;
		else
			sector->enemys = NULL;
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp);
	}
}
