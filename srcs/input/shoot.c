/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:51:14 by akrache           #+#    #+#             */
/*   Updated: 2019/05/19 17:20:07 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		send_bullet(t_fvct3 pos, t_texture *tex)
{
	(void)pos;
	(void)tex;
}

void		reload(t_weapon *weapon)
{
	int	r;

	r = weapon->clip_max - weapon->clip;
	(weapon->ammo - r < 0 ? r += weapon->ammo - r : 0);
	weapon->ammo -= r;
	weapon->clip = r;
}

void		shoot(t_player *player)
{
	if (player->weapons[player->hand].clip == 0)
		reload(&(player->weapons[player->hand]));
	else
	{
		if (player->hand == 4)//ROCKETLAUNCHER)
			;//send_bullet(player->pos, /*RocketTexture*/);
		else
			send_bullet(player->pos, 0);
		player->weapons[player->hand].clip--;
	}
}

void		kick(t_player *player, t_sector *sector)
{
(void)player;
(void)sector;
	//if (is_in_range(player-> sector) && is_ennemy(sector))
	//	sector->health -= player->>dmg;
}
