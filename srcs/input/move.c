/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:13:17 by akrache           #+#    #+#             */
/*   Updated: 2019/06/03 19:53:06 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		crouch(t_player *player)
{

	if (!(player->crouch))
	{
		player->crouch = 1;
		player->speed = 16350;
		player->height /= 2;
	}
}

void		crouch_release(t_player *player)
{
	player->crouch = 0;
	player->speed = 32700.0;
	player->height *= 2;
}

void		sprint(t_player *player)
{
	player->speed = 49050.0;
}

void		sprint_release(t_player *player)
{
	player->speed = 32700.0;
}

void		fall_damage(t_player *player, int f)
{
	if (player->vel.z > 1000.0)
	{
		player->health -= player->vel.z / 100.0;
	}
	if (f)
		player->pos.z = player->sector->h_floor;
	else
		player->pos.z = player->sector->h_floor + player->sector->h_ceil - player->height;
	player->vel.z = 0;
}

void		gravity(t_player *player)
{
	player->vel.x += player->sector->gravity.x;
	player->vel.y += player->sector->gravity.y;
	//tmp = player->vel.z + player->sector->gravity.z;
	//if (tmp >= player->sector->h_floor && tmp <= player->height + player->sector->h_ceil + player->sector->h_floor)
	//if (player->pos.z <= player->sector->h_floor)
	//	fall_damage(player, 1);
	//else if (player->pos.z < player->sector->h_floor + player->sector->h_ceil - player->height)
	//	fall_damage(player, 0);
	//else
		player->vel.z += player->sector->gravity.z * 350.0;
	printf("gravity !\n");
	//player->vel.z += player->sector->gravity.z / 100;
	//else
	//	fall_damage(player);
}

void		update_rotation(t_player *player)
{
	// Update Rotation
	player->rot.x += player->rotvel.x;
	player->rot.y += player->rotvel.y;
	if (player->rot.x < 10.0)
		player->rot.x = 10.0;
	else if (player->rot.x > 170.0)
		player->rot.x = 170.0;
	if (player->rot.y < 0.0)
		player->rot.y += 360.0;
	else if (player->rot.y > 360)
		player->rot.y -= 360.0;
	if (player->sector->h_floor >= player->pos.z || player->pos.z >= player->sector->h_floor + player->sector->h_ceil - player->height)
		inertie(player);
	else
		gravity(player);
}

void		update_position(t_doom *doom, t_fvct3 npos)
{
	t_fvct3	tmp;
	t_wall	*w;

	if (!(w = collision(doom, npos, NULL)))
	{
		doom->player.pos.x = npos.x;
		doom->player.pos.y = npos.y;
		return ;
	}
	tmp.x = doom->player.pos.x;
	tmp.y = npos.y;
	if (!collision(doom, tmp, w))
	{
		doom->player.pos.y = npos.y;
		return ;
	}
	tmp.y = doom->player.pos.y;
	tmp.x = npos.x;
	if (!collision(doom, tmp, w))
		doom->player.pos.x = npos.x;
}

void		move(t_doom *doom, t_player *player)
{
	t_fvct2	d;
	t_fvct3	npos;

	update_rotation(player);
	d.x = sin(player->rot.y * PI180) / 10.0;
	d.y = cos(player->rot.y * PI180) / 10.0;
	npos.x = player->pos.x + d.x * player->vel.y / 35000.0 + d.y * player->vel.x / 35000.0;
	npos.y = player->pos.y - d.x * -player->vel.x / 35000.0 - d.y * player->vel.y / 35000.0;
	npos.z = player->pos.z + player->vel.z / 35000.0;
	printf("%f\t%f\t%f\n", npos.x, npos.y, npos.z);
	if (npos.z < player->sector->h_floor)
		fall_damage(player, 1);
	else if (npos.z > player->height + player->sector->h_ceil + player->sector->h_floor)
		fall_damage(player, 0);
	else
		player->pos.z = npos.z;
	update_position(doom, npos);
}

void		inertie(t_player *player)
{
	if (player->vel.x > DECELERATION)
		player->vel.x -= DECELERATION;
	else if (player->vel.x < -DECELERATION)
		player->vel.x += DECELERATION;
	else
		player->vel.x = 0;
	if (player->vel.y > DECELERATION)
		player->vel.y -= DECELERATION;
	else if (player->vel.y < -DECELERATION)
		player->vel.y += DECELERATION;
	else
		player->vel.y = 0;
	printf("inertie !\n");
	/*if (player->vel.z > DECELERATION)
		player->vel.z -= DECELERATION;
	else if (player->vel.z < -DECELERATION)
		player->vel.z += DECELERATION;
	else
	{
		player->vel.z = 0;
		player->pos.z = player->sector->h_floor;
	}*/
}