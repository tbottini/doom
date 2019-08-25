/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 21:02:06 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/25 21:42:12 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
**	on determine la position gauche et droite du props sur le mur
**	et puis on le convertie en pourcentage
*/

void				prop_init(t_prop *prop, t_wall *wall)
{
	double			hyp;
	double			hyp_pos;
	t_fvct2			diff;

	diff.x = wall->next->p.x - wall->pillar->p.x;
	diff.y = wall->next->p.y - wall->pillar->p.y;
	hyp = sqrt(diff.x * diff.x + diff.y * diff.y);
	diff.x = prop->pos.x - wall->pillar->p.x;
	diff.y = prop->pos.y - wall->pillar->p.y;
	hyp_pos = sqrt(diff.x * diff.x + diff.y * diff.y);
	prop->percent.x = 1 - (hyp_pos - 0.5) / (hyp);
	prop->percent.y = 1 - (hyp_pos + 0.5) / (hyp);
}

/*
**	va iterer sur tout les props d'un tableau
*/

void				prop_iter(t_prop *prop, int len
	, void (*prop_iter)(t_prop*))
{
	int				i;

	i = 0;
	while (i <= len)
	{
		prop_iter(&prop[i]);
		i++;
	}
}

/*
**	va iterer sur tous les props d'un tableau avec
**		une fonction acceptant une structure quelconque
*/

void				prop_iter_v(t_prop *prop, int len
	, void (*prop_iter)(t_prop*, void*), void *sup)
{
	int				i;

	i = 0;
	while (i <= len)
	{
		prop_iter(&prop[i], sup);
		i++;
	}
}

void				prop_get_pos(t_arch *arch, t_prop *prop
	, t_fvct2 *left, t_fvct2 *right)
{
	t_fvct2			p_wall;
	t_fvct2			delta_wall;

	p_wall.x = (prop->percent.x - arch->shift_txtr.x)
		/ (arch->shift_txtr.y - arch->shift_txtr.x);
	p_wall.y = (prop->percent.y - arch->shift_txtr.x)
		/ (arch->shift_txtr.y - arch->shift_txtr.x);
	delta_wall.x = arch->next.x - arch->pillar.x;
	delta_wall.y = arch->next.y - arch->pillar.y;
	left->x = delta_wall.x * p_wall.x + arch->pillar.x;
	left->y = delta_wall.y * p_wall.x + arch->pillar.y;
	right->x = delta_wall.x * p_wall.y + arch->pillar.x;
	right->y = delta_wall.y * p_wall.y + arch->pillar.y;
}

void				prop_get_px(t_arch *arch, t_vct2 *px_props
	, t_fvct2 left, t_fvct2 right)
{
	if (right.x < 0 && left.x < 0)
		*px_props = (t_vct2){0, 0};
	else if (right.x < 0)
	{
		px_props->x = arch->sdl->size.x / 2 - ((left.y / left.x)
			* (arch->sdl->size.x / 2));
		px_props->y = (right.y < 0) ? arch->sdl->size.x - 1 : 0;
	}
	else if (left.x < 0)
	{
		px_props->y = arch->sdl->size.x / 2 - ((right.y / right.x)
			* (arch->sdl->size.x / 2));
		px_props->x = (left.y < 0) ? arch->sdl->size.x - 1 : 0;
	}
	else
	{
		px_props->x = arch->sdl->size.x / 2 - ((left.y / left.x)
			* (arch->sdl->size.x / 2));
		px_props->y = arch->sdl->size.x / 2 - ((right.y / right.x)
			* (arch->sdl->size.x / 2));
	}
}

/*
**	a partir du pourcentage du prop sur le mur et les information a propos
**		du mur et de l'ecran
**	on recupere le pixel sur l'ecran du props
**	- recuperation du pourcentage dans le mur actuelle
**	- recuperation de la position dans la ref de la camera
**	- recuperation projection
*/

t_vct2				prop_get_screen_pixel(t_prop *prop, t_arch *arch)
{
	t_fvct2			left;
	t_fvct2			right;
	t_vct2			px_props;

	prop_get_pos(arch, prop, &left, &right);
	prop_get_px(arch, &px_props, left, right);
	if (px_props.x > px_props.y)
	{
		prop->px.x = px_props.y;
		prop->px.y = px_props.x;
	}
	else
	{
		prop->px.x = px_props.x;
		prop->px.y = px_props.y;
	}
	return (px_props);
}

void				prop_init_render(t_prop *prop, void *arch)
{
	t_arch			*arc;
	t_vct2			px;

	arc = (t_arch*)arch;
	px = prop_get_screen_pixel(prop, arc);
}

extern inline bool	column_is_printable(t_arch *arch, t_prop *prop)
{
	return (arch->px.x > prop->px.x
			&& arch->px.x < prop->px.y
			&& prop->pos.z + 1.0 > 0
			&& prop->pos.z < arch->sector->h_ceil);
}

void				props_draw_column(t_prop *props, t_arch *a
	, t_fvct2 s)
{
	int				i;
	int				cursor;
	t_vct2			tmp;
	t_fvct2			hei;
	int				padding_render;

	i = 0;
	while (i <= a->wall->nb_props)
	{
		if (column_is_printable(a, &props[i]))
		{
			hei.x = (a->sector->h_ceil - 1 - (props[i].pos.z
				- a->sector->h_floor)) / a->sector->h_ceil;
			hei.y = (props[i].pos.z - a->sector->h_floor) / a->sector->h_ceil;
			padding_render = (s.y - s.x) * hei.x;
			tmp.x = s.x + (s.y - s.x) * hei.x;
			tmp.y = s.y - (s.y - s.x) * hei.y;
			cursor = a->px.x + tmp.x * a->sdl->size.x;
			draw_part_prop(a, cursor, tmp, (t_vct2){s.x, s.y}, &props[i]);
			break ;
		}
		i++;
	}
}
