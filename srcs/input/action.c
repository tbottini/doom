/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:35:25 by akrache           #+#    #+#             */
/*   Updated: 2019/06/19 18:46:35 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

# define RANGE 2

void		next_weapon(t_player *player)
{
	player->hand += (player->hand == WEAPON_MAX - 1) ? -player->hand : 1;
}

void		prev_weapon(t_player *player)
{
	player->hand -= player->hand == 0 ? (WEAPON_MAX + 1) : 1;
}

void		change_weapon(t_player *player, int new_w)
{
	if (new_w >= 0 && new_w < WEAPON_MAX)
		player->hand = new_w;
}
///////////////////////////////////////////////////////////////////////////////
double			button_clipping(t_prop prop, t_fvct3 pos, double angle)
{
	t_fvct2		inter;
	t_fvct2		diff;
	t_fvct2		diff2;
	double		coef_wall;
	double		b;

	diff.x = prop.x1 - pos.x;
	diff.y = prop.y1 - pos.y;
	diff2.x = prop.x2 - pos.x;
	diff2.y = prop.y2 - pos.y;
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

t_prop		*button_hit(t_prop **but, t_fvct3 pos, double angle)
{
	t_prop *hit;
	int		i;
	double	res;
	double	tmp;

	i = 0;
	res = 987654312.0;
	hit = NULL;
	while (but[i])
	{
		if ((tmp = button_clipping(*but[i], pos, angle)) < res)
		{
			res = tmp;
			hit = but[i];
		}
		++i;
	}
	printf("BOUTON TONTON || %f ||\n", res);
	return (hit);
}

int			is_button(t_prop *prop)
{
	return (prop->func ? 1 : 0);
}

t_prop		*possible_button(t_stat *stat, t_fvct3 ori, t_fvct3 pos)
{
	t_prop		*but[10];
	t_prop		*b;
	int			i;
	int			j;
	int			index;

	j = -1;
	index = 0;
	b = NULL;
	while (++j < stat->sector->len_sub)
	{
		i = -1;
		while (++i < stat->sector->ssector[j].len_prop)
		{
			if (is_button(b = &stat->sector->ssector[j].prop[i]) && vector_intersect(ori, pos, (t_fvct3){b->x1, b->y1, 0.0}, (t_fvct3){b->x2, b->y2, 0.0}))
			{
				but[index] = b;
				if (++index > 9)
					return (button_hit(but, pos, stat->rot.y));
				printf("sub wall %d\n", i);
			}
		}
	}
	i = -1;
	while (++i < stat->sector->len)
	{
		if (is_button(b = &stat->sector->prop[i]) && vector_intersect(ori, pos, (t_fvct3){b->x1, b->y1, 0.0}, (t_fvct3){b->x2, b->y2, 0.0}))
		{
			but[index] = b;
			if (++index > 9)
				return (button_hit(but, pos, stat->rot.y));
			printf("sec wall %d\n", i);
		}
	}
	but[index] = NULL;
	return (button_hit(but, pos, stat->rot.y));
}

void		action(t_player *player, t_stat *stat)
{
	t_fvct3		d;
	t_prop	*hit;

	(void)player;
	d.x = stat->pos.x + (RANGE * sin(stat->rot.x * PI180) * cos(stat->rot.y * PI180));
	d.y = stat->pos.y + (RANGE * sin(stat->rot.x * PI180) * sin(stat->rot.y * PI180));
	d.z = stat->pos.z + (-(RANGE * cos(stat->rot.x * PI180)) + (stat->height / 2));
	hit = possible_button(stat, d, stat->pos);
	if (hit)
	{
		printf("BUTTON HIT\n");
		//apply damage or impact texture
	}
	else
		printf("BUTTON MISSED\n");
	printf("\rRot : %f\t%f\n", stat->rot.x, stat->rot.y);
	printf("\rbullet landed : x = %f | y = %f | z = %f\n", d.x, d.y, d.z);
}

///////////////////////////////////////////////////////////////////////

void		jump(t_player *player)
{
	if (player->stat.pos.z == player->stat.sector->h_floor)
	{
		player->stat.vel.z = WALK;
		Mix_Pause(1);
	}
}

void		kick(t_doom *doom, t_player *player)
{
	t_fvct3	d;
	int		range;

	range = 1;
	d.x = range * sin(player->stat.rot.x * PI180) * cos(player->stat.rot.y * PI180);
	d.y = range * sin(player->stat.rot.x * PI180) * sin(player->stat.rot.y * PI180);
	d.z = -(range * cos(player->stat.rot.x * PI180)) + (player->stat.height / 2);
	Mix_PlayChannel(2, doom->sound.tab_effect[6], 0);
}
