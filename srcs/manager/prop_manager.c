/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:35:37 by akrache           #+#    #+#             */
/*   Updated: 2019/07/03 16:27:57 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*============super pill=================*/

static void	superhot(t_player *player)
{
	player->boost = SDL_GetTicks() + 5000;
}

static void	superhotpill_init(t_prop *prop)
{
	prop->func = &superhot;
}

/*============deco wall=================*/

static void	deco_wall_init(t_prop *prop)
{
	prop->func = NULL;
}

/*============deco secteur=================*/

static void	deco_secteur_init(t_prop *prop)
{
	prop->func = NULL;
}

/*============cassette=================*/

static void	new_music(t_sound *sound)
{
	if (sound->maxmusic + 1 < TOTALMUSIC)
		sound->maxmusic++;
}

static void	casette_init(t_prop *prop)
{
	prop->func = &new_music;
}

/*============bouton=================*/

static void	open_close(t_wall *wall)
{
	if (wall->status == OPEN_DOOR)
		close_door(wall);//a faire avec animation
	else if (wall->status == CLOSE_DOOR)
		open_door(wall);//a faire avaec animation
}

static void	button_init(t_prop *prop)
{
	prop->func = &open_close;
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

static void	ammo_pack_init(t_prop *prop)
{
	prop->func = &add_ammo;
}
/*=============Health====================*/
static void	heal(t_stat *stat)
{
	stat->health = stat->health + 25 <= 100
		? stat->health + 25 : 100;
}

static void	health_pack_init(t_prop *prop)
{
	prop->func = &heal;
}

////////////////////////////////
t_prop		prop_init(int type)
{
	t_prop prop;

	//if (!(prop = (t_prop *)malloc(sizeof(t_prop))))
	//	return (0);
}