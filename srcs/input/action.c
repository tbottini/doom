/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:35:25 by akrache           #+#    #+#             */
/*   Updated: 2019/05/28 23:38:13 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		pause_game(t_doom *doom)
{
	doom->ui.m_status = 3;
}

void		next_weapon(t_player *player)
{
	player->hand = ++player->hand % player->nb_weapons;
}

void		prev_weapon(t_player *player)
{
	player->hand = --player->hand < 0 ? player->nb_weapons - 1 : --player->hand;
}

int			is_in_range(t_player *player, t_sector *sector)
{
	(void)player;
	(void)sector;
	return (0);
}

void		action(t_doom *doom)
{
	if (is_in_range(&(doom->player), (doom->sector)))
		;//interact(sector);
}

void		jump(t_player *player)
{
	if (player->pos.z == player->sector->h_floor)
		player->vel.z = 32700;
}