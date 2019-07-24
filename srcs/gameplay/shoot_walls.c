/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 21:41:46 by akrache           #+#    #+#             */
/*   Updated: 2019/07/24 21:07:04 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
static double	bullet_clipping(t_wall wall, t_stat *stat)
{
	t_fvct2		inter;
	t_fvct2		diff;
	t_fvct2		diff2;
	double		coef_wall;
	double		b;

	diff.x = wall.pillar->p.x - stat->pos.x;
	diff.y = wall.pillar->p.y - stat->pos.y;
	diff2.x = wall.next->p.x - stat->pos.x;
	diff2.y = wall.next->p.y - stat->pos.y;
	if (diff2.x - diff.x < 0.0001 && diff2.x - diff.x > -0.0001)
	{
		inter.x = diff.x;
		inter.y = diff.x * tan(stat->rot.y * PI180);
	}
	else
	{
		coef_wall = (diff2.y - diff.y) / (diff2.x - diff.x);
		b = diff.y - diff.x * coef_wall;
		inter.x = b / (tan(stat->rot.y * PI180) - coef_wall);
		inter.y = coef_wall * inter.x + b;
	}
	return (distance((t_fvct2){0.0, 0.0}, inter));
}

static t_wall	*real_hit(t_wall **walls, t_stat *stat)
{
	t_wall	*hit;
	int		i;
	double	res;
	double	tmp;
	double	toto;

	i = 0;
	res = 987654321.0;
	hit = NULL;
	toto = cos((stat->rot.x - 90.0) * PI180);
	if (toto < G_EPSILON)
		toto = 1;
	while (walls[i])
	{
		if ((tmp = bullet_clipping(*walls[i], stat)) / toto < res)
		{
			res = tmp;
			hit = walls[i];
		}
		++i;
	}
	if (hit)
		hit->dist = res;
	return (hit);
}

t_wall			*possible_walls(t_wall **walls, t_stat *stat, t_fvct3 ori, int *index)
{
	int		i;

	i = -1;
	while (*index < 50 && ++i < stat->sector->len)
	{
		if (vector_intersect(ori, stat->pos, *(t_fvct3*)&stat->sector->wall[i].pillar->p, *(t_fvct3*)&stat->sector->wall[i].next->p))
		{
			walls[*index] = &stat->sector->wall[i];
			*index++;
		}
	}
	walls[*index] = NULL;
	return (real_hit(walls, stat));
}

void			apply_wall(t_wall *wall, t_stat *stat, t_fvct3 mo)
{
	t_fvct3 aim;

	aim.x = stat->pos.x + wall->dist * (mo.x / RADIUS);
	aim.y = stat->pos.y + wall->dist * (mo.y / RADIUS);
	aim.z = stat->pos.z + wall->dist * (mo.z / RADIUS);
	(void)wall;//apply texture on wall
	printf("SUPER COORD : x = %f | y = %f | z = %f\n", aim.x, aim.y, aim.z);
	printf("distance || %f ||\n\n", wall->dist);
}
*/

/*
void			apply_wall(t_wall *wall, t_stat *stat, t_fvct3 mo)
{
	t_fvct3 aim;

	aim.x = stat->pos.x + wall->dist * (mo.x / RADIUS);
	aim.y = stat->pos.y + wall->dist * (mo.y / RADIUS);
	aim.z = stat->pos.z + wall->dist * (mo.z / RADIUS);
	(void)wall;//apply texture on wall
	printf("SUPER COORD : x = %f | y = %f | z = %f\n", aim.x, aim.y, aim.z);
	printf("distance || %f ||\n\n", wall->dist);
}

void		supa_shoota(t_stat *stat, t_fvct3 d, t_fvct3 mo)
{
	t_super	super;

	possible(&super, stat, d);
	wall_real_hit(&super, stat);
	apply(&super, stat, mo);
}*/


//==================ACTION==============================

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