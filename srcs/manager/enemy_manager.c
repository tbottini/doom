/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:52:40 by akrache           #+#    #+#             */
/*   Updated: 2019/06/27 16:06:30 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/* Types
** 1 = CAC
** 2 = GUN
** 3 = FAT
** 4 = BOSS
*/

int			cac_init(t_enemy *enemy)
{
	enemy->stat.speed = 37700.0;
	enemy->stat.height = 1.4;
	enemy->stat.health = 50;
	enemy->sprites = NULL;
	return (1);
}

int			gun_init(t_enemy *enemy)
{
	enemy->stat.speed = 32700.0;
	enemy->stat.height = 1.8;
	enemy->stat.health = 75;
	enemy->sprites = NULL;
	return (1);
}

int			fat_init(t_enemy *enemy)
{
	enemy->stat.speed = 18350.0;
	enemy->stat.height = 2.0;
	enemy->stat.health = 125;
	enemy->sprites = NULL;
	return (1);
}

int			boss_init(t_enemy *enemy)
{
	enemy->stat.speed = 16350.0;
	enemy->stat.height = 4.0;
	enemy->stat.health = 500;
	enemy->sprites = NULL;
	return (1);
}

int			enemy_init(t_enemy *enemy, int type)
{
	enemy->state = 0;
	enemy->dist = NULL;
	if (type == 1)
		return (cac_init(enemy));
	else if (type == 2)
		return (gun_init(enemy));
	else if (type == 3)
		return (auto_init(enemy))
	else if (type == 4)
		return (boss_init(enemy));
	return (NULL);
}
