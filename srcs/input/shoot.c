/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:51:14 by akrache           #+#    #+#             */
/*   Updated: 2019/05/05 21:35:08 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		crouch(t_doom *doom)
{

	if (!(tab->player->crouch))
	{
		tab->player->crouch = 1;
		tab->player->speed >>= 1
		tab->player->height >>= 1
	}
}

void		crouch_release(t_doom *doom)
{

	tab->player->crouch = 0;
	tab->player->speed >>= 1;
	tab->player->height >>= 1;
}

void		sprint(t_doom *doom)
{
	if (doom->player->speed < MAX_SPEED)
		doom->player->speed += 0.2;
}

void		action(t_doom *doom)
{
	;
}

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

void		send_bullet();