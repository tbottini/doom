/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:51:14 by akrache           #+#    #+#             */
/*   Updated: 2019/06/10 02:01:57 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		reload(t_weapon *weapon)
{
	int	r;

	r = weapon->clip_max - weapon->clip;
	(weapon->ammo - r < 0 ? r += weapon->ammo - r : 0);
	weapon->ammo -= r;
	weapon->clip = r;
}

void		shoot(t_player *player)
{
	if (player->weapons[player->hand].clip == 0)
		reload(&(player->weapons[player->hand]));
	else
	{
		if (player->hand == 4)//ROCKETLAUNCHER)
			;//send_bullet(player->pos, /*RocketTexture*/);
		else
			;//bullet(player);
		player->weapons[player->hand].clip--;
	}
}

void		kick(t_doom *doom, t_player *player)
{
	t_fvct3	d;
	int		range;

	range = 1;
	d.x = range * sin(player->rot.x * PI180) * cos(player->rot.y * PI180);
	d.y = range * sin(player->rot.x * PI180) * sin(player->rot.y * PI180);
	d.z = -(range * cos(player->rot.x * PI180)) + (player->height / 2);
}

//===================================================================================================//

t_wall		*collision_bullet(t_doom *doom, t_fvct3 ori, t_fvct3 pos)// ne renvoie pas encore le mur le plus proche
{
	int		i;
	int		j;

	j = -1;
	while (++j < doom->sector->len_sub)
	{
		i = -1;
		while (++i < doom->sector->len)
		{
			if (vector_intersect(ori, pos, *(t_fvct3*)&doom->sector->ssector[j].wall[i].pillar.p, *(t_fvct3*)&doom->sector->ssector[j].wall[i].next->p))
				{printf("\nsubwall %d\n", i);return (&doom->sector->wall[i]);}
		}
	}
	i = 0;
	while (i < doom->sector->len)
	{
		if (vector_intersect(ori, pos, *(t_fvct3*)&doom->sector->wall[i].pillar.p, *(t_fvct3*)&doom->sector->wall[i].next->p))
			{printf("\nwall %d\n", i);return (&doom->sector->wall[i]);}
		++i;
	}
	printf("\nwall %d\n", 0);
	return (NULL);
}

# define RADIUS 500

void		bullet(t_doom *doom, t_player *player)
{
	t_fvct3	d;
	t_wall	*hit;

	d.x = RADIUS * sin(player->rot.x * PI180) * cos(player->rot.y * PI180);
	d.y = RADIUS * sin(player->rot.x * PI180) * sin(player->rot.y * PI180);
	d.z = -(RADIUS * cos(player->rot.x * PI180)) + (player->height / 2);
	hit = collision_bullet(doom, d, player->pos);
	if (hit)
	{
		printf("HIT\n");
	}
	else
		printf("MISSED\n");
	printf("\rRot : %f\t%f\n", player->rot.x, player->rot.y);
	printf("\rFov : %d\n", player->fov);
	printf("\rbullet landed : x = %f | y = %f | z = %f\n", d.x, d.y, d.z);
}
