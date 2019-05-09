/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:51:14 by akrache           #+#    #+#             */
/*   Updated: 2019/05/08 19:21:43 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		send_bullet(t_fvct2 pos, t_texture *tex)
{
	;
}

void		reload(t_weapon *weapon)
{
	int	r;

	r = weapon->clip_max - weapon->clip;
	(weapon->ammo - r < 0 ? r += weapon->ammo - r : 0);
	weapon->ammo -= r;
	weapon->clip = r;
}

void		shoot(t_doom *doom)
{
	if (doom->player.weapons[doom->player.hand].clip == 0)
		reload(&(doom->player.weapons[doom->player.hand]));
	else
	{
		if (doom->player.hand == 4)//ROCKETLAUNCHER)
			;//send_bullet(player.pos, /*RocketTexture*/);
		else
			send_bullet(doom->player.pos, 0);
		doom->player.weapons[doom->player.hand].clip--;
	}
}

void		kick(t_player *player, t_sector *sector)
{
	;//if (is_in_range(player, sector) && is_ennemy(sector))
	//	sector->health -= player->dmg;
}
