/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:13:17 by akrache           #+#    #+#             */
/*   Updated: 2019/08/12 20:50:40 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void		inertie(t_stat *stat)
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


static void		gravity(t_stat *stat)
{
	stat->vel.x += stat->sector->gravity.x;
	stat->vel.y += stat->sector->gravity.y;
	stat->vel.z += stat->sector->gravity.z * 450.0;
}

static void		update_rotation(t_stat *stat, t_inv *inv)
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
		|| !inv->jetpack)
		inertie(stat);
	else if (inv->jetpack)
		gravity(stat);
}

static void		update_position(t_stat *stat, t_fvct3 npos)
{
	t_fvct3	tmp;
	t_wall	*w;
	int		port;

	w = NULL;
	if ((port = colli_port(stat, stat->sector, npos, &w)) >= 1)
	{
		if (port == 2)
		{
			npos.x = npos.x + sin(stat->rot.y * PI180) * stat->vel.y / 35000.0 + cos(stat->rot.y * PI180) * stat->vel.x / 35000.0;
			npos.y = npos.y + sin(stat->rot.y * PI180) * stat->vel.x / 35000.0 - cos(stat->rot.y * PI180) * stat->vel.y / 35000.0;
		}
		stat->pos.x = npos.x;
		stat->pos.y = npos.y;
		return ;
	}
	else if (port == -1)
		return ;
	if (!(w = collision(stat->sector, npos, w)))
	{
		stat->pos.x = npos.x;
		stat->pos.y = npos.y;
		return ;
	}
	tmp.x = stat->pos.x;
	tmp.y = npos.y;
	if (!collision(stat->sector, tmp, w))
	{
		stat->pos.y = npos.y;
		return ;
	}
	tmp.y = stat->pos.y;
	tmp.x = npos.x;
	if (!collision(stat->sector, tmp, w))
		stat->pos.x = npos.x;
}

void		move(t_stat *stat, t_inv *inv)
{
	t_fvct2	d;
	t_fvct3	npos;

	update_rotation(stat, inv);
	d.x = sin(stat->rot.y * PI180) / 10.0;
	d.y = cos(stat->rot.y * PI180) / 10.0;
	npos.x = stat->pos.x + d.x * stat->vel.y / 35000.0 + d.y * stat->vel.x / 35000.0;
	npos.y = stat->pos.y + d.x * stat->vel.x / 35000.0 - d.y * stat->vel.y / 35000.0;
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
