/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 22:08:13 by magrab            #+#    #+#             */
/*   Updated: 2019/08/26 10:50:39 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	check_boost(Uint32 timestamp, t_player *player)
{
	if (timestamp > player->boost)
	{
		if (player->power == PUNCH)
			player->weapons[0].dmg = 10;
		else if (player->power == SMOL)
		{
			if (player->stat.sector->h_ceil <=
				player->stat.sector->h_floor + H_NORMAL)
				return ;
			else
				player->stat.height = H_NORMAL;
		}
		player->power = NONE;
	}
}

void	player_free(t_player *player)
{
	(void)player;
}

int		player_init(t_player *player)
{
	player->weapons[0] = hand_init();
	player->weapons[1] = gun_init();
	player->weapons[2] = shotgun_init();
	player->weapons[3] = rifle_init();
	player->hand = &player->weapons[0];
	player->stat.speed = WALK;
	player->stat.width = 0;
	player->boost = 0;
	player->inv.jetpack = -1;
	player->inv.key1 = false;
	player->inv.key2 = false;
	player->inv.key3 = false;
	player->inv.last_key = false;
	player->stat.height = H_NORMAL;
	player->stat.crouch = false;
	player->stat.rot.x = 90;
	player->stat.pos.z = player->stat.sector->h_floor;
	player->stat.rotvel.x = 0;
	player->stat.rotvel.y = 0;
	player->stat.vel.x = 0;
	player->stat.vel.y = 0;
	player->stat.vel.z = 0;
	player->power = NONE;
	return (1);
}
