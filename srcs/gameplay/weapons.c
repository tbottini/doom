/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 12:59:22 by akrache           #+#    #+#             */
/*   Updated: 2019/07/30 13:00:02 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		next_weapon(t_player *player)
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

void		prev_weapon(t_player *player)
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

void		change_weapon(t_player *player, int id)
{
	if (id >= 0 && id < NB_WEAPON && player->weapons[id].on)
		player->hand = &player->weapons[id];
}

void		reload(Uint32 timestamp, t_player *player, t_weapon *weapon)
{
	int	r;

	if (player->occupied < timestamp)
	{
		r = weapon->clip_max - weapon->clip;
		if (weapon->ammo - r < 0)
			r = weapon->ammo;
		weapon->ammo -= r;
		weapon->clip += r;
		player->occupied = timestamp + 1000;//ajuster avec vitesse d'animation
	}
}
