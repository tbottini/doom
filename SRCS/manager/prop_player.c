/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 18:20:44 by magrab            #+#    #+#             */
/*   Updated: 2019/08/18 18:20:44 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** ============jetpack=================
*/

void	jetpack(t_inv *inv)
{
	if (inv->jetpack == -1)
		inv->jetpack = 1;
}

/*
** ============weapon=================
*/

void	add_weapon(t_weapon *weapon)
{
	if (!weapon->on)
		weapon->on = true;
	else
		weapon->ammo += weapon->clip_max;
}

/*
** ============cassette=================
*/

void	new_music(t_sound *sound)
{
	if (sound->maxmusic + 1 < TOTALMUSIC)
		sound->maxmusic++;
}

/*
** ===============ammo===================
*/

void	add_ammo(t_weapon *weapon)
{
	if (weapon->id == 1)
		weapon->ammo += 15;
	if (weapon->id == 2)
		weapon->ammo += 6;
	if (weapon->id == 3)
		weapon->ammo += 32;
}

/*
** =============Health====================
*/

void	heal(t_stat *stat)
{
	stat->health = stat->health + 25 <= 100
		? stat->health + 25 : 100;
}
