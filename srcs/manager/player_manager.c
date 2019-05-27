/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 22:08:13 by magrab            #+#    #+#             */
/*   Updated: 2019/05/27 22:09:00 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	player_free(t_player *player)
{
	(void)player;
}

int		player_init(t_player *player)
{
	player->pos.x = 1.0;
	player->pos.y = 1.0;
	player->rot.x = 90;
	player->rot.y = 90;
	player->fov = 90;
	player->health = 100;
	player->height = 180;
	player->weight = 10;
	return (1);
}
