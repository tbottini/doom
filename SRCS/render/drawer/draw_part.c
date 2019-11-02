/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:32:34 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 15:43:40 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int				draw_part_texture(t_arch *arch, int numcol, t_vct2 surface)
{
	t_needle	needle;

	needle = needle_prepare(numcol, &arch->wall->txtr,
		texture_interpolation2d(arch, &arch->wall->txtr), surface);
	return (draw_txtr_column(arch, &needle, &pixel_txtr));
}

int				draw_part_prop(t_arch *arch, t_needle *needle
	, t_vct2 limit, t_prop *prop)
{
	*needle = needle_prepare(needle->numcol, &prop->tex
		, texture_prop_interpolation2d(arch, &prop->tex, prop)
		, needle->surface);
	return (draw_txtr_column_prop(arch, needle, limit));
}

int				draw_part_opacity(t_arch *arch, int cursor, t_vct2 surface
	, t_txtr *txtr)
{
	t_needle	needle;

	needle = needle_prepare(cursor, txtr
		, texture_interpolation2d(arch, txtr), surface);
	return (draw_txtr_column(arch, &needle, &pixel_opacity));
}

/*
**	le point d'ouverture est la ou la porte s'arrete
**	les pourcentage de porte si ce n'est pas inverse
**	1 la texture de porte au point d'ouverture
**		p_wall - p_open la difference par rapport au point d'ouverture
**	si inverse
**	2 la texture de la porte plus l'inversement 1 + 1 - ... = 2 -
**	p_open - p_wall difference par rapport au point d'ouverture
**		mais inverse
*/

int				draw_part_decal(t_arch *arch, int numcol, t_vct2 surface
	, t_pil_render *render_stuff)
{
	double		percent_wall;
	double		percent_txtr;
	t_needle	needle;
	int			px;

	percent_wall = percent_interpolation2d(arch);
	percent_txtr = 2 - percent_wall - render_stuff->perc_open;
	if (percent_txtr > 1)
		percent_txtr = 1;
	else if (percent_txtr < 0)
		percent_txtr = 0;
	px = percent_txtr * arch->wall->txtr.w;
	needle = needle_prepare(numcol, &arch->wall->txtr, px, surface);
	return (draw_txtr_column(arch, &needle, &pixel_txtr));
}

/*
**	on donne la surface(sans le facteur largeur)
**	on convertit la valeur
**	on la trunc
*/

double			draw_part(t_arch *a, int start, int end, uint32_t color)
{
	t_vct2		s;

	s = (t_vct2){start, end};
	if (s.x >= (int)a->portal.b_down[a->px.x] || s.x > a->sdl->size.y)
		return (a->portal.b_down[a->px.x] * a->sdl->size.x + a->px.x);
	else if (s.y <= (int)a->portal.b_up[a->px.x] || s.y < 0)
		return (a->portal.b_up[a->px.x] * a->sdl->size.x + a->px.x);
	if (s.x <= (int)a->portal.b_up[a->px.x] || s.x <= 0)
		s.x = a->px.x + a->portal.b_up[a->px.x] * a->sdl->size.x;
	else
		s.x = s.x * a->sdl->size.x + a->px.x;
	if (s.y > (int)a->portal.b_down[a->px.x] || s.y > a->sdl->size.y)
		s.y = a->px.x + (a->portal.b_down[a->px.x] - 1) * a->sdl->size.x;
	else
		s.y = s.y * a->sdl->size.x;
	while (s.x < s.y)
	{
		a->sdl->screen[s.x] = color;
		s.x += a->sdl->size.x;
	}
	return (s.x);
}
