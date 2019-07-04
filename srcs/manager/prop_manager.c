/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:35:37 by akrache           #+#    #+#             */
/*   Updated: 2019/07/04 17:44:37 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*============jetpack=================*/

static void	jetpack(t_stat *stat)
{
	stat->jetpack = 1;
}

/*============weapon=================*/

static void	add_weapon(t_weapon *weapon)
{
	if (!weapon->on)
		weapon->on = true;
}

/*============super pill=================*/

static void	superpunch(t_player *player)
{
	if (!player->boost)
	{
		player->weapons[0].dmg = 100;
		player->boost = SDL_GetTicks() + 15000;
	}
}

static void	superhot(t_player *player)
{
	if (!player->boost)
		player->boost = SDL_GetTicks() + 5000;
}

/*============cassette=================*/

static void	new_music(t_sound *sound)
{
	if (sound->maxmusic + 1 < TOTALMUSIC)
		sound->maxmusic++;
}

/*============bouton=================*/

static void	open_close(t_wall *wall)
{
	if (wall->status == OPEN_DOOR)
		close_door(wall);//a faire avec animation
	else if (wall->status == CLOSE_DOOR)
		open_door(wall);//a faire avaec animation
}

/*===============ammo===================*/

static void	add_ammo(t_weapon *weapon)
{
	if (weapon->id == 1)
		weapon->ammo += 15;
	if (weapon->id == 2)
		weapon->ammo += 6;
	if (weapon->id == 3)
		weapon->ammo += 32;
}

/*=============Health====================*/
static void	heal(t_stat *stat)
{
	stat->health = stat->health + 25 <= 100
		? stat->health + 25 : 100;
}

void		func_prop(t_prop *prop, int type)
{
	if (type == MINPROPSPOS)//HEAL
		prop->func = &heal;
	else if (type == MINPROPSPOS + 1)//Cassette
		prop->func = &new_music;
	else if (type == MINPROPSPOS + 2)//Munitions
		prop->func = &add_ammo;
	else if (type == MINPROPSPOS + 3)//Superhot pill
		prop->func = &superhot;
	else if (type == MINPROPSPOS + 4)//superpunch pill
		prop->func = &superpunch;
	else if (type == MINPROPSPOS + 5)//Add new weapon
		prop->func = &add_weapon;
	else if (type == MINPROPSPOS + 6)// Deco sector
		prop->func = NULL;
	else if (type == MINWPROPSPOS) // Wall button
		prop->func = &open_close;
	else if (type == MINWPROPSPOS + 1) // wall deco
		prop->func = NULL;
}

////////////////////////////////
t_prop		prop_init(int type, t_wall *door)
{
	t_prop prop;

	//if (!(prop = (t_prop *)malloc(sizeof(t_prop))))
	//	return (0);
	prop.door = door;
	prop.type = type;
	func_prop(&prop, type);
	return (prop);
}