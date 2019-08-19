/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 21:02:06 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/19 18:07:55 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "debug.h"

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
**	va iterer sur tout les props d'un tableauå
*/

void				prop_iter(t_prop *prop, int len, void(*prop_iter)(t_prop*))
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
**	va iterer sur tous les props d'un tableau avec une fonction acceptant une structure quelconque
*/

void				prop_iter_v(t_prop *prop, int len, void(*prop_iter)(t_prop*, void*), void *sup)
{
	int				i;

	i = 0;
	while (i <= len)
	{
		prop_iter(&prop[i], sup);
		i++;
	}
}

/*
**	a partir du pourcentage du prop sur le mur et les information a propos du mur et de l'ecran
**	on recupere le pixel sur l'ecran du props
**	- recuperation du pourcentage dans le mur actuelle
**	- recuperation de la position dans la ref de la camera
**	- recuperation projection
*/

t_vct2				prop_get_screen_pixel(t_prop *prop, t_arch *arch)
{
	t_fvct2			percent_wall;
	t_fvct2			delta_wall;
	t_fvct2			prop_left_pos;
	t_fvct2			prop_rigth_pos;
	t_vct2			px_props;

	percent_wall.x = (prop->percent.x - arch->shift_txtr.x) / (arch->shift_txtr.y - arch->shift_txtr.x);
	percent_wall.y = (prop->percent.y - arch->shift_txtr.x) / (arch->shift_txtr.y - arch->shift_txtr.x);
	delta_wall.x = arch->next.x - arch->pillar.x;
	delta_wall.y = arch->next.y - arch->pillar.y;
	prop_left_pos.x = delta_wall.x * percent_wall.x + arch->pillar.x;
	prop_left_pos.y = delta_wall.y * percent_wall.x + arch->pillar.y;
	prop_rigth_pos.x = delta_wall.x * percent_wall.y + arch->pillar.x;
	prop_rigth_pos.y = delta_wall.y * percent_wall.y + arch->pillar.y;
	px_props.y = arch->sdl->size.x / 2 - ((prop_rigth_pos.y / prop_rigth_pos.x) * (arch->sdl->size.x / 2));
	px_props.x = arch->sdl->size.x / 2 - ((prop_left_pos.y / prop_left_pos.x) * (arch->sdl->size.x / 2));
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
	if (debug_screen == 8)
	{
		fill_line_debug(arch, arch->sdl, (t_vct2){px_props.x, arch->sdl->size.y / 2}, (t_vct2){px_props.y, arch->sdl->size.y / 2}, 0xffffffff);
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

void				props_draw_column(t_prop *props, t_arch *arch, t_fvct2 surface)
{
	int				i;
	int				cursor;
	t_vct2			surface_tmp;
	t_fvct2			heigth_percent;
	bool			col_print;
	int				padding_render;

	i = 0;
	col_print = false;
	while (i <= arch->wall->nb_props && !col_print)
	{
		if (arch->px.x > props[i].px.x && arch->px.x < props[i].px.y && props[i].pos.z + 1.0 > 0 && props[i].pos.z < arch->sector->h_ceil)
		{
			heigth_percent.x = (arch->sector->h_ceil - 1 - props[i].pos.z) / arch->sector->h_ceil;
			heigth_percent.y = props[i].pos.z / arch->sector->h_ceil;
			padding_render = (surface.y - surface.x) * heigth_percent.x;
			surface_tmp.x = surface.x + padding_render;
			surface_tmp.y = surface.y - padding_render;

			surface_tmp.x = surface.x + (surface.y - surface.x) * heigth_percent.x;
			surface_tmp.y = surface.y - (surface.y - surface.x) * heigth_percent.y;
			cursor = arch->px.x + surface_tmp.x * arch->sdl->size.x;
			if (cursor < 0)
				cursor = arch->px.x;
			draw_part_prop(arch, cursor, surface_tmp, &props[i]);
			col_print = true;
		}
		i++;
	}
}
