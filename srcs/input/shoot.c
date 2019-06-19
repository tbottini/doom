/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:51:14 by akrache           #+#    #+#             */
/*   Updated: 2019/06/19 16:54:07 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

# define RADIUS 500

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
			;//send_bullet(player->stat.pos, /*RocketTexture*/);
		else
			;//bullet(&player->stat);
		player->weapons[player->hand].clip--;
	}
}

double			bullet_clipping(t_wall wall, t_fvct3 pos, double angle)
{
	t_fvct2		inter;
	t_fvct2		diff;
	t_fvct2		diff2;
	double		coef_wall;
	double		b;

	diff.x = wall.pillar.p.x - pos.x;
	diff.y = wall.pillar.p.y - pos.y;
	diff2.x = wall.next->p.x - pos.x;
	diff2.y = wall.next->p.y - pos.y;
	if (diff2.x - diff.x < 0.00001 && diff2.x - diff.x > -0.000001)
	{
		inter.x = diff.x;
		inter.y = diff.x * tan(angle * PI180);
	}
	else
	{
		coef_wall = (diff2.y - diff.y) / (diff2.x - diff.x);
		b = diff.y - diff.x * coef_wall;
		inter.x = b / (tan(angle * PI180) - coef_wall);
		inter.y = coef_wall * inter.x + b;
	}
	return (distance((t_fvct2){0.0, 0.0}, inter));
}

t_wall		*real_hit(t_wall **walls, t_fvct3 pos, double angle)
{
	t_wall *hit;
	int		i;
	double	res;
	double	tmp;

	i = 0;
	res = 987654312.0;
	hit = NULL;
	while (walls[i])
	{
		if ((tmp = bullet_clipping(*walls[i], pos, angle)) < res)
		{
			res = tmp;
			hit = walls[i];
		}
		++i;
	}
	printf("MURMUR AU MUR PAS MUR || %f ||\n", res);
	return (hit);
}

t_wall		*possible_walls(t_stat *stat, t_fvct3 ori, t_fvct3 pos)
{
	t_wall	*walls[50];
	int		i;
	int		j;
	int		index;

	j = -1;
	index = 0;
	while (++j < stat->sector->len_sub)
	{
		i = -1;
		while (++i < stat->sector->ssector[j].len)
		{
			if (vector_intersect(ori, pos, *(t_fvct3*)&stat->sector->ssector[j].wall[i].pillar.p, *(t_fvct3*)&stat->sector->ssector[j].wall[i].next->p))
			{
				walls[index] = &stat->sector->ssector[j].wall[i];
				index++;
				printf("sub wall %d\n", i);
			}
		}
	}
	i = -1;
	while (++i < stat->sector->len)
	{
		if (vector_intersect(ori, pos, *(t_fvct3*)&stat->sector->wall[i].pillar.p, *(t_fvct3*)&stat->sector->wall[i].next->p))
		{
			walls[index] = &stat->sector->wall[i];
			index++;
			printf("sec wall %d\n", i);
		}
	}
	walls[index] = NULL;
	return (real_hit(walls, pos, stat->rot.y));
}

void		bullet(t_doom *doom, t_stat *stat)
{
	t_fvct3	d;
	t_wall	*hit;

	d.x = stat->pos.x + (RADIUS * sin(stat->rot.x * PI180) * cos(stat->rot.y * PI180));
	d.y = stat->pos.y + (RADIUS * sin(stat->rot.x * PI180) * sin(stat->rot.y * PI180));
	d.z = stat->pos.z + (-(RADIUS * cos(stat->rot.x * PI180)) + (stat->height / 2));
	hit = possible_walls(stat, d, stat->pos);
	if (hit)
	{
		(void)doom;
		printf("HIT\n");
		//apply damage or impact texture
	}
	else
		printf("MISSED\n");
	printf("\rRot : %f\t%f\n", stat->rot.x, stat->rot.y);
	printf("\rbullet landed : x = %f | y = %f | z = %f\n", d.x, d.y, d.z);
}
