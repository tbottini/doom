/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 21:03:08 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/13 03:00:58 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
**	on donne la surface(sans le facteur largeur)
**	on convertit la valeur
**	on la trunc
*/

double			draw_part(t_arch *arch, t_vct2 surface, uint32_t color)
{
	if (surface.x >= (int)arch->portal.b_down[arch->px.x])
		return (arch->portal.b_down[arch->px.x] * arch->sdl->size.x
			+ arch->px.x);
	else if (surface.y <= (int)arch->portal.b_up[arch->px.x])
	{
		return (arch->portal.b_up[arch->px.x] * arch->sdl->size.x
			+ arch->px.x);
	}
	if (surface.x <= (int)arch->portal.b_up[arch->px.x])
		surface.x = arch->px.x + arch->portal.b_up[arch->px.x]
			* arch->sdl->size.x;
	else
		surface.x = surface.x * arch->sdl->size.x + arch->px.x;
	if (surface.y > (int)arch->portal.b_down[arch->px.x])
		surface.y = arch->px.x + (arch->portal.b_down[arch->px.x] - 1)
			* arch->sdl->size.x;
	else
		surface.y = surface.y * arch->sdl->size.x;
	while (surface.x < surface.y)
	{
		arch->sdl->screen[surface.x] = color;
		surface.x += arch->sdl->size.x;
	}
	return (surface.x);
}

void			draw_column(t_arch *arch, t_fvct2 surface)
{
	double			cursor;
	t_vct2			surface_tmp;

	surface_tmp = (t_vct2){arch->portal.b_up[arch->px.x], surface.x};
	cursor = draw_part(arch, surface_tmp, 0);
	surface_tmp = (t_vct2){surface.x, surface.y};
	draw_part_texture(arch, cursor, surface_tmp, &arch->wall->txtr);
	surface_tmp = (t_vct2){surface.y, arch->portal.b_down[arch->px.x]};
	draw_part(arch, surface_tmp, 0x272130ff);
}

/*
**	on determine la surface du portail
**	on dessine : le ciel, la liaison haute du mur, le portail,
**	 	la liaison basse, le sol
**	on prepare la recursivite avec les borne, tout en sauvegardant
**		les actuelles configuration
**		dans parent borne
*/

void			draw_portal(t_arch *arch, t_fvct2 surface,
	t_borne *parent_borne, int start)
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
