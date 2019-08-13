/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 01:21:12 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/13 04:11:19 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
**	renvoie la position en pixel d'un point
**	wall_angle est l'angle du point par rapport au joueur
*/

int			px_point(t_arch *arch, t_player *player, double h_diff
	, double depth)
{
	double	wall_angle;
	int		px;
	double	player_angle;

	player_angle = (player->stat.rot.x - 90) * PI180;
	wall_angle = atan2(h_diff, depth);
	px = arch->sdl->size.y / 2 - tan(wall_angle) * arch->cam->d_screen;
	px += (player->stat.rot.x - 90) * 15.5;
	return (px);
}

/*
**	calcul la taille du secteur par rapport au joueur
**	length.x = up
**	length.y = down
*/

t_fvct2		length_sector(t_player *player, t_sector *sector)
{
	t_fvct2	length;

	length.y = -player->stat.height - (player->stat.pos.z - sector->h_floor);
	length.x = length.y + sector->h_ceil;
	return (length);
}

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

/*
**	fait des coeficient pour rendre les colomnes entre les deux pilier
**	et si c'est un portail prepare
**		-sauvegarde la borne actuel dans borne_tmp
**		-la borne pour la recursivite arch->portal
**		-recharge borne_tmp dans arch->portal
*/


//une strucutre
typedef	struct		s_cursor
{
	t_fvct2			c_surface;
	double			c_neutre;
	double			c_dist;
	t_fvct2			*surface;
	double			dist_px;
	double			neutre;
}					t_cursor;

t_cursor			init_cursor_dir_pillar(t_arch *arch, t_fvct2 *pillar, t_fvct2 *next)
{
	t_cursor		cursor;
	t_fvct2			neutre;

	cursor.c_surface.x = coef_diff(pillar->x - next->x, arch->px);
	cursor.c_surface.y = coef_diff(pillar->y - next->y, arch->px);
	neutre.x = (double)(arch->sdl->size.y) / arch->pillar.x;
	neutre.y = (double)(arch->sdl->size.y) / arch->next.x;
	cursor.neutre = neutre.x;
	cursor.c_neutre = coef_vct(neutre, arch->px);
	cursor.c_dist = (arch->next.x - arch->pillar.x) / (arch->px.y - arch->px.x);
	cursor.dist_px = arch->pillar.x;
	cursor.surface = pillar;
	return (cursor);
}


void			pillar_to_pillar(t_arch *arch, t_fvct2 *pillar, t_fvct2 *next
	, t_borne *borne_tmp)
{
   	t_fvct2		neutre;
   	t_fvct2		coef_surface;
	double		coef_neutre;
	int			start;
	double		coef_distance;

	t_cursor	curs;

	start = arch->px.x;
	coef_surface.x = coef_diff(pillar->x - next->x, arch->px);
	coef_surface.y = coef_diff(pillar->y - next->y, arch->px);
	neutre.x = (double)(arch->sdl->size.y) / arch->pillar.x;
	neutre.y = (double)(arch->sdl->size.y) / arch->next.x;
	coef_neutre = coef_vct(neutre, arch->px);
	coef_distance = (arch->next.x - arch->pillar.x) / (arch->px.y - arch->px.x);

	curs = init_cursor_dir_pillar(arch, pillar, next);

	while (arch->px.x != arch->px.y)
	{
		if (arch->portal.b_up[arch->px.x] > (uint32_t)arch->sdl->size.y)
			arch->portal.b_up[arch->px.x] = arch->sdl->size.y - 1;
		if (arch->portal.b_down[arch->px.x] > (uint32_t)arch->sdl->size.y)
			arch->portal.b_down[arch->px.x] = arch->sdl->size.y - 1;
		if (arch->wall->status == WALL)
		{
			if (z_line_buffer(arch, curs.neutre, arch->px.x))
			{
				draw_column(arch, *pillar);
				props_draw_column(arch->wall->props, arch, *pillar);
			}
		}
		else if (arch->wall->status == PORTAL)
		{
			if (zline_portal(arch, borne_tmp->zline, curs.neutre, start))
			{
				draw_portal(arch, *pillar, borne_tmp, start);
			}
		}
		curs.surface->x -= coef_surface.x;
		curs.surface->y -= coef_surface.y;
		curs.neutre += coef_neutre;
		arch->px.x++;
	}
}

void			render_surface(t_arch *arch, t_player *player)
{
	t_fvct2		pillar_px;
	t_fvct2		next_px;
	t_fvct2		len_sector;
	t_borne		borne_tmp;
	t_sector	*sector_tmp;
	t_vct2		px_draw;

	len_sector = length_sector(player, arch->sector);
	pillar_px = surface_pillar(arch, player, len_sector, arch->pillar.x);
	next_px = surface_pillar(arch, player, len_sector, arch->next.x);
	prop_iter_v(arch->wall->props, arch->wall->nb_props, &prop_init_render, arch);
	if (arch->wall->status == PORTAL)
	{
		borne_svg(arch, &borne_tmp);
		px_draw = arch->px;
	}
	pillar_to_pillar(arch, &pillar_px, &next_px, &borne_tmp);
	if (arch->wall->status == PORTAL)
	{
		arch->px.x = px_draw.x;
		set_borne_horizontal(arch);
		arch->portal.pillar = arch->pillar;
		arch->portal.next = arch->next;
		sector_tmp = arch->sector;
		arch->depth_portal++;
		sector_render(arch, player, arch->wall->link);
		arch->depth_portal--;
		arch->sector = sector_tmp;
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
		if (arch->wall->status == CLOSE_DOOR || arch->wall->status == OPEN_DOOR)
		{
			door_split(arch, player, arch->wall->status);
			return ;
		}
		reorder(arch);
		render_surface(arch, player);
	}
}
