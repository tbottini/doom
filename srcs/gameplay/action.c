/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:35:25 by akrache           #+#    #+#             */
/*   Updated: 2019/07/28 18:45:10 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

# define RANGE 2

void		next_weapon(t_player *player)
{
	int i;

	i = player->hand->id + 1;
	while (i < NB_WEAPON)
	{
		if (player->weapons[i].on)
			break;
		i++;
	}
	if (i == NB_WEAPON)
		player->hand = &player->weapons[0];
	else
		player->hand = &player->weapons[i];
}

void		prev_weapon(t_player *player)
{
	int i;

	i = (player->hand->id == FIST) ? NB_WEAPON - 1 : player->hand->id - 1;
	while (i > 0)
	{
		if (player->weapons[i].on)
			break;
		i--;
	}
	player->hand = &player->weapons[i];
}

void		change_weapon(t_player *player, int id)
{
	ft_printf("ID SWITCH    %d\n", id);
	if (player->weapons[id].on)
	{
		switch (id)
		{
		case (0):
			printf("no weapon equipped\n");
			break ;
		case (1):
			printf("gun equipped\n");
			break ;
		case (2):
			printf("shotgun equipped\n");
			break ;
		case (3):
			printf("rifle equipped\n");
			break ;
		default:
			printf("couldnt switch\n");
			break;
		}
	}
	if (id >= 0 && id < NB_WEAPON && player->weapons[id].on)
		player->hand = &player->weapons[id];
}

int			is_in_hitbox(t_hitbox *hitbox, t_fvct3 pos, double hheight)
{
	if (hitbox->x <= pos.x && pos.x <= hitbox->w
		&& hitbox->y <= pos.y && pos.y <= hitbox->l
		&& hitbox->z <= (pos.z + hheight) && (pos.z + hheight) <= hitbox->h)
		return (1);
	return (0);
}

void		action(t_doom *doom, t_stat *stat)
{
	int			x;
	t_fvct3		d;
	t_wall		*wallhit;

	d.x = stat->pos.x + (RANGE * sin(stat->rot.x * PI180) * cos(stat->rot.y * PI180));
	d.y = stat->pos.y + (RANGE * sin(stat->rot.x * PI180) * sin(stat->rot.y * PI180));
	d.z = stat->pos.z + (-(RANGE * cos(stat->rot.x * PI180)) + (stat->height / 2));
	if (!(wallhit = collisionV21(stat->sector, stat->pos, d, NULL)))
	{
		ft_printf("No Wall HIT\n");
		return ;
	}
	x = 0;
	while (x < wallhit->nb_props)
	{
		/* printf("Player:\nx: %f\ny: %f\nz: %f\n\n", stat->pos.x, stat->pos.y, stat->pos.z);
		printf("x: %f\ny: %f\nw: %f\ny: %f\nz: %f\nh: %f\n",
			wallhit->props[x].hitbox.x,
			wallhit->props[x].hitbox.y,
			wallhit->props[x].hitbox.w,
			wallhit->props[x].hitbox.l,
			wallhit->props[x].hitbox.z,
			wallhit->props[x].hitbox.h);*/
		if (is_in_hitbox(&wallhit->props[x].hitbox, stat->pos, stat->height / 2))
		{
			if (wallhit->props[x].type == MINWPROPSPOS)
			{
				wallhit->props[x].func(&wallhit->props[x]);
				if (wallhit->props[x].wall)
					wallhit->props[x].wall->ots = doom->timestamp;
			}
			else if (wallhit->props[x].type == MINWPROPSPOS + 1)
				wallhit->props[x].func(doom);
			printf("POS : touched prop type = %d\n", wallhit->props[x].type);
		}
		x++;
	}
}

///////////////////////////////////////////////////////////////////////

void		jump(t_player *player)
{
	if (player->stat.pos.z == player->stat.sector->h_floor)
	{
		player->stat.vel.z = (WALK * player->stat.height) / 2;
		Mix_Pause(1);
	}
}

void		kick(Uint32 timestamp, t_sound *sound, t_player *player)
{
	t_fvct3	d;
	int		range;

	range = 1;
	d.x = range * sin(player->stat.rot.x * PI180) * cos(player->stat.rot.y * PI180);
	d.y = range * sin(player->stat.rot.x * PI180) * sin(player->stat.rot.y * PI180);
	d.z = -(range * cos(player->stat.rot.x * PI180)) + (player->stat.height / 2);
	Mix_PlayChannel(2, sound->tab_effect[6], 0);
	player->occupied = timestamp + 1000;//ajuster avec vitesse d'animation
}
