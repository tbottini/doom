/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:51:14 by akrache           #+#    #+#             */
/*   Updated: 2019/05/06 15:45:37 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		reload(t_weapon *weapon)
{
	int	r;

	r = clip_max - clip;
	(weapon.ammo - r < 0 ? r += weapon.ammo - r : 0);
	weapon.ammo -= r;
	weapon.clip = r;
}

void		shoot(t_doom *doom)
{
	if (doom->player.weapons[hand].clip == 0)
		reload(weapon);
	else
	{
		if (doom->player.hand == ROCKETLAUNCHER)
			send_bullet(player.pos, /*RocketTexture*/);
		else
			send_bullet(player.pos, 0);
		clip--;
	}
}

void		kick(t_player *player, t_sector *sector)
{
	if (is_in_range(player, sector) && is_ennemy(sector))
		sector->health -= player->dmg;
}

void		send_bullet(t_fvct2 pos, t_texture *tex);
