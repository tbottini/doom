/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:13:17 by akrache           #+#    #+#             */
/*   Updated: 2019/05/08 19:12:41 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		crouch(t_doom *doom)
{

	if (!(doom->player.crouch))
	{
		doom->player.crouch = 1;
		doom->player.speed >>= 1;
		doom->player.height >>= 1;
	}
}

void		crouch_release(t_doom *doom)
{
	doom->player.crouch = 0;
	doom->player.speed >>= 1;
	doom->player.height >>= 1;
}

void		sprint(t_doom *doom)
{
	if (doom->player.speed < MAX_SPEED)
		doom->player.speed += 0.2;
}

void		sprint_release(t_doom *doom)
{
	doom->player.speed = 10;
}

void		move(t_doom *doom, int x, int y)
{
	t_fvct2 d;
	t_fvct2 npos;

	// Update Rotation
	doom->player.rot.y += 5.0;
	if (doom->player.rot.y < 0.0)
		doom->player.rot.y += 360.0;
	else if (doom->player.rot.y > 360)
		doom->player.rot.y -= 360.0;
	// Update Position
	d.x = sin(doom->player.rot.y * PI180) / 10.0;
	d.y = cos(doom->player.rot.y * PI180) / 10.0;
	npos.x = doom->player.pos.x + d.x * -y / 35000.0 + d.y * 1 * -x / 35000.0;
	npos.y = doom->player.pos.y + d.x * -x / 35000.0 + d.y * y / 35000.0;
	// Check new pos
	doom->player.pos = npos;
}
