/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:35:37 by akrache           #+#    #+#             */
/*   Updated: 2019/08/26 12:24:02 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** ============super pill=================
*/

static void	supersmol(t_player *player)
{
	if (!player->power && player->stat.height == H_NORMAL)
	{
		player->stat.height = H_SMOL;
		player->boost = SDL_GetTicks() + 25000;
		player->power = SMOL;
	}
}

static void	superpunch(t_player *player)
{
	if (!player->power)
	{
		player->weapons[0].dmg = 100;
		player->boost = SDL_GetTicks() + 15000;
		player->power = PUNCH;
	}
}

static void	superhot(t_player *player)
{
	if (!player->power)
	{
		player->boost = SDL_GetTicks() + 5000;
		player->power = FREEZE;
	}
}

void		func_prop(t_prop *prop, int type)
{
	if (type == MINPROPSPOS)
		prop->func = &heal;
	else if (type == MINPROPSPOS + 1)
		prop->func = &new_music;
	else if (type == MINPROPSPOS + 2)
		prop->func = &add_ammo;
	else if (type == MINPROPSPOS + 3 || type == MINPROPSPOS + 4)
		prop->func = type == MINPROPSPOS + 3 ? &superhot : &superpunch;
	else if (type == MINPROPSPOS + 5)
		prop->func = &supersmol;
	else if (type == MINPROPSPOS + 6)
		prop->func = &jetpack;
	else if (MINPROPSPOS + 7 <= type && type <= MINPROPSPOS + 9)
		prop->func = &add_weapon;
	else if (type == MINPROPSPOS + 10 || type == MINPROPSPOS + 11)
		prop->func = type == MINPROPSPOS + 10 ? &addkey1 : &addkey2;
	else if (type == MINPROPSPOS + 12 || type == MINPROPSPOS + 13)
		prop->func = type == MINPROPSPOS + 12 ? &addkey3 : &addlastkey;
	else if (type == MINPROPSPOS + 14 || type >= MINWPROPSPOS + 2)
		prop->func = NULL;
	else if (type == MINWPROPSPOS)
		prop->func = &open_close;
	else if (type == MINWPROPSPOS + 1)
		prop->func = &end_level;
}
