/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 21:03:08 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/12 14:08:39 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "debug.h"

int		draw_part_texture(t_arch *arch, int numcol, t_vct2 surface, t_txtr *txtr)
{
	double		coef;
	uint32_t	px;
	double		buff;

	px = texture_interpolation2d(arch, txtr);
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
	if (surface.x >= (int)arch->portal.b_down[arch->px.x])
	{
		return (arch->portal.b_down[arch->px.x] * arch->sdl->size.x + arch->px.x);
	}
	else if (surface.y <= (int)arch->portal.b_up[arch->px.x])
	{
		return (arch->portal.b_up[arch->px.x] * arch->sdl->size.x + arch->px.x);
	}
	if (surface.x <= (int)arch->portal.b_up[arch->px.x])
		surface.x = arch->px.x + arch->portal.b_up[arch->px.x] * arch->sdl->size.x;
	else
		surface.x = surface.x * arch->sdl->size.x + arch->px.x;
	if (surface.y > (int)arch->portal.b_down[arch->px.x])
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

void		draw_column(t_arch *arch, t_fvct2 surface)
{
	double	cursor;
	t_vct2	surface_tmp;

	surface_tmp = (t_vct2){arch->portal.b_up[arch->px.x], surface.x};
	cursor = draw_part(arch, surface_tmp, 0);
	surface_tmp = (t_vct2){surface.x, surface.y};
	draw_part_texture(arch, cursor, surface_tmp, &arch->wall->txtr);
	surface_tmp = (t_vct2){surface.y, arch->portal.b_down[arch->px.x]};
	draw_part(arch, surface_tmp, 0x272130ff);
}

/*
**	calcul la surface du portail selon la hauteur du prochain secteur
**	on calcul le pourcentage de hauteur du prochain secteur (pour le plafond puis pour le sol)
**	on fait le rapport avec la surface du mur
**	si la surface du portail est plus grand que la suface du mur on la tronque
**	-->renvoie sans le facteur largeur (arch->sdl->size.x)
*/
t_fvct2		surface_portal(t_fvct2 surface, t_sector *parent, t_sector *child)
{
	t_fvct2	s_portal;

	s_portal.y = (child->h_floor - parent->h_floor) / parent->h_ceil;
	s_portal.x = (child->h_floor - parent->h_floor + child->h_ceil) / parent->h_ceil;
	s_portal.y = surface.y - s_portal.y * (surface.y - surface.x);
	s_portal.x = surface.y - s_portal.x * (surface.y - surface.x);
	if (s_portal.x < surface.x)
		s_portal.x = surface.x;
	if (s_portal.y > surface.y)
		s_portal.y = surface.y;
	return (s_portal);
}


/*
**	on determine la surface du portail
**	on dessine : le ciel, la liaison haute du mur, le portail, la liaison basse, le sol
**	on prepare la recursivite avec les borne, tout en sauvegardant les actuelles configuration
**		dans parent borne
*/
void		draw_portal(t_arch *arch, t_fvct2 surface, t_borne *parent_borne, int start)
{
	t_fvct2		s_portal;
	t_vct2		surf;
	t_vct2		tmp;

	s_portal = surface_portal(surface, arch->sector, arch->wall->link);

	tmp = (t_vct2){arch->portal.b_up[arch->px.x], surface.x};
	surf.x = draw_part(arch, tmp, 0);
	tmp = (t_vct2){surface.x, s_portal.x};
	surf.x = draw_part_texture(arch, surf.x, tmp, &arch->wall->txtr);
	tmp = (t_vct2){s_portal.x, s_portal.y};
	surf.x = draw_part(arch, tmp, ORANGE);
	tmp = (t_vct2){s_portal.y, surface.y};
	surf.x = draw_part_texture(arch, surf.x, tmp, &arch->wall->txtr);
	tmp = (t_vct2){surface.y, arch->portal.b_down[arch->px.x]};
	draw_part(arch, tmp, 0x272130ff);
	parent_borne->b_up[arch->px.x - start] = arch->portal.b_up[arch->px.x];
	parent_borne->b_down[arch->px.x - start] = arch->portal.b_down[arch->px.x];

	tmp = (t_vct2){s_portal.x, s_portal.y};
	set_borne_vertical(arch, tmp, arch->px.x);
}
