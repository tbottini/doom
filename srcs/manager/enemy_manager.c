/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:52:40 by akrache           #+#    #+#             */
/*   Updated: 2019/07/09 21:41:34 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/* Types
** 1 = CAC
** 2 = GUN
** 3 = FAT
** 4 = BOSS
*/

static void	cac_init(t_enemy *enemy)
{
	enemy->stat.speed = 37700.0;
	enemy->stat.height = 1.4;
	enemy->stat.health = 50;
	enemy->sprites = NULL;//
}

static void	egun_init(t_enemy *enemy)
{

	enemy->stat.speed = 32700.0;
	enemy->stat.height = 1.8;
	enemy->stat.health = 75;
	enemy->sprites = NULL;//
}

static void	fat_init(t_enemy *enemy)
{
	enemy->stat.speed = 18350.0;
	enemy->stat.height = 2.0;
	enemy->stat.health = 125;
	enemy->sprites = NULL;//
}

static void	boss_init(t_enemy *enemy)
{

	enemy->stat.speed = 16350.0;
	enemy->stat.height = 4.0;
	enemy->stat.health = 500;
	enemy->sprites = NULL;//
}

void	enemy_free(t_enemy *enemy)
{
	//sprites_free(sprites);
	if (enemy->next)
		enemy_free(enemy->next);
	free(enemy);
}

t_enemy	*enemy_init(int type)
{
	t_enemy *enemy;

	if (!(enemy = (t_enemy *)malloc(sizeof(t_enemy))))
		return (NULL);
	enemy->state = 0;
	enemy->dist = 0;
	enemy->next = NULL;
	if (type == 1)
		cac_init(enemy);
	else if (type == 2)
		egun_init(enemy);
	else if (type == 3)
		fat_init(enemy);
	else if (type == 4)
		boss_init(enemy);
	/*
		e1.x = sin((stat->rot.y - 90.0) * PI180) * (tmp->stat.width / 2);
		e1.y = cos((stat->rot.y - 90.0) * PI180) * (tmp->stat.width / 2);
		e2.x = sin((stat->rot.y + 90.0) * PI180) * (tmp->stat.width / 2);
		e2.y = cos((stat->rot.y + 90.0) * PI180) * (tmp->stat.width / 2);
	*/
	return (enemy);
}

//////////////////////////////////////////////////////

t_enemy		*pushfront_enemy(t_sector *sector, t_enemy *enemy)
{
	t_enemy *tmp;

	if (!(sector)|| !(enemy))
		return (NULL);
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
		enemy_free(tmp);
	}
}
