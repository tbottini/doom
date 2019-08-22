/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:32:34 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/23 01:50:37 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

typedef struct	s_needle
{
	int			numcol;
	t_vct2		surface;
	t_txtr		*txtr;
	uint32_t	txtr_col;
	double		coef;
	double		buff;
}				t_needle;

void			needle_buff_affect(t_needle *needle)
{
	if (needle->buff > 1.0)
	{
		needle->txtr_col += (int)needle->buff * needle->txtr->w;
		needle->buff = needle->buff - (int)needle->buff;
	}
}

t_needle		needle_prepare(int numcol, t_txtr *txtr, uint32_t txtr_col
	, t_vct2 surface)
{
	t_needle	needle;

	needle.numcol = numcol;
	needle.txtr = txtr;
	needle.surface = surface;
	needle.txtr_col = txtr_col;
	return (needle);
}

/*
**	rend une colonne de texture
**	-numcol le numero de la colonne
**	-surface la taille de la surface a rendre le debut et la fin
**	-txtr la texture a rendre
**	-txtr_col la colonne de pixels dans la texture
*/
int				draw_txtr_column(t_arch *a, t_needle *ne)
{
	ne->buff = 0;
	ne->coef = (double)ne->txtr->h / (ne->surface.y - ne->surface.x);
	if (ne->surface.y < (int)a->portal.b_up[a->px.x])
		return (a->px.x + a->portal.b_up[a->px.x] * a->sdl->size.x);
	if (ne->surface.x < (int)a->portal.b_up[a->px.x])
	{
		ne->buff = (-ne->surface.x + a->portal.b_up[a->px.x]) * ne->coef;
		needle_buff_affect(ne);
		ne->surface.x = a->portal.b_up[a->px.x];
	}
	while (ne->surface.x < ne->surface.y
		&& ne->surface.x < (int)a->portal.b_down[a->px.x])
	{
		if (ne->numcol < a->sdl->size.x * a->sdl->size.y
			&& ne->txtr_col < ne->txtr->w * ne->txtr->h)
			a->sdl->screen[ne->numcol] = ne->txtr->pixels[ne->txtr_col];
		ne->surface.x++;
		ne->numcol += a->sdl->size.x;
		ne->buff += ne->coef;
		needle_buff_affect(ne);
	}
	return (ne->numcol);
}

void			needle_reajust(t_arch *arch, t_needle *needle, int limit)
{
	needle->numcol = arch->px.x + limit * arch->sdl->size.x;
	needle->buff = (limit - needle->surface.x) * needle->coef;
	needle_buff_affect(needle);
	needle->surface.x = limit;
}

bool			needle_in_line(t_arch *arch, t_needle *needle, int limit)
{
	return (needle->surface.x < needle->surface.y
		&& needle->surface.x < (int)arch->portal.b_down[arch->px.x]
		&& needle->surface.x < limit);
}

void			needle_indent_down(t_needle *needle, t_arch *arch)
{
	needle->surface.x++;
	needle->numcol += arch->sdl->size.x;
	needle->buff += needle->coef;
}

int				draw_txtr_column_prop(t_arch *a, t_needle *n, t_vct2 limit)
{
	n->buff = 0;
	n->coef = (double)n->txtr->h / (n->surface.y - n->surface.x);
	if (n->surface.y < (int)a->portal.b_up[a->px.x])
		return (a->px.x + a->portal.b_up[a->px.x] * a->sdl->size.x);
	if (n->surface.x < limit.x)
		needle_reajust(a, n, limit.x);
	else if (n->surface.x < (int)a->portal.b_up[a->px.x])
		needle_reajust(a, n, a->portal.b_up[a->px.x]);
	while (needle_in_line(a, n, limit.y))
	{
		if (n->numcol < a->sdl->size.x * a->sdl->size.y
			&& n->txtr_col < n->txtr->w * n->txtr->h)
			a->sdl->screen[n->numcol] = n->txtr->pixels[n->txtr_col];
		needle_indent_down(n, a);
		needle_buff_affect(n);
	}
	return (n->numcol);
}

