/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:35:25 by akrache           #+#    #+#             */
/*   Updated: 2019/08/04 15:55:06 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define RANGE 2

int			is_in_hitbox(t_hitbox *hitbox, t_fvct3 pos, double hheight)
{
	if (hitbox->x <= pos.x && pos.x <= hitbox->w
		&& hitbox->y <= pos.y && pos.y <= hitbox->l
		&& hitbox->z <= (pos.z + hheight) && (pos.z + hheight) <= hitbox->h)
		return (1);
	return (0);
}

bool		has_key(t_inv *inv, int key)
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

void		action(t_doom *doom, t_stat *s, t_inv *inv)
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
		if (is_in_hitbox(&wallhit->props[x].hitbox, s->pos, s->height / 2))
		{
			if (wallhit->props[x].type == MINWPROPSPOS)
			{
				if (wallhit->props[x].wall)
				{
					if (has_key(inv, wallhit->props[x].wall->level))
						wallhit->props[x].func(&wallhit->props[x]);
					wallhit->props[x].wall->ots = doom->timestamp;
				}
				else
					wallhit->props[x].func(&wallhit->props[x]);
			}
			else if (wallhit->props[x].type == MINWPROPSPOS + 1 && inv->last_key == true)
				wallhit->props[x].func(doom);
			printf("POS : touched prop type = %d\n", wallhit->props[x].type);//clic sound
		}
	}
	
}

void		jump(t_stat *stat, t_inv *inv)
{
	if (inv->jetpack && stat->pos.z == stat->sector->h_floor)
	{
		stat->vel.z = (WALK * stat->height) / 2;
		Mix_Pause(1);
	}
	else if (!inv->jetpack)
	{
		if (stat->pos.z < stat->sector->h_ceil + stat->sector->h_floor - stat->height - 0.1)
			stat->pos.z += 0.1;
		else if (stat->pos.z < stat->sector->h_ceil + stat->sector->h_floor - stat->height)
			stat->pos.z = stat->sector->h_ceil + stat->sector->h_ceil - stat->height;
	}
}

static void	kick_button(t_stat *stat, t_fvct3 d, Uint32 timestamp)
{
	t_wall	*wallhit;
	int		x;

	if (!(wallhit = colli_walls(stat->sector, stat->pos, d, NULL)))
		return ;
	x = -1;
	while (++x < wallhit->nb_props)
	{
		if (is_in_hitbox(&wallhit->props[x].hitbox, stat->pos, stat->height / 2))
		{
			if (wallhit->props[x].type == MINWPROPSPOS)
			{
				wallhit->props[x].func(&wallhit->props[x]);
				if (wallhit->props[x].wall)
					wallhit->props[x].wall->ots = timestamp;
			}
			printf("POS : touched prop type = %d\n", wallhit->props[x].type);//clic sound
		}
	}
}

void		kick(Uint32 timestamp, t_sound *sound, t_player *pl)
{
	t_fvct3	d;
	t_enemy	*tmp;
	t_enemy	*tmp2;

	printf("SUPA KICKA\t\t");
	tmp = pl->stat.sector->enemys;
	d.x = pl->stat.pos.x + RANGE * sin(pl->stat.rot.x * PI180) * cos(pl->stat.rot.y * PI180);
	d.y = pl->stat.pos.y + RANGE * sin(pl->stat.rot.x * PI180) * sin(pl->stat.rot.y * PI180);
	d.z = pl->stat.pos.z + -(RANGE * cos(pl->stat.rot.x * PI180)) + (pl->stat.height / 2);
	while (tmp)
	{
		tmp2 = tmp->next;
		if (vector_intersect(d, pl->stat.pos, tmp->e1, tmp->e2))
		{
			injure_enemy(tmp, pl->weapons[0].dmg, d);
			Mix_PlayChannel(2, sound->tab_effect[6], 0);
			pl->occupied = timestamp + 1000; //ajuster avec vitesse d'animation
			return ;
		}
		tmp = tmp2;
	}
	printf("MISSED\n");
	kick_button(&pl->stat, d, timestamp);
	pl->occupied = timestamp + 1000; //ajuster avec vitesse d'animation
}
