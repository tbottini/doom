/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:35:37 by akrache           #+#    #+#             */
/*   Updated: 2019/07/20 18:26:26 by akrache          ###   ########.fr       */
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
	if (!player->boost)
	{
		if (player->stat.height == H_NORMAL)
			player->stat.height = H_SMOL;
		player->boost = SDL_GetTicks() + 30000;
	}
}

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

void	open_close(t_wall *wall)
{
	ft_printf("toto\n");
	if (wall->status == OPEN_DOOR)
		wall->status = CLOSE_DOOR;//close_door(wall);//a faire avec animation
	else if (wall->status == CLOSE_DOOR)
		wall->status = OPEN_DOOR;//open_door(wall);//a faire avaec animation
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
	else if (type == MINPROPSPOS + 5)//superpunch pill
		prop->func = &supersmol;
	else if (type == MINPROPSPOS + 6)//Add jetpack
		prop->func = &jetpack;
	else if (type == MINPROPSPOS + 7)// Deco sector
		prop->func = NULL;
	else if (type == MINPROPSPOS + 8 || type == MINPROPSPOS + 9 || type == MINPROPSPOS + 10)//Add new weapons
		prop->func = &add_weapon;
	else if (type == MINWPROPSPOS) // Wall button
	{
		ft_printf("New Button\n");
		prop->func = &open_close;
	}
	else if (type == MINWPROPSPOS + 1) // wall deco
		prop->func = NULL;
	ft_printf("New PROP %d\t\t%d\n", type, MINWPROPSPOS);
}

int			is_in_hitbox(t_hitbox *hitbox, t_fvct3 pos)
{
	if (hitbox->x <= pos.x && pos.x <= hitbox->w
		&& hitbox->y <= pos.y && pos.y <= hitbox->l
		&& hitbox->z <= pos.z && pos.z <= hitbox->h)
		return (1);
	return (0);
}

void		init_prop(t_prop *prop, double height)
{
	if (ISWALLPROP(prop->type))
		prop->pos.z = height + (H_NORMAL / 2);
	else
		prop->pos.z = prop->sector->h_floor;
	printf("PRROP Z = %f\n\n", prop->pos.z);
	prop->hitbox.x = prop->pos.x - HITBOXSIZE;
	prop->hitbox.y = prop->pos.y - HITBOXSIZE;
	prop->hitbox.z = prop->pos.z - HITBOXSIZE;
	printf("HITBOX Z = %f\n\n", prop->hitbox.z);
	prop->hitbox.w = prop->pos.x + HITBOXSIZE;
	prop->hitbox.l = prop->pos.y + HITBOXSIZE;
	prop->hitbox.h = prop->pos.z + HITBOXSIZE;
	prop->width = 3;
	func_prop(prop, prop->type);
	//txtr_prop(prop, prop->type);
}

void		activate_prop(t_game *game, t_prop *prop, t_wall *wall)
{
	if (prop->type == MINPROPSPOS || prop->type == MINPROPSPOS + 6)//HEAL & jetpack
		prop->func(&game->player.stat);
	else if (prop->type == MINPROPSPOS + 1)//Cassette
		prop->func(&game->sound);
	else if (prop->type == MINPROPSPOS + 2)//Munitions
		prop->func(&game->player.hand);
	else if (prop->type == MINPROPSPOS + 3 || prop->type == MINPROPSPOS + 4
		|| prop->type == MINPROPSPOS + 5)//Pills
		prop->func(&game->player);
	else if (prop->type == MINPROPSPOS + 8)//Add gun
		prop->func(&game->player.weapons[1]);
	else if (prop->type == MINPROPSPOS + 9)//Add shotgun
		prop->func(&game->player.weapons[2]);
	else if (prop->type == MINPROPSPOS + 10)//Add rifle
		prop->func(&game->player.weapons[3]);
	else if (prop->type == MINWPROPSPOS) // Wall button
		prop->func(wall);
}

void		pickup_prop(t_game *game)
{
	int i;

	i = 0;
	while (i < game->player.stat.sector->len_prop)
	{
		if (is_in_hitbox(&game->player.stat.sector->props[i].hitbox, game->player.stat.pos))
		{
			activate_prop(game, &game->player.stat.sector->props[i], NULL);
			if (game->player.stat.sector->props[i].type < MAXPROPSNUMBER)
				game->player.stat.sector->props[i].tex = NULL;
			break ;
		}
		i++;
	}
}
