/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:03:42 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 15:44:12 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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
