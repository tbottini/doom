/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:52:40 by akrache           #+#    #+#             */
/*   Updated: 2019/06/29 17:13:41 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/* Types
** 1 = CAC
** 2 = GUN
** 3 = FAT
** 4 = BOSS
*/

t_enemy	*cac_init(t_enemy *enemy)
{
	enemy->stat.speed = 37700.0;
	enemy->stat.height = 1.4;
	enemy->stat.health = 50;
	enemy->sprites = NULL;//
	return (enemy);
}

t_enemy	*egun_init(t_enemy *enemy)
{

	enemy->stat.speed = 32700.0;
	enemy->stat.height = 1.8;
	enemy->stat.health = 75;
	enemy->sprites = NULL;//
	return (enemy);
}

t_enemy	*fat_init(t_enemy *enemy)
{
	enemy->stat.speed = 18350.0;
	enemy->stat.height = 2.0;
	enemy->stat.health = 125;
	enemy->sprites = NULL;//
	return (enemy);
}

t_enemy	*boss_init(t_enemy *enemy)
{

	enemy->stat.speed = 16350.0;
	enemy->stat.height = 4.0;
	enemy->stat.health = 500;
	enemy->sprites = NULL;//
	return (enemy);
}

t_enemy	enemy_init(int type)
{
	t_enemy enemy;

	enemy.state = 0;
	enemy.dist = 0;
	if (type == 1)
		cac_init(&enemy);
	else if (type == 2)
		egun_init(&enemy);
	else if (type == 3)
		fat_init(&enemy);
	else if (type == 4)
		boss_init(&enemy);
	return (enemy);
}
