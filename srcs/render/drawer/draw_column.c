/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 21:03:08 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/19 15:49:43 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "debug.h"

void		draw_wall(t_arch *arch, t_pil_render *render_stuff)
{
	double	cursor;
	t_vct2	surface_tmp;

	surface_tmp = (t_vct2){arch->portal.b_up[arch->px.x], render_stuff->pillar.x};
	cursor = draw_part(arch, surface_tmp.x, surface_tmp.y, 0);
	surface_tmp = (t_vct2){render_stuff->pillar.x, render_stuff->pillar.y};
	draw_part_texture(arch, cursor, surface_tmp, &arch->wall->txtr);
	surface_tmp = (t_vct2){render_stuff->pillar.y, arch->portal.b_down[arch->px.x]};
	draw_part(arch, surface_tmp.x, surface_tmp.y, 0x272130ff);
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
**	on dessine : le ciel, la liaison haute du mur, le portail, la liaison
**	basse, le sol
**	on prepare la recursivite avec les borne, tout en sauvegardant
**	les actuelles configuration
**		dans parent borne
**	surface = la surface du mur a rendre
*/

void		draw_portal(t_arch *arch, t_pil_render *render_stuff)
{
	t_fvct2		s_portal;
	t_vct2		surf;
	t_vct2		tmp;
	t_borne		*p_borne;
	t_fvct2		surface;

	p_borne = &render_stuff->borne_tmp;
	surface = render_stuff->pillar;
	s_portal = surface_portal(surface, arch->sector, arch->wall->link);
	surf.x = draw_part(arch, arch->portal.b_up[arch->px.x], surface.x, 0);
	if (s_portal.y < surface.x)
	{
		tmp = (t_vct2){surface.x, surface.y};
		surf.x = draw_part_texture(arch, surf.x, tmp, &arch->wall->txtr);
	}
	else
	{
		tmp = (t_vct2){surface.x, s_portal.x};
		surf.x = draw_part_texture(arch, surf.x, tmp, &arch->wall->txtr);
		surf.x = draw_part(arch, s_portal.x, s_portal.y, BLUE_SOFT);
		tmp = (t_vct2){s_portal.y, surface.y};
		surf.x = draw_part_texture(arch, surf.x, tmp, &arch->wall->txtr);
	}
	draw_part(arch, surface.y, arch->portal.b_down[arch->px.x], 0x272130ff);
	p_borne->b_up[arch->px.x - render_stuff->px_start] = arch->portal.b_up[arch->px.x];
	p_borne->b_down[arch->px.x - render_stuff->px_start] = arch->portal.b_down[arch->px.x];
	tmp = (t_vct2){s_portal.x, s_portal.y};
	set_borne_vertical(arch, tmp, arch->px.x);
}

void		draw_door(t_arch *arch, t_pil_render *render_stuff, int flag)
{
	t_fvct2		mid_part;
	t_vct2		surf;
	t_vct2		tmp;
	t_borne		*p_borne;
	t_fvct2		surface;

	p_borne = &render_stuff->borne_tmp;
	surface = render_stuff->pillar;
	mid_part = surface_portal(surface, arch->sector, arch->wall->link);
	surf.x = draw_part(arch, arch->portal.b_up[arch->px.x], surface.x, 0);
	if (arch->px.x == arch->sdl->size.x / 2)
		printf("surf.x %d\n", surf.x);
	if (surface.y < surface.x)
	{
		tmp = (t_vct2){surface.x, surface.y};
		surf.x = draw_part_texture(arch, surf.x, tmp, &arch->wall->txtr);
		printf("secteur trop haut\n");
	}
	else
	{
		tmp = (t_vct2){surface.x, mid_part.x};
		surf.x = draw_part_texture(arch, surf.x, tmp, &arch->wall->txtr);
		if (arch->px.x == arch->sdl->size.x / 2)
			printf("surf.x out txtr %d\n", surf.x);
		tmp = (t_vct2){mid_part.x, mid_part.y};
		if (flag == PORTAL)
			surf.x = draw_part(arch, tmp.x, tmp.y, ORANGE);
		else if (flag == WALL)
			surf.x = draw_part_decal(arch, surf.x, tmp, render_stuff);
		tmp = (t_vct2){mid_part.y, surface.y};
		surf.x = draw_part_texture(arch, surf.x, tmp, &arch->wall->txtr);
	}
	draw_part(arch, surface.y, arch->portal.b_down[arch->px.x], 0x272130ff);
	if (flag == PORTAL)
	{
		p_borne->b_up[arch->px.x - render_stuff->px_start] = arch->portal.b_up[arch->px.x];
		p_borne->b_down[arch->px.x - render_stuff->px_start] = arch->portal.b_down[arch->px.x];
		tmp = (t_vct2){mid_part.x, mid_part.y};
		set_borne_vertical(arch, tmp, arch->px.x);
	}
}
