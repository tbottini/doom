/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 01:21:12 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/13 07:36:14 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
**	renvoie la surface en pixels d'un pillier
**	params : la hauteur du joueur (player)
**	de la hauteur du mur (wall_height)
**	et de la distance par rapport au mur (depth)
**	up est la difference entre le point de vue de la camera
**		et le haut du mur
*/

t_fvct2			surface_pillar(t_arch *arch, t_player *player
	, t_fvct2 len_sector, double depth)
{
	t_fvct2		wall_portion;

	wall_portion.x = px_point(arch, player, len_sector.x, depth);
	wall_portion.y = px_point(arch, player, len_sector.y, depth);
	return (wall_portion);
}

/*
**	rearrange les parametre pour que l'on rende les colonnes de gauche a droite
*/

void			reorder(t_arch *arch)
{
	double		tmp;
	int			tmpint;
	t_fvct2		pillar_tmp;

	if (arch->px.x > arch->px.y)
	{
		tmpint = arch->px.x;
		arch->px.x = arch->px.y;
		arch->px.y = tmpint;
		pillar_tmp = arch->pillar;
		arch->pillar = arch->next;
		arch->next = pillar_tmp;
		tmp = arch->shift_txtr.x;
		arch->shift_txtr.x = arch->shift_txtr.y;
		arch->shift_txtr.y = tmp;
	}
}

void			render_surface(t_arch *arch, t_player *player)
{
	t_fvct2		pillar_px[2];
	t_fvct2		len_sector;
	t_borne		borne_tmp;
	t_vct2		px_draw;

	reorder(arch);
	len_sector = length_sector(player, arch->sector);
	pillar_px[0] = surface_pillar(arch, player, len_sector, arch->pillar.x);
	pillar_px[1] = surface_pillar(arch, player, len_sector, arch->next.x);
	prop_iter_v(arch->wall->props, arch->wall->nb_props,
		&prop_init_render, arch);
	if (arch->wall->status == PORTAL)
	{
		borne_svg(arch, &borne_tmp);
		px_draw = arch->px;
	}
	pillar_to_pillar(arch, &pillar_px[0], &pillar_px[1], &borne_tmp);
	if (arch->wall->status == PORTAL)
	{
		arch->px.x = px_draw.x;
		if (arch->wall->link != arch->sector)
			render_recursive(arch, player);
		borne_load(arch, &borne_tmp, px_draw);
	}
}

/*
**	on recupere les info du pillier
**	on regarde si le mur est derriere le portail ou non
**	on reorder les info du portail
**	on rend la surface
*/

void			render_wall(t_arch *arch, t_player *player)
{
	pillar_screen_info(arch, player);
	if (arch->depth_portal == 0 || (wall_behind_portal(arch)))
	{
		if (arch->wall->status == CLOSE_DOOR
			|| arch->wall->status == OPEN_DOOR)
		{
			door_split(arch, player, arch->wall->status);
			return ;
		}
		render_surface(arch, player);
	}
}

void			render_recursive(t_arch *arch, t_player *player)
{
	t_sector	*sector_tmp;

	set_borne_horizontal(arch);
	arch->portal.pillar = arch->pillar;
	arch->portal.next = arch->next;
	sector_tmp = arch->sector;
	arch->depth_portal++;
	sector_render(arch, player, arch->wall->link);
	arch->depth_portal--;
	arch->sector = sector_tmp;
}
