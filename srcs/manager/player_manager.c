/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 22:08:13 by magrab            #+#    #+#             */
/*   Updated: 2019/06/13 11:24:18 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	player_free(t_player *player)
{
	(void)player;
}

int		player_init(t_player *player)
{
	player->hand = 0;
	player->crouch = 0;
	player->stat.speed = 32700.0;
	//player->stat.pos.x = 1.0;
	//player->stat.pos.y = 1.0;
	//player->stat.rot.x = 90;
	//player->stat.rot.y = 90;
	player->fov = 90;
	player->stat.health = 100;
	player->stat.weight = 10;
	return (1);
}
