/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 12:59:22 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 04:20:08 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	jetpack_on_off(t_player *player)
{
	if (player->inv.jetpack == 1)
	{
		player->inv.jetpack = 0;
		player->stat.vel.x = 0;
		player->stat.vel.y = 0;
		player->stat.vel.z = 0;
	}
	else if (player->inv.jetpack == 0)
		player->inv.jetpack = 1;
}

void	next_weapon(t_player *player)
{
	int i;

	i = player->hand->id + 1;
	while (i < NB_WEAPON)
	{
		if (player->weapons[i].on)
			break ;
		i++;
	}
	if (i == NB_WEAPON)
		player->hand = &player->weapons[0];
	else
		player->hand = &player->weapons[i];
}

void	prev_weapon(t_player *player)
{
	int i;

	i = (player->hand->id == FIST) ? NB_WEAPON - 1 : player->hand->id - 1;
	while (i > 0)
	{
		if (player->weapons[i].on)
			break ;
		i--;
	}
	player->hand = &player->weapons[i];
}

void	change_weapon(t_player *player, int id)
{
	if (id >= 0 && id < NB_WEAPON && player->weapons[id].on)
		player->hand = &player->weapons[id];
}

void	reload(Uint32 t, t_player *player, t_weapon *weapon, t_sound *sound)
{
	int	r;

	if (player->occupied < t)
	{
		r = weapon->clip_max - weapon->clip;
		if (weapon->ammo - r < 0)
			r = weapon->ammo;
		weapon->ammo -= r;
		weapon->clip += r;
		Mix_PlayChannel(2, sound->tab_effect[9], 0);
		player->act = true;
		player->timeact = t;
		player->occupied = t + (weapon->id == GUN ? 900 : 1500);
	}
}
