/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:35:25 by akrache           #+#    #+#             */
/*   Updated: 2019/08/26 23:04:54 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int				in_hitbox(t_hitbox *hitbox, t_fvct3 pos, double hheight)
{
	if (hitbox->x <= pos.x && pos.x <= hitbox->w
		&& hitbox->y <= pos.y && pos.y <= hitbox->l
		&& hitbox->z <= (pos.z + hheight) && (pos.z + hheight) <= hitbox->h)
		return (1);
	return (0);
}

static bool		has_key(t_inv *inv, int key)
{
	if (key == 0)
		return (true);
	if (key == 1 && inv->key1 == true)
		return (true);
	if (key == 2 && inv->key2 == true)
		return (true);
	if (key == 3 && inv->key3 == true)
		return (true);
	return (false);
}

static void		action_button(t_doom *doom, t_wall *wallhit, t_inv *inv, int x)
{
	if (wallhit->props[x].type == MINWPROPSPOS)
	{
		if (wallhit->props[x].wall)
		{
			if (has_key(inv, wallhit->props[x].wall->level))
			{
				wallhit->props[x].func(&wallhit->props[x]);
				wallhit->props[x].wall->ots = doom->timestamp;
				Mix_PlayChannel(3, doom->game.sound.tab_effect[3], 0);
			}
			else
				Mix_PlayChannel(3, doom->game.sound.tab_effect[5], 0);
		}
		else
			wallhit->props[x].func(&wallhit->props[x]);
	}
	else if (wallhit->props[x].type == MINWPROPSPOS + 1
		&& inv->last_key == true)
		wallhit->props[x].func(doom);
	else if (!inv->last_key)
		Mix_PlayChannel(3, doom->game.sound.tab_effect[5], 0);
}

void			action(t_doom *doom, t_stat *s, t_inv *inv)
{
	int			x;
	t_fvct3		d;
	t_wall		*wallhit;

	d.x = s->pos.x + (RANGE * sin(s->rot.x * PI180) * cos(s->rot.y * PI180));
	d.y = s->pos.y + (RANGE * sin(s->rot.x * PI180) * sin(s->rot.y * PI180));
	d.z = s->pos.z + (-(RANGE * cos(s->rot.x * PI180)) + (s->height / 2));
	if (!(wallhit = colli_walls(s->sector, s->pos, d, NULL)))
		return ;
	x = -1;
	while (++x < wallhit->nb_props)
	{
		if (in_hitbox(&wallhit->props[x].hitbox, s->pos, s->height / 2))
		{
			action_button(doom, wallhit, inv, x);
			break ;
		}
	}
}

void			jump(t_stat *stat, t_inv *inv)
{
	if (inv->jetpack && stat->pos.z == stat->sector->h_floor)
	{
		stat->vel.z = (WALK * stat->height) / 2;
		Mix_Pause(1);
	}
	else if (!inv->jetpack)
	{
		if (stat->pos.z < stat->sector->h_ceil
			+ stat->sector->h_floor - stat->height - 0.1)
			stat->pos.z += 0.1;
		else if (stat->pos.z < stat->sector->h_ceil
			+ stat->sector->h_floor - stat->height)
			stat->pos.z = stat->sector->h_ceil
				+ stat->sector->h_ceil - stat->height;
	}
}
