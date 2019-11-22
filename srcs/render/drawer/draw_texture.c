/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 03:39:30 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 15:33:51 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

uint32_t				pixel_opacity(t_arch *arch, t_needle *needle)
{
	return (opacity_from_color(needle->txtr->pixels[needle->txtr_col]
		, arch->sdl->screen[needle->numcol]));
}

uint32_t				pixel_txtr(t_arch *arch, t_needle *needle)
{
	(void)arch;
	return (needle->txtr->pixels[needle->txtr_col]);
}

/*
**	rend une colonne de texture
**	-numcol le numero de la colonne
**	-surface la taille de la surface a rendre le debut et la fin
**	-txtr la texture a rendre
**	-txtr_col la colonne de pixels dans la texture
*/

int						draw_txtr_column(t_arch *a, t_needle *ne
	, uint32_t (*pixel_effector)(t_arch*, t_needle*))
{
	if (ne->surface.y < (int)a->portal.b_up[a->px.x])
		return (a->px.x + a->portal.b_up[a->px.x] * a->sdl->size.x);
	if (ne->surface.x < (int)a->portal.b_up[a->px.x])
		needle_reajust2(ne, a->portal.b_up[a->px.x]);
	while (ne->surface.x < ne->surface.y
		&& ne->surface.x < (int)a->portal.b_down[a->px.x])
	{
		if (ne->numcol < a->sdl->size.x * a->sdl->size.y
			&& ne->txtr_col < ne->txtr->w * ne->txtr->h)
			a->sdl->screen[ne->numcol] = pixel_effector(a, ne);
		needle_indent_down(ne, a);
		needle_buff_affect(ne);
	}
	return (ne->numcol);
}

int						draw_txtr_column_prop(t_arch *a, t_needle *n
	, t_vct2 limit)
{
	if (n->surface.y < (int)a->portal.b_up[a->px.x])
		return (a->px.x + a->portal.b_up[a->px.x] * a->sdl->size.x);
	if (n->surface.x < limit.x)
		needle_reajust(a, n, limit.x);
	else if (n->surface.x < (int)a->portal.b_up[a->px.x])
		needle_reajust(a, n, a->portal.b_up[a->px.x]);
	while (n->surface.x < n->surface.y
		&& n->surface.x < (int)a->portal.b_down[a->px.x]
		&& n->surface.x < limit.y)
	{
		if (n->numcol < a->sdl->size.x * a->sdl->size.y
			&& n->txtr_col < n->txtr->w * n->txtr->h)
			a->sdl->screen[n->numcol] = opacity(a->sdl->screen[n->numcol],
				n->txtr->pixels[n->txtr_col],
				1 - (unsigned char)(n->txtr->pixels[n->txtr_col]) / 255.0);
		needle_indent_down(n, a);
		needle_buff_affect(n);
	}
	return (n->numcol);
}

/*
**	on recupere la largeur de la texture a l'ecran a partir
**		de ses dimensions de base et de
**	sa hauteur a l'ecran
**	on ajoute sa position x, colonne du millieu de texture
*/

t_vct2					txtr_width(t_txtr *texture, t_vct2 surface, int posx)
{
	t_vct2		width;

	width.x = (((surface.y - surface.x) / (double)texture->h) * texture->w) / 2;
	width.y = posx + width.x;
	width.x = posx - width.x;
	return (width);
}
