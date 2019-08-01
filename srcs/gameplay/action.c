/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:35:25 by akrache           #+#    #+#             */
/*   Updated: 2019/08/01 15:54:50 by akrache          ###   ########.fr       */
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

void		action(t_doom *doom, t_stat *s)
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
				wallhit->props[x].func(&wallhit->props[x]);
				if (wallhit->props[x].wall)
					wallhit->props[x].wall->ots = doom->timestamp;
			}
			else if (wallhit->props[x].type == MINWPROPSPOS + 1)
				wallhit->props[x].func(doom);
			printf("POS : touched prop type = %d\n", wallhit->props[x].type);//clic sound
		}
	}
}

void		jump(t_stat *stat)
{
	if (stat->jetpack && stat->pos.z == stat->sector->h_floor)
	{
		stat->vel.z = (WALK * stat->height) / 2;
		Mix_Pause(1);
	}
	else if (!stat->jetpack)
	{
		if (stat->pos.z < stat->sector->h_ceil + stat->sector->h_floor - stat->height - 0.1)
			stat->pos.z += 0.1;
		else if (stat->pos.z < stat->sector->h_ceil + stat->sector->h_floor - stat->height)
			stat->pos.z = stat->sector->h_ceil + stat->sector->h_ceil - stat->height;
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
	pl->occupied = timestamp + 1000; //ajuster avec vitesse d'animation
}
