/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 22:08:13 by magrab            #+#    #+#             */
/*   Updated: 2019/06/10 10:20:05 by akrache          ###   ########.fr       */
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
	player->nb_weapons = 1;
	player->speed = 32700.0;
	//player->pos.x = 1.0;
	//player->pos.y = 1.0;
	//player->rot.x = 90;
	//player->rot.y = 90;
	player->fov = 90;
	player->health = 100;
	player->weight = 10;
	player->crouch = 0;
	return (1);
}
