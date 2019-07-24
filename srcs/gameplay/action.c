/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:35:25 by akrache           #+#    #+#             */
/*   Updated: 2019/07/24 14:11:13 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

# define RANGE 2

void		next_weapon(t_player *player)
{
	int i;

	i = player->hand.id + 1;
	while (i < NB_WEAPON)
	{
		if (player->weapons[i].on)
			break;
		i++;
	}
	if (i == NB_WEAPON)
		player->hand = player->weapons[0];
	else
		player->hand = player->weapons[i];
}

void		prev_weapon(t_player *player)
{
	int i;

	if ((i = player->hand.id - 1) == -1)
		player->hand = player->weapons[NB_WEAPON - 1];
	while (i > 0)
	{
		if (player->weapons[i].on)
			break;
		i--;
	}
	player->hand = player->weapons[i];
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
		player->hand = player->weapons[id];
}
/*
double			button_clipping(t_prop prop, t_fvct3 pos, double angle)
{
	t_fvct2		inter;
	t_fvct2		diff;
	t_fvct2		diff2;
	double		coef_wall;
	double		b;

	//diff.x = prop.x1 - pos.x;
	//diff.y = prop.y1 - pos.y;
	//diff2.x = prop.x2 - pos.x;
	//diff2.y = prop.y2 - pos.y;
	(void)pos;
	diff.x = sin((angle - 90.0) * PI180) * (prop.width / 2);
	diff.y = cos((angle - 90.0) * PI180) * (prop.width / 2);
	diff2.x = sin((angle + 90.0) * PI180) * (prop.width / 2);
	diff2.y = cos((angle + 90.0) * PI180) * (prop.width / 2);
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


static void			prop_hitbox(t_prop *prop, double angle)
{
	prop->e1.x = sin((angle - 90.0) * PI180) * (prop->width / 2);
	prop->e1.y = cos((angle - 90.0) * PI180) * (prop->width / 2);
	prop->e2.x = sin((angle + 90.0) * PI180) * (prop->width / 2);
	prop->e2.y = cos((angle + 90.0) * PI180) * (prop->width / 2);
}

 t_prop		*possible_button(t_stat *stat, t_fvct3 ori, t_fvct3 pos)
{
	t_prop		*but[10];
	t_prop		*b;
	int			i;
	int			index;

	index = 0;
	b = NULL;
	i = -1;
	while (++i < stat->sector->len)
	{
		b = &stat->sector->props[i];
		prop_hitbox(b, stat->rot.y);
		//if (is_button(b = &stat->sector->prop[i]) && vector_intersect(ori, pos, (t_fvct3){b->x1, b->y1, 0.0}, (t_fvct3){b->x2, b->y2, 0.0}))
		if (b->func && vector_intersect(ori, pos, (t_fvct3){b->e1.x, b->e1.y, 0.0}, (t_fvct3){b->e2.x, b->e2.y, 0.0}))
		{
			but[index] = b;
			if (++index > 9)
				return (button_hit(but, pos, stat->rot.y));
			printf("sec wall %d\n", i);
		}
	}
	but[index] = NULL;
	return (button_hit(but, pos, stat->rot.y));
}*/

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
		printf("Player:\nx: %f\ny: %f\nz: %f\n\n", stat->pos.x, stat->pos.y, stat->pos.z);
		printf("x: %f\ny: %f\nw: %f\ny: %f\nz: %f\nh: %f\n",
			wallhit->props[x].hitbox.x,
			wallhit->props[x].hitbox.y,
			wallhit->props[x].hitbox.w,
			wallhit->props[x].hitbox.l,
			wallhit->props[x].hitbox.z,
			wallhit->props[x].hitbox.h);
		if (is_in_hitbox(&wallhit->props[x].hitbox, d, 0))//stat->pos))
		{
			if (wallhit->props[x].type == MINWPROPSPOS)
				wallhit->props[x].func(wallhit->props[x].wall);
			else if (wallhit->props[x].type == MINWPROPSPOS + 1)
				wallhit->props[x].func(doom);
			printf("D : touched prop type = %d\n", wallhit->props[x].type);
		}
		else if (is_in_hitbox(&wallhit->props[x].hitbox, stat->pos, stat->height / 2))
		{
			if (wallhit->props[x].type == MINWPROPSPOS)
				wallhit->props[x].func(wallhit->props[x].wall);
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

void		kick(t_sound *sound, t_player *player)
{
	t_fvct3	d;
	int		range;

	range = 1;
	d.x = range * sin(player->stat.rot.x * PI180) * cos(player->stat.rot.y * PI180);
	d.y = range * sin(player->stat.rot.x * PI180) * sin(player->stat.rot.y * PI180);
	d.z = -(range * cos(player->stat.rot.x * PI180)) + (player->stat.height / 2);
	Mix_PlayChannel(2, sound->tab_effect[6], 0);
}
