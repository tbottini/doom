/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:52:40 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 08:10:24 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	cac_init(t_enemy *enemy, double difficulty)
{
	enemy->stat.speed = 37700.0;
	enemy->stat.height = 1.6;
	enemy->stat.health = 50 * difficulty;
	enemy->dmg = 1 * difficulty;
}

static void	egun_init(t_enemy *enemy, double difficulty)
{
	enemy->stat.speed = 32700.0;
	enemy->stat.height = 1.8;
	enemy->stat.health = 75 * difficulty;
	enemy->dmg = 1 * difficulty;
}

static void	fat_init(t_enemy *enemy, double difficulty)
{
	enemy->stat.speed = 18350.0;
	enemy->stat.height = 2.0;
	enemy->stat.health = 125 * difficulty;
	enemy->dmg = 1 * difficulty;
}

static void	boss_init(t_enemy *enemy, double difficulty)
{
	enemy->stat.speed = 15350.0;
	enemy->stat.height = 3.0;
	enemy->stat.health = 750 * difficulty;
	enemy->dmg = 1 * difficulty;
}

t_enemy		*enemy_init(int type, int difficulty, t_sector *sector)
{
	t_enemy *enemy;

	if (!(enemy = (t_enemy *)malloc(sizeof(t_enemy))))
		return (NULL);
	enemy->state = -1;
	enemy->rts = 0;
	enemy->next = NULL;
	enemy->prev = NULL;
	enemy->stat.sector = sector;
	enemy->type = type;
	enemy->sprites.pixels = NULL;
	if (type == 1)
		cac_init(enemy, difficulty);
	else if (type == 2)
		egun_init(enemy, difficulty);
	else if (type == 3)
		fat_init(enemy, difficulty);
	else if (type == 4)
		boss_init(enemy, difficulty);
	return (enemy);
}
