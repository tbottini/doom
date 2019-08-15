/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:32:34 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/15 19:09:02 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int		draw_part_texture(t_arch *arch, int numcol, t_vct2 surface, t_txtr *txtr)
{
	double		coef;
	uint32_t	px;
	double		buff;

	px = texture_interpolation2d(arch, txtr);
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


int		draw_part_prop(t_arch *arch, int numcol, t_vct2 surface, t_prop *prop)
{
	double		coef;
	uint32_t	px;
	double		buff;
	t_txtr		*txtr;

	txtr = &prop->tex;
	px = texture_prop_interpolation2d(arch, txtr, prop);
	buff = 0;
	coef = (double)txtr->h / (surface.y - surface.x);
	if (surface.y < (int)arch->portal.b_up[arch->px.x])
		return (numcol + surface.y * arch->sdl->size.x);
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
		arch->sdl->screen[numcol] =
			opacity(arch->sdl->screen[numcol],
			txtr->pixels[px],
			1 - (unsigned char)(txtr->pixels[px]) / 255.0);
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

/*
**	on donne la surface(sans le facteur largeur)
**	on convertit la valeur
**	on la trunc
*/

double		draw_part(t_arch *arch, t_vct2 surface, uint32_t color)
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
