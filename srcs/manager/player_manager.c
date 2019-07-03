/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 22:08:13 by magrab            #+#    #+#             */
/*   Updated: 2019/07/02 15:19:57 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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
	player->hand = player->weapons[0];
	player->crouch = false;
	player->stat.speed = 32700.0;
	player->fov = 90;
	player->stat.health = 100;
	player->stat.width = 0;
	return (1);
}
