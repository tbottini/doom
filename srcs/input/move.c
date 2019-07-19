/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:13:17 by akrache           #+#    #+#             */
/*   Updated: 2019/07/19 14:30:44 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		jetpack_on_off(t_player *player)
{
	if (player->stat.jetpack == 1)
	{
		player->stat.jetpack = 0;
		player->stat.vel.x = 0;
		player->stat.vel.y = 0;
		player->stat.vel.z = 0;
	}
	else if (player->stat.jetpack == 0)
		player->stat.jetpack = 1;
}

void		fly(t_stat *stat)
{
	if (stat->pos.z < stat->sector->h_ceil + stat->sector->h_floor - stat->height - 0.1)
		stat->pos.z += 0.1;
	else if (stat->pos.z < stat->sector->h_ceil + stat->sector->h_floor - stat->height)
		stat->pos.z = stat->sector->h_ceil + stat->sector->h_ceil - stat->height;
}

void		unfly(t_stat *stat)
{
	if (stat->pos.z > stat->sector->h_floor + 0.1)
		stat->pos.z -= 0.1;
	else if (stat->pos.z > stat->sector->h_floor)
		stat->pos.z = stat->sector->h_floor;
}

void		crouch(t_player *player)
{
	if (!player->crouch && player->stat.speed == WALK)
	{
		player->crouch = true;
		player->stat.speed = CROUCH;
		player->stat.height /= 2;
	}
}

void		crouch_release(t_player *player)
{
	if (player->crouch && player->stat.jetpack)
	{
		player->crouch = false;
		player->stat.speed = WALK;
		player->stat.height *= 2;
	}
}

void		sprint(t_stat *stat)
{
	if (stat->speed == WALK)
		stat->speed = SPRINT;
}

void		sprint_release(t_stat *stat)
{
	stat->speed = WALK;
}

/*void		fall_damage(t_stat *stat)
{
	stat->pos.z = stat->sector->h_floor;
	Mix_Resume(1);
	//stat->vel.z = 0;
}*/

void		gravity(t_stat *stat)
{
	if (stat->jetpack)
	{
		stat->vel.x += stat->sector->gravity.x;
		stat->vel.y += stat->sector->gravity.y;
		//if (fabs((stat->sector->h_floor + stat->sector->h_ceil) - (stat->pos.z + stat->height)) == 0.0)
		//	stat->vel.z = 0;
		stat->vel.z += stat->sector->gravity.z * 450.0;
	}
}

void		update_rotation(t_stat *stat)
{
	// Update Rotation
	stat->rot.x += stat->rotvel.x;
	stat->rot.y += stat->rotvel.y;
	if (stat->rot.x < 0.0)
		stat->rot.x = 0.0;
	else if (stat->rot.x > 360.0)
		stat->rot.x = 360.0;
	if (stat->rot.y < 0.0)
		stat->rot.y += 360.0;
	else if (stat->rot.y > 360)
		stat->rot.y -= 360.0;
	// Update Position
	if (((stat->sector->h_floor >= stat->pos.z
		&& stat->sector->gravity.z < 0) || (stat->pos.z
		>= stat->sector->h_floor + stat->sector->h_ceil
		- stat->height && stat->sector->gravity.z > 0))
		|| !stat->jetpack)
		inertie(stat);
	else
		gravity(stat);
}

void		update_position(t_stat *stat, t_fvct3 npos)
{
	t_fvct3	tmp;
	t_wall	*w;

	if (!colli_teleport(stat, npos, stat->pos))
	{
		stat->pos.x = npos.x;
		stat->pos.y = npos.y;
		return ;
	}
	if (!(w = collision(stat, npos, NULL)))
	{
		stat->pos.x = npos.x;
		stat->pos.y = npos.y;
		return ;
	}
	tmp.x = stat->pos.x;
	tmp.y = npos.y;
	if (!collision(stat, tmp, w))
	{
		stat->pos.y = npos.y;
		return ;
	}
	tmp.y = stat->pos.y;
	tmp.x = npos.x;
	if (!collision(stat, tmp, w))
		stat->pos.x = npos.x;
}

void		move(t_stat *stat)
{
	t_fvct2	d;
	t_fvct3	npos;

	update_rotation(stat);
	d.x = sin(stat->rot.y * PI180) / 10.0;
	d.y = cos(stat->rot.y * PI180) / 10.0;
	npos.x = stat->pos.x + d.x * stat->vel.y / 35000.0 + d.y * stat->vel.x / 35000.0;
	npos.y = stat->pos.y - d.x * -stat->vel.x / 35000.0 - d.y * stat->vel.y / 35000.0;
	npos.z = stat->pos.z + stat->vel.z / 35000.0;
	if (npos.z < stat->sector->h_floor)
	{
		stat->pos.z = stat->sector->h_floor;
		Mix_Resume(1);
	}
	else if (npos.z > stat->sector->h_ceil - stat->height + stat->sector->h_floor)
	{
		stat->pos.z = stat->sector->h_ceil - stat->height + stat->sector->h_floor - 0.10;
		stat->vel.z = 0;
	}
	else
		stat->pos.z = npos.z;
	update_position(stat, npos);
}

void		inertie(t_stat *stat)
{
	if (stat->vel.x > DECELERATION)
		stat->vel.x -= DECELERATION;
	else if (stat->vel.x < -DECELERATION)
		stat->vel.x += DECELERATION;
	else
		stat->vel.x = 0;
	if (stat->vel.y > DECELERATION)
		stat->vel.y -= DECELERATION;
	else if (stat->vel.y < -DECELERATION)
		stat->vel.y += DECELERATION;
	else
		stat->vel.y = 0;
	if (stat->vel.x < stat->speed - DECELERATION && stat->vel.y < stat->speed - DECELERATION && Mix_Playing(1))
		Mix_FadeOutChannel(1, 0);
}
