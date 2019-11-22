/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 01:52:58 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 14:27:16 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
**	fait des coeficient pour rendre les colomnes entre les deux pilier
**	et si c'est un portail prepare
**		-sauvegarde la borne actuel dans borne_tmp
**		-la borne pour la recursivite arch->portal
**		-recharge borne_tmp dans arch->portal
**	on rend le pillier avec la method de rendu associe au status
**		de la surface
*/

void				pillar_to_pillar(t_arch *arch, t_pil_render *stuff)
{
	t_fvct2			neutre;
	t_fvct2			coef_surface;
	double			coef_neutre;
	double			coef_distance;
	double			dist_px;

	coef_surface.x = coef_diff(stuff->pillar.x - stuff->next.x, arch->px);
	coef_surface.y = coef_diff(stuff->pillar.y - stuff->next.y, arch->px);
	neutre.x = (double)(arch->sdl->size.y) / arch->pillar.x;
	neutre.y = (double)(arch->sdl->size.y) / arch->next.x;
	coef_neutre = coef_vct(neutre, arch->px);
	coef_distance = (arch->next.x - arch->pillar.x)
		/ (arch->px.y - arch->px.x);
	dist_px = arch->pillar.x;
	while (arch->px.x < arch->px.y)
	{
		borne_secur(arch);
		arch->render_method[arch->wall->status](arch, stuff, neutre.x);
		stuff->pillar.x -= coef_surface.x;
		stuff->pillar.y -= coef_surface.y;
		neutre.x += coef_neutre;
		arch->px.x++;
		dist_px += coef_distance;
	}
}

/*
**	preparatif de rendu avant le pillar to pillar
**	on set les bornes pour la recursivite si ya un portail
**	on recupere les info pour les door si la surface est de ce type
**	on recupere les info pour les props
**	on recupere les info pour les surface pillar et next
*/

void				render_surface(t_arch *a, t_player *player)
{
	t_fvct2			len_sector;
	t_vct2			px_draw;
	t_pil_render	stuff;

	if (is_door(a))
		door_split_info(a, &stuff, a->wall->status);
	reorder(a);
	len_sector = length_sector(player, a->sector);
	stuff.pillar = surface_pillar(a, player, len_sector, a->pillar.x);
	stuff.next = surface_pillar(a, player, len_sector, a->next.x);
	prop_iter_v(a->wall->props, a->wall->nb_props, &prop_init_render, a);
	if (a->wall->status == PORTAL || is_door(a))
	{
		save_pixels_portal(a, &stuff, &px_draw);
		stuff.px_start = px_draw.x;
		borne_svg(a, &stuff.borne_tmp, px_draw);
	}
	pillar_to_pillar(a, &stuff);
	if ((a->wall->status == PORTAL || is_door(a))
		&& (px_draw.x < px_draw.y))
	{
		if (a->depth_portal < PORTAL_MAX)
			render_recursivite(a, player, px_draw);
		borne_load(a, &stuff.borne_tmp, px_draw);
	}
}

void				arch_window_info_load(t_arch *arch, t_fvct2 *info
	, t_vct2 px)
{
	arch->px = px;
	arch->pillar = info[0];
	arch->next = info[1];
	arch->shift_txtr = info[2];
}

/*
**	on recupere les info du pillier
**	on regarde si le mur est derriere le portail ou non
**	on reorder les info du portail
**	on rend la surface
*/

void				render_wall(t_arch *arch, t_player *player)
{
	t_fvct2			info[3];
	t_vct2			px;
	t_txtr			tmp;

	pillar_screen_info(arch, player);
	if (arch->depth_portal == 0 || (wall_behind_portal(arch)))
	{
		if (arch->wall->status == WINDOW)
		{
			info[0] = arch->pillar;
			info[1] = arch->next;
			info[2] = arch->shift_txtr;
			px = arch->px;
			tmp = arch->wall->txtr;
			arch->wall->txtr = arch->sector->txtrsol;
			arch->wall->status = PORTAL;
			render_surface(arch, player);
			arch->wall->txtr = tmp;
			arch->wall->status = WINDOW;
			arch_window_info_load(arch, info, px);
		}
		render_surface(arch, player);
	}
}
