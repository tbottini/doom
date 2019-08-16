/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 21:03:08 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/13 03:00:58 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void				rectif_buff_txtr(double *buff, uint32_t *px, int txtr_w)
{
	if (*buff > 1.0)
	{
		*px += (int)*buff * txtr_w;
		*buff = *buff - (int)*buff;
	}
}

uint32_t			opacity_pixel(t_arch *arch, t_prop *prop, int px
	, int numcol)
{
	return (opacity(arch->sdl->screen[numcol],
			prop->tex.pixels[px],
			1 - (unsigned char)(prop->tex.pixels[px]) / 255.0));
}

int					draw_part_texture(t_arch *arch, int numcol, t_vct2 surface
	, t_txtr *txtr)
{
	double			coef;
	uint32_t		px;
	double			buff;

	px = texture_interpolation2d(arch, txtr);
	buff = 0;
	coef = (double)txtr->h / (surface.y - surface.x);
	if (surface.y < (int)arch->portal.b_up[arch->px.x])
		return (numcol + surface.y * arch->sdl->size.x);
	if (surface.x < (int)arch->portal.b_up[arch->px.x])
	{
		buff = (-surface.x + arch->portal.b_up[arch->px.x]) * coef;
		rectif_buff_txtr(&buff, &px, txtr->w);
		surface.x = arch->portal.b_up[arch->px.x];
	}
	while (surface.x < surface.y
		&& surface.x < (int)arch->portal.b_down[arch->px.x])
	{
		arch->sdl->screen[numcol] = txtr->pixels[px];
		surface.x++;
		numcol += arch->sdl->size.x;
		buff += coef;
		rectif_buff_txtr(&buff, &px, txtr->w);
	}
	return (numcol);
}

int					draw_part_prop(t_arch *arch, int numcol, t_vct2 surface
	, t_prop *prop)
{
	double			coef;
	uint32_t		px;
	double			buff;

	px = texture_prop_interpolation2d(arch, &prop->tex, prop);
	buff = 0;
	coef = (double)prop->tex.h / (surface.y - surface.x);
	if (surface.y < (int)arch->portal.b_up[arch->px.x])
		return (numcol + surface.y * arch->sdl->size.x);
	if (surface.x < (int)arch->portal.b_up[arch->px.x])
	{
		buff = (-surface.x + arch->portal.b_up[arch->px.x]) * coef;
		rectif_buff_txtr(&buff, &px, prop->tex.w);
		surface.x = arch->portal.b_up[arch->px.x];
	}
	while (surface.x < surface.y && surface.x
		< (int)arch->portal.b_down[arch->px.x])
	{
		arch->sdl->screen[numcol] = opacity_pixel(arch, prop, px, numcol);
		surface.x++;
		numcol += arch->sdl->size.x;
		buff += coef;
		rectif_buff_txtr(&buff, &px, prop->tex.w);
	}
	return (numcol);
}

/*
**	calcul la surface du portail selon la hauteur du prochain secteur
**	on calcul le pourcentage de hauteur du prochain secteur
**	(pour le plafond puis pour le sol)
**	on fait le rapport avec la surface du mur
**	si la surface du portail est plus grand que la suface du mur on la tronque
**	-->renvoie sans le facteur largeur (arch->sdl->size.x)
*/

t_fvct2				surface_portal(t_fvct2 surface, t_sector *parent,
	t_sector *child)
{
	t_fvct2			s_portal;

	s_portal.y = (child->h_floor - parent->h_floor) / parent->h_ceil;
	s_portal.x = (child->h_floor - parent->h_floor + child->h_ceil)
		/ parent->h_ceil;
	s_portal.y = surface.y - s_portal.y * (surface.y - surface.x);
	s_portal.x = surface.y - s_portal.x * (surface.y - surface.x);
	if (s_portal.x < surface.x)
		s_portal.x = surface.x;
	if (s_portal.y > surface.y)
		s_portal.y = surface.y;
	return (s_portal);
}
