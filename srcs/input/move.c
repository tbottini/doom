/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:13:17 by akrache           #+#    #+#             */
/*   Updated: 2019/06/13 10:14:15 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		crouch(t_player *player)
{
	if (!(player->crouch) && player->stat.speed == WALK)
	{
		player->crouch = 1;
		player->stat.speed = CROUCH;
		player->stat.height /= 2;
	}
}

void		crouch_release(t_player *player)
{
	if (player->crouch)
	{
		player->crouch = 0;
		player->stat.speed = WALK;
		player->stat.height *= 2;
	}
}

void		sprint(t_player *player)
{
	if (player->stat.speed == WALK)
		player->stat.speed = SPRINT;
}

void		sprint_release(t_player *player)
{
	player->stat.speed = WALK;
}

void		fall_damage(t_player *player, int f)
{
	if (player->stat.vel.z > 1000.0)
	{
		player->stat.health -= player->stat.vel.z / 100.0;
	}
	if (f)
	{
		player->stat.pos.z = player->stat.sector->h_floor;
		Mix_Resume(1);
	}
	else
		player->stat.pos.z = player->stat.sector->h_floor + player->stat.sector->h_ceil - player->stat.height;
	player->stat.vel.z = 0;
}

void		gravity(t_stat *stat)
{
	stat->vel.x += stat->sector->gravity.x;
	stat->vel.y += stat->sector->gravity.y;
	//tmp = player->stat.vel.z + player->stat.sector->gravity.z;
	//if (tmp >= player->stat.sector->h_floor && tmp <= player->stat.height + player->stat.sector->h_ceil + player->stat.sector->h_floor)
	//if (player->stat.pos.z <= player->stat.sector->h_floor)
	//	fall_damage(player, 1);
	//else if (player->stat.pos.z < player->stat.sector->h_floor + player->stat.sector->h_ceil - player->stat.height)
	//	fall_damage(player, 0);
	//else
		stat->vel.z += stat->sector->gravity.z * 450.0;
	//printf("gravity !\n");
	//player->stat.vel.z += player->stat.sector->gravity.z / 100;
	//else
	//	fall_damage(player);
}

void		update_rotation(t_player *player)
{
	// Update Rotation
	player->stat.rot.x += player->stat.rotvel.x;
	player->stat.rot.y += player->stat.rotvel.y;
	if (player->stat.rot.x < 0.0)
		player->stat.rot.x = 0.0;
	else if (player->stat.rot.x > 180.0)
		player->stat.rot.x = 180.0;
	if (player->stat.rot.y < 0.0)
		player->stat.rot.y += 360.0;
	else if (player->stat.rot.y > 360)
		player->stat.rot.y -= 360.0;
	// Update Position
	if (player->stat.sector->h_floor >= player->stat.pos.z || player->stat.pos.z >= player->stat.sector->h_floor + player->stat.sector->h_ceil - player->stat.height)
		inertie(player);
	else
		gravity(&player->stat);
}

void		update_position(t_doom *doom, t_fvct3 npos)
{
	t_fvct3	tmp;
	t_wall	*w;

	if (!(w = collision(doom, npos, NULL)))
	{
		doom->player.stat.pos.x = npos.x;
		doom->player.stat.pos.y = npos.y;
		return ;
	}
	tmp.x = doom->player.stat.pos.x;
	tmp.y = npos.y;
	if (!collision(doom, tmp, w))
	{
		doom->player.stat.pos.y = npos.y;
		return ;
	}
	tmp.y = doom->player.stat.pos.y;
	tmp.x = npos.x;
	if (!collision(doom, tmp, w))
		doom->player.stat.pos.x = npos.x;
}

void		move(t_doom *doom, t_player *player)
{
	t_fvct2	d;
	t_fvct3	npos;

	update_rotation(player);
	d.x = sin(player->stat.rot.y * PI180) / 10.0;
	d.y = cos(player->stat.rot.y * PI180) / 10.0;
	npos.x = player->stat.pos.x + d.x * player->stat.vel.y / 35000.0 + d.y * player->stat.vel.x / 35000.0;
	npos.y = player->stat.pos.y - d.x * -player->stat.vel.x / 35000.0 - d.y * player->stat.vel.y / 35000.0;
	npos.z = player->stat.pos.z + player->stat.vel.z / 35000.0;
	//printf("%f\t%f\t%f\n", npos.x, npos.y, npos.z);
	if (npos.z < player->stat.sector->h_floor)
		fall_damage(player, 1);
	else if (npos.z > player->stat.height + player->stat.sector->h_ceil + player->stat.sector->h_floor)
		fall_damage(player, 0);
	else
		player->stat.pos.z = npos.z;
	update_position(doom, npos);
}

void		inertie(t_player *player)
{
	if (player->stat.vel.x > DECELERATION)
		player->stat.vel.x -= DECELERATION;
	else if (player->stat.vel.x < -DECELERATION)
		player->stat.vel.x += DECELERATION;
	else
		player->stat.vel.x = 0;
	if (player->stat.vel.y > DECELERATION)
		player->stat.vel.y -= DECELERATION;
	else if (player->stat.vel.y < -DECELERATION)
		player->stat.vel.y += DECELERATION;
	else
		player->stat.vel.y = 0;
	if (player->stat.vel.x < player->stat.speed - DECELERATION && player->stat.vel.y < player->stat.speed - DECELERATION  && Mix_Playing(1))
		Mix_FadeOutChannel(1, 0);
	//printf("inertie !\n");
	/*if (player->stat.vel.z > DECELERATION)
		player->stat.vel.z -= DECELERATION;
	else if (player->stat.vel.z < -DECELERATION)
		player->stat.vel.z += DECELERATION;
	else
	{
		player->stat.vel.z = 0;
		player->stat.pos.z = player->stat.sector->h_floor;
	}*/
}
