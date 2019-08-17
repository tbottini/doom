/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:32:34 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/17 14:59:13 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int				draw_txtr_column(t_arch *arch, int numcol, t_vct2 surface, t_txtr *txtr, uint32_t px)
{
	double		coef;
	double		buff;

	buff = 0;
	coef = (double)txtr->h / (surface.y - surface.x);
	if (surface.y < (int)arch->portal.b_up[arch->px.x])
		return (arch->px.x);
	if (surface.x < (int)arch->portal.b_up[arch->px.x])
	{
		buff = (-surface.x + arch->portal.b_up[arch->px.x]) * coef;
		if (buff > 1.0)
		{
			px += (int)buff * txtr->w;
			buff = buff - (int)buff;
		}
		surface.x = arch->portal.b_up[arch->px.x];
	}
	while (surface.x < surface.y && surface.x < (int)arch->portal.b_down[arch->px.x])
	{
		arch->sdl->screen[numcol] = txtr->pixels[px];
		surface.x++;
		numcol += arch->sdl->size.x;
		buff += coef;
		if (buff > 1.0)
		{
			px += (int)buff * txtr->w;
			buff = buff - (int)buff;
		}
	}
	return (numcol);
}

int				draw_part_texture(t_arch *arch, int numcol, t_vct2 surface, t_txtr *txtr)
{
	uint32_t 	px;

	px = texture_interpolation2d(arch, txtr);
	return (draw_txtr_column(arch, numcol, surface, txtr, px));
}

int				draw_part_prop(t_arch *arch, int numcol, t_vct2 surface, t_prop *prop)
{
	uint32_t	px;

	px = texture_prop_interpolation2d(arch, &prop->tex, prop);
	return (draw_txtr_column(arch, numcol, surface, &prop->tex, px));
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
	uint32_t	px_txtr;
	double		percent_wall;
	double		percent_txtr;

	percent_wall = percent_interpolation2d(arch);
	percent_txtr = 2 - percent_wall - render_stuff->perc_open;
	if (percent_txtr > 1)
		percent_txtr = 1;
	else if (percent_txtr < 0)
		percent_txtr = 0;
	px_txtr = percent_txtr * arch->wall->txtr.w;
	return (draw_txtr_column(arch, numcol, surface, &arch->wall->txtr,
		px_txtr));
}

/*
**	on donne la surface(sans le facteur largeur)
**	on convertit la valeur
**	on la trunc
*/

double			draw_part(t_arch *arch, t_vct2 surface, uint32_t color)
{
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
