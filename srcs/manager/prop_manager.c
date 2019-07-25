/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:35:37 by akrache           #+#    #+#             */
/*   Updated: 2019/07/25 10:57:22 by akrache          ###   ########.fr       */
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

static void	supersmol(t_player *player)
{
	if (!player->power)
	{
		if (player->stat.height == H_NORMAL)
			player->stat.height = H_SMOL;
		player->boost = SDL_GetTicks() + 30000;
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

/*============cassette=================*/

static void	new_music(t_sound *sound)
{
	if (sound->maxmusic + 1 < TOTALMUSIC)
		sound->maxmusic++;
}

/*============bouton=================*/

void	end_level(t_doom *doom)
{
	game_over(doom, true);
}

void	open_close(t_prop *prop)
{
	if (prop->wall)
	{
		if (prop->wall->status == OPEN_DOOR)
		{
			prop->wall->status = CLOSE_DOOR;//close_door(wall);//a faire avec animation
		}
		else if (prop->wall->status == CLOSE_DOOR)
		{
			prop->wall->status = OPEN_DOOR;//open_door(wall);//a faire avaec animation
		}
		//prop->wall->ots = timestamp;
		prop->wall->percent = fabs(prop->wall->percent - 100.0);
	}
	if (prop->sector)
	{
		if (prop->sector->gravity.z == G_EARTH)
			prop->sector->gravity.z = G_MOON;
		else
			prop->sector->gravity.z = G_EARTH;
	}
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
	else if (type == MINPROPSPOS + 5)//supersmol pill
		prop->func = &supersmol;
	else if (type == MINPROPSPOS + 6)//Add jetpack
		prop->func = &jetpack;
	else if (type == MINPROPSPOS + 7 || type == MINPROPSPOS + 8 || type == MINPROPSPOS + 9)//Add new weapons
		prop->func = &add_weapon;
	else if (type == MINPROPSPOS + 10)// Deco sector
		prop->func = NULL;
	else if (type == MINWPROPSPOS) // Wall button
	{
		ft_printf("New Button\n");
		prop->func = &open_close;
	}
	else if (type == MINWPROPSPOS + 1) // End button
		prop->func = &end_level;
	else if (type == MINWPROPSPOS + 2) // wall deco
		prop->func = NULL;
	printf("New PROP %d\t\t%d\t\t pos z = %f\n", type, MINWPROPSPOS, prop->pos.z);
}

void		init_prop(t_prop *prop, double height)
{
	if (prop->type == MINWPROPSPOS + 2)
		prop->pos.z = -1;
	else if (ISWALLPROP(prop->type))
		prop->pos.z = height + (H_NORMAL / 2);
	else
		prop->pos.z = prop->sector->h_floor;
	prop->hitbox.x = prop->pos.x - HITBOXSIZE;
	prop->hitbox.y = prop->pos.y - HITBOXSIZE;
	prop->hitbox.z = prop->pos.z - HITBOXSIZE;
	prop->hitbox.w = prop->pos.x + HITBOXSIZE;
	prop->hitbox.l = prop->pos.y + HITBOXSIZE;
	prop->hitbox.h = prop->pos.z + HITBOXSIZE;
	//prop->width = 3;
	func_prop(prop, prop->type);
	//txtr_prop(prop, prop->type);
}

void		activate_prop(t_doom *doom, t_prop *prop, t_wall *wall)
{
	if (prop->type == MINPROPSPOS || prop->type == MINPROPSPOS + 6)//HEAL & jetpack
		prop->func(&doom->game.player.stat);
	else if (prop->type == MINPROPSPOS + 1)//Cassette
		prop->func(&doom->game.sound);
	else if (prop->type == MINPROPSPOS + 2)//Munitions
		prop->func(&doom->game.player.hand);
	else if (prop->type == MINPROPSPOS + 3 || prop->type == MINPROPSPOS + 4
		|| prop->type == MINPROPSPOS + 5)//Pills
		prop->func(&doom->game.player);
	else if (prop->type == MINPROPSPOS + 7)//Add gun
		prop->func(&doom->game.player.weapons[1]);
	else if (prop->type == MINPROPSPOS + 8)//Add shotgun
		prop->func(&doom->game.player.weapons[2]);
	else if (prop->type == MINPROPSPOS + 9)//Add rifle
		prop->func(&doom->game.player.weapons[3]);
	else if (prop->type == MINWPROPSPOS) // Wall button
		prop->func(prop);
	else if (prop->type == MINWPROPSPOS + 1) // End button
		prop->func(doom);
}

void		pickup_prop(t_doom *doom)
{
	int i;

	i = 0;
	while (i < doom->game.player.stat.sector->len_prop)
	{
		if (is_in_hitbox(&doom->game.player.stat.sector->props[i].hitbox, doom->game.player.stat.pos, 0))
		{
			activate_prop(doom, &doom->game.player.stat.sector->props[i], NULL);
			if (doom->game.player.stat.sector->props[i].type < MAXPROPSNUMBER)
				doom->game.player.stat.sector->props[i].tex = NULL;
			break ;
		}
		i++;
	}
}
