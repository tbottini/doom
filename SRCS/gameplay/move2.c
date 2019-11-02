/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 11:25:46 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 04:18:24 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		fly_down(t_stat *stat)
{
	if (stat->pos.z > stat->sector->h_floor + 0.1)
		stat->pos.z -= 0.1;
	else if (stat->pos.z > stat->sector->h_floor)
		stat->pos.z = stat->sector->h_floor;
}

void		crouch(t_player *player)
{
	if (!player->stat.crouch && player->stat.speed
	!= SPRINT && player->stat.height != H_SMOL)
	{
		player->stat.crouch = true;
		player->stat.speed = CROUCH;
		player->stat.height = H_CROUCH;
	}
}

void		crouch_release(t_player *player)
{
	if (player->stat.crouch && player->inv.jetpack)
	{
		player->stat.crouch = false;
		if (player->stat.sector->h_ceil
		<= player->stat.sector->h_floor + H_NORMAL)
			return ;
		player->stat.speed = WALK;
		player->stat.height = H_NORMAL;
	}
}

void		sprint(t_stat *stat)
{
	if (stat->speed == WALK && stat->height != H_CROUCH)
		stat->speed = SPRINT;
}

void		sprint_release(t_stat *stat)
{
	if (stat->speed == SPRINT)
		stat->speed = WALK;
}
