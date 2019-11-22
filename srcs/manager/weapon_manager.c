/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:51:35 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 08:14:02 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_weapon	hand_init(void)
{
	t_weapon	weapon;

	weapon.id = FIST;
	weapon.clip_max = 0;
	weapon.clip = 0;
	weapon.ammo = 0;
	weapon.rate = 0;
	weapon.nb_tr = 0;
	weapon.nb_ts = 3;
	weapon.dmg = 10;
	weapon.on = true;
	return (weapon);
}

t_weapon	gun_init(void)
{
	t_weapon	weapon;

	weapon.id = GUN;
	weapon.clip_max = 16;
	weapon.clip = 16;
	weapon.ammo = 48;
	weapon.rate = 0;
	weapon.dmg = 20;
	weapon.nb_tr = 0;
	weapon.nb_ts = 7;
	weapon.on = false;
	return (weapon);
}

t_weapon	shotgun_init(void)
{
	t_weapon	weapon;

	weapon.id = SHOTGUN;
	weapon.clip_max = 6;
	weapon.clip = 6;
	weapon.ammo = 18;
	weapon.rate = 0;
	weapon.dmg = 45;
	weapon.nb_tr = 12;
	weapon.nb_ts = 4;
	weapon.on = false;
	return (weapon);
}

t_weapon	rifle_init(void)
{
	t_weapon	weapon;

	weapon.id = RIFLE;
	weapon.clip_max = 32;
	weapon.clip = 32;
	weapon.ammo = 96;
	weapon.rate = 1;
	weapon.dmg = 15;
	weapon.nb_tr = 17;
	weapon.nb_ts = 4;
	weapon.on = false;
	return (weapon);
}
