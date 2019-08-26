/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 21:03:08 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 14:24:49 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void			draw_wall(t_arch *arch, t_pil_render *rendr)
{
	double		cursor;
	t_vct2		surface_tmp;

	surface_tmp = (t_vct2){arch->portal.b_up[arch->px.x]
		, rendr->pillar.x};
	cursor = draw_part(arch, surface_tmp.x, surface_tmp.y, 0);
	surface_tmp = (t_vct2){rendr->pillar.x, rendr->pillar.y};
	draw_part_texture(arch, cursor, surface_tmp);
	surface_tmp = (t_vct2){rendr->pillar.y
		, arch->portal.b_down[arch->px.x]};
	draw_part(arch, surface_tmp.x, surface_tmp.y, 0x272130ff);
}

/*
**	calcul la surface du portail selon la hauteur du prochain secteur
**	on calcul le pourcentage de hauteur du prochain secteur
**	(pour le plafond puis pour le sol)
**	on fait le rapport avec la surface du mur
**	si la surface du portail est plus grand que la suface du mur on la tronque
**	-->renvoie sans le facteur largeur (arch->sdl->size.x)
*/

t_fvct2			surface_portal(t_fvct2 surface, t_sector *parent
	, t_sector *child)
{
	t_fvct2		s_portal;

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

/*
**	on determine la surface du portail
**	on dessine : le ciel, la liaison haute du mur, le portail, la liaison
**	basse, le sol
**	on prepare la recursivite avec les borne, tout en sauvegardant
**	les actuelles configuration
**		dans parent borne
**	surface = la surface du mur a rendre
*/

void			draw_portal(t_arch *arch, t_pil_render *rendr)
{
	t_fvct2		portal;
	int			cur;
	t_vct2		tmp;
	t_fvct2		surface;

	surface = rendr->pillar;
	portal = surface_portal(surface, arch->sector, arch->wall->link);
	cur = draw_part(arch, arch->portal.b_up[arch->px.x], surface.x, 0);
	if (portal.y < surface.x)
	{
		tmp = (t_vct2){surface.x, surface.y};
		cur = draw_part_texture(arch, cur, tmp);
	}
	else
	{
		cur = draw_part_texture(arch, cur, (t_vct2){surface.x, portal.x});
		cur = draw_part(arch, portal.x, portal.y, 0);
		cur = draw_part_texture(arch, cur, (t_vct2){portal.y, surface.y});
	}
	draw_part(arch, surface.y, arch->portal.b_down[arch->px.x], 0x272130ff);
	borne_svg_vertical(arch, rendr, portal);
}

void			draw_door(t_arch *arch, t_pil_render *rendr, int flag)
{
	t_fvct2		mid_part;
	int			cur;
	t_vct2		tmp;
	t_fvct2		sface;

	sface = rendr->pillar;
	mid_part = surface_portal(sface, arch->sector, arch->wall->link);
	cur = draw_part(arch, arch->portal.b_up[arch->px.x], sface.x, 0);
	if (sface.y < sface.x)
		cur = draw_part_texture(arch, cur, (t_vct2){sface.x, sface.y});
	else
	{
		cur = draw_part_texture(arch, cur, (t_vct2){sface.x, mid_part.x});
		tmp = (t_vct2){mid_part.x, mid_part.y};
		if (flag == PORTAL)
			cur = draw_part(arch, tmp.x, tmp.y, 0);
		else if (flag == WALL)
			cur = draw_part_decal(arch, cur, tmp, rendr);
		cur = draw_part_texture(arch, cur, (t_vct2){mid_part.y, sface.y});
	}
	draw_part(arch, sface.y, arch->portal.b_down[arch->px.x], 0x272130ff);
	if (flag == PORTAL)
		borne_svg_vertical(arch, rendr, mid_part);
}

void			draw_window(t_arch *arch, t_pil_render *rendr)
{
	t_fvct2		mid_part;
	t_vct2		surface_tmp;
	int			cursor;

	mid_part = surface_portal(rendr->pillar, arch->sector
		, arch->wall->link);
	if (mid_part.x < arch->portal.b_up[arch->px.x])
		cursor = arch->px.x + arch->portal.b_up[arch->px.x]
			* arch->sdl->size.x;
	else if (mid_part.x > arch->portal.b_down[arch->px.x])
		return ;
	else
		cursor = arch->px.x + (int)mid_part.x * arch->sdl->size.x;
	surface_tmp = (t_vct2){mid_part.x, mid_part.y};
	draw_part_opacity(arch, cursor, surface_tmp, &arch->wall->txtr);
}
