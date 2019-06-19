/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:35:25 by akrache           #+#    #+#             */
/*   Updated: 2019/06/19 12:04:35 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		next_weapon(t_player *player)
{
	player->hand += (player->hand == WEAPON_MAX - 1) ? -player->hand : 1;
}

void		prev_weapon(t_player *player)
{
	player->hand -= player->hand == 0 ? (WEAPON_MAX + 1) : 1;
}

void		change_weapon(t_player *player, int new_w)
{
	if (new_w >= 0 && new_w < WEAPON_MAX)
		player->hand = new_w;
}

void		action(t_doom *doom)
{
	(void)doom;
	;//if (is_in_range(&(doom->player), (doom->sector)))
		//interact(sector);
}

void		jump(t_player *player)
{
	if (player->stat.pos.z == player->stat.sector->h_floor)
	{
		player->stat.vel.z = WALK;
		Mix_Pause(1);
	}
}

void		kick(t_doom *doom, t_player *player)
{
	t_fvct3	d;
	int		range;

	range = 1;
	d.x = range * sin(player->stat.rot.x * PI180) * cos(player->stat.rot.y * PI180);
	d.y = range * sin(player->stat.rot.x * PI180) * sin(player->stat.rot.y * PI180);
	d.z = -(range * cos(player->stat.rot.x * PI180)) + (player->stat.height / 2);
	Mix_PlayChannel(2, doom->sound.tab_effect[6], 0);
}