int				draw_txtr_opacity(t_arch *a, t_needle *ne)
{
	ne->buff = 0;
	ne->coef = (double)ne->txtr->h / (ne->surface.y - ne->surface.x);
	if (ne->surface.y < (int)a->portal.b_up[a->px.x])
		return (a->px.x + a->portal.b_up[a->px.x] * a->sdl->size.x);
	if (ne->surface.x < (int)a->portal.b_up[a->px.x])
	{
		ne->buff = (-ne->surface.x + a->portal.b_up[a->px.x]) * ne->coef;
		needle_buff_affect(ne);
		ne->surface.x = a->portal.b_up[a->px.x];
	}
	while (ne->surface.x < ne->surface.y
		&& ne->surface.x < (int)a->portal.b_down[a->px.x])
	{
		if (ne->numcol < a->sdl->size.x * a->sdl->size.y
			&& ne->txtr_col < ne->txtr->w * ne->txtr->h)
				a->sdl->screen[ne->numcol] = opacity_from_color(ne->txtr->pixels[ne->txtr_col], a->sdl->screen[ne->numcol]);
		ne->surface.x++;
		ne->numcol += a->sdl->size.x;
		ne->buff += ne->coef;
		needle_buff_affect(ne);
	}
	return (ne->numcol);
}

int				draw_part_texture(t_arch *arch, int numcol, t_vct2 surface)
{
	t_needle	needle;

	needle.txtr_col = texture_interpolation2d(arch, &arch->wall->txtr);
	needle.numcol = numcol;
	needle.surface = surface;
	needle.txtr = &arch->wall->txtr;

	return (draw_txtr_column(arch, &needle));
}

int				draw_part_prop(t_arch *arch, int numcol, t_vct2 surface
	, t_vct2 limit, t_prop *prop)
{
	t_needle	needle;

	needle = needle_prepare(numcol, &prop->tex
		, texture_prop_interpolation2d(arch, &prop->tex, prop), surface);
	//px = texture_prop_interpolation2d(arch, &prop->tex, prop);
	return (draw_txtr_column_prop(arch, &needle, limit));
	//return (draw_txtr_column_prop(arch, numcol, surface, limit, &prop->tex, px));
}

int				draw_part_opacity(t_arch *arch, int cursor, t_vct2 surface
	, t_txtr *txtr)
{
	t_needle	needle;

	needle = needle_prepare(cursor, txtr
		, texture_interpolation2d(arch, txtr), surface);
	return (draw_txtr_opacity(arch, &needle));
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

	needle.numcol = numcol;
	needle.surface = surface;
	needle.txtr = &arch->wall->txtr;
	percent_wall = percent_interpolation2d(arch);
	percent_txtr = 2 - percent_wall - render_stuff->perc_open;
	if (percent_txtr > 1)
		percent_txtr = 1;
	else if (percent_txtr < 0)
		percent_txtr = 0;
	needle.txtr_col = percent_txtr * arch->wall->txtr.w;
	return (draw_txtr_column(arch, &needle));
}

/*
**	on donne la surface(sans le facteur largeur)
**	on convertit la valeur
**	on la trunc
*/

double			draw_part(t_arch *arch, int start, int end, uint32_t color)
{
	t_vct2		surface;

	surface = (t_vct2){start, end};
	if (surface.x >= (int)arch->portal.b_down[arch->px.x]
		|| surface.x > arch->sdl->size.y)
	{
		return (arch->portal.b_down[arch->px.x] * arch->sdl->size.x + arch->px.x);
	}
	else if (surface.y <= (int)arch->portal.b_up[arch->px.x]
		|| surface.y < 0)
	{
		return (arch->portal.b_up[arch->px.x] * arch->sdl->size.x + arch->px.x);
	}
	if (surface.x <= (int)arch->portal.b_up[arch->px.x]
		|| surface.x <= 0)
		surface.x = arch->px.x + arch->portal.b_up[arch->px.x] * arch->sdl->size.x;
	else
		surface.x = surface.x * arch->sdl->size.x + arch->px.x;
	if (surface.y > (int)arch->portal.b_down[arch->px.x]
		|| surface.y > arch->sdl->size.y)
		surface.y = arch->px.x + (arch->portal.b_down[arch->px.x] - 1) * arch->sdl->size.x;
	else
		surface.y = surface.y * arch->sdl->size.x;
	while (surface.x < surface.y)
	{
		arch->sdl->screen[surface.x] = color;
		surface.x += arch->sdl->size.x;
	}
	return (surface.x);
}
