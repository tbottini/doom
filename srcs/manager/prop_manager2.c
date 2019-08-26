/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop_manager2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:35:37 by akrache           #+#    #+#             */
/*   Updated: 2019/08/26 14:33:20 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** ============bouton=================
*/

void		end_level(t_doom *doom)
{
	game_over(doom, true);
}

void		open_close(t_prop *prop)
{
	if (prop->wall)
	{
		if (prop->wall->status == OPEN_DOOR)
			prop->wall->status = CLOSE_DOOR;
		else if (prop->wall->status == CLOSE_DOOR)
			prop->wall->status = OPEN_DOOR;
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

static void	activate_prop(t_doom *doom, t_prop *prop)
{
	if (prop->type == MINPROPSPOS)
		prop->func(&doom->game.player.stat);
	else if (prop->type == MINPROPSPOS + 1)
		prop->func(&doom->game.sound);
	else if (prop->type == MINPROPSPOS + 2)
		prop->func(doom->game.player.hand);
	else if (prop->type == MINPROPSPOS + 3 || prop->type == MINPROPSPOS + 4
		|| prop->type == MINPROPSPOS + 5)
		prop->func(&doom->game.player);
	if (prop->type == MINPROPSPOS + 6 || prop->type == MINPROPSPOS + 10
		|| prop->type == MINPROPSPOS + 11 || prop->type == MINPROPSPOS + 12
		|| prop->type == MINPROPSPOS + 13)
		prop->func(&doom->game.player.inv);
	else if (prop->type == MINPROPSPOS + 7)
		prop->func(&doom->game.player.weapons[1]);
	else if (prop->type == MINPROPSPOS + 8)
		prop->func(&doom->game.player.weapons[2]);
	else if (prop->type == MINPROPSPOS + 9)
		prop->func(&doom->game.player.weapons[3]);
	else if (prop->type == MINWPROPSPOS)
		prop->func(prop);
	else if (prop->type == MINWPROPSPOS + 1)
		prop->func(doom);
}

void		pickup_prop(t_doom *doom)
{
	int i;

	i = 0;
	while (i < doom->game.player.stat.sector->len_prop)
	{
		if (in_hitbox(&doom->game.player.stat.sector->props[i].hitbox,
			doom->game.player.stat.pos, 0))
		{
			activate_prop(doom, &doom->game.player.stat.sector->props[i]);
			doom->game.player.stat.sector->props[i].hitbox.h = -10000;
			break ;
		}
		i++;
	}
	check_boost(doom->timestamp, &doom->game.player);
}

void		init_prop(t_prop *prop, double height)
{
	if (ISWALLPROP(prop->type))
		prop->pos.z = height + (H_NORMAL / 2);
	else if (prop->sector)
		prop->pos.z = prop->sector->h_floor;
	prop->hitbox.x = prop->pos.x - HITBOXSIZE;
	prop->hitbox.y = prop->pos.y - HITBOXSIZE;
	prop->hitbox.z = prop->pos.z - HITBOXSIZE;
	prop->hitbox.w = prop->pos.x + HITBOXSIZE;
	prop->hitbox.l = prop->pos.y + HITBOXSIZE;
	prop->hitbox.h = prop->pos.z + HITBOXSIZE;
	func_prop(prop, prop->type);
}
