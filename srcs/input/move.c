/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:13:17 by akrache           #+#    #+#             */
/*   Updated: 2019/05/19 17:47:33 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		crouch(t_player *player)
{

	if (!(player->crouch))
	{
		player->crouch = 1;
		player->speed >>= 1;
		player->height >>= 1;
	}
}

void		crouch_release(t_player *player)
{
	player->crouch = 0;
	player->speed >>= 1;
	player->height >>= 1;
}

void		sprint(t_player *player)
{
	if (player->speed < MAX_SPEED)
		player->speed += 0.2;
}

void		sprint_release(t_player *player)
{
	player->speed = 10;
}

void		move(t_player *player, int x, int y)
{
	t_fvct2 d;
	t_fvct3 npos;

	// Update Rotation
	npos.z = player->pos.z;
	player->rot.y += player->rotvel.y;
	if (player->rot.y < 0.0)
		player->rot.y += 360.0;
	else if (player->rot.y > 360)
		player->rot.y -= 360.0;
	// Update Position
	d.x = sin(player->rot.y * PI180) / 10.0;
	d.y = cos(player->rot.y * PI180) / 10.0;
	npos.x = player->pos.x + d.x * y / 35000.0 + d.y * 1 * x / 35000.0;
	npos.y = player->pos.y + d.x * -x / 35000.0 + d.y * y / 35000.0;
	// Check new pos
	//DEPRECATED if (0 < npos.x && npos.x < doom->map_size.x && 0 < npos.y && npos.y < doom->map_size.y)
	//DEPRECATED	if (doom->map[(int)npos.y][(int)npos.x] != '#')
	player->pos = npos;
}
