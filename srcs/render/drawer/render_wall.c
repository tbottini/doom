/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 01:21:12 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/13 07:36:14 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
**	renvoie la position en pixel d'un point
**	wall_angle est l'angle du point par rapport au joueur
*/

int				px_point(t_arch *arch, t_player *player, double h_diff
	, double depth)
{
	double		wall_angle;
	int			px;
	double		player_angle;

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

t_fvct2			length_sector(t_player *player, t_sector *sector)
{
	t_fvct2		length;

	length.y = -player->stat.height - (player->stat.pos.z - sector->h_floor);
	length.x = length.y + sector->h_ceil;
	return (length);
}

/*
**	fait des coeficient pour rendre les colomnes entre les deux pilier
**	et si c'est un portail prepare
**		-sauvegarde la borne actuel dans borne_tmp
**		-la borne pour la recursivite arch->portal
**		-recharge borne_tmp dans arch->portal
*/

t_cursor		init_cursor_dir_pillar(t_arch *arch, t_fvct2 *pillar,
	t_fvct2 *next)
{
	t_cursor	cursor;
	t_fvct2		neutre;

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

void			cursor_increment(t_cursor *cursor)
{
	cursor->surface->x -= cursor->c_surface.x;
	cursor->surface->y -= cursor->c_surface.y;
	cursor->neutre += cursor->c_neutre;
}

void			pillar_to_pillar(t_arch *arch, t_fvct2 *pillar, t_fvct2 *next
	, t_borne *borne_tmp)
{
	int			start;
	t_cursor	curs;

	start = arch->px.x;
	curs = init_cursor_dir_pillar(arch, pillar, next);
	while (arch->px.x != arch->px.y)
	{
		if (arch->portal.b_up[arch->px.x] > (uint32_t)arch->sdl->size.y)
			arch->portal.b_up[arch->px.x] = arch->sdl->size.y - 1;
		if (arch->portal.b_down[arch->px.x] > (uint32_t)arch->sdl->size.y)
			arch->portal.b_down[arch->px.x] = arch->sdl->size.y - 1;
		if (arch->wall->status == WALL
			&& z_line_buffer(arch, curs.neutre, arch->px.x))
		{
			draw_column(arch, *pillar);
			props_draw_column(arch->wall->props, arch, *pillar);
		}
		else if (arch->wall->status == PORTAL
			&& zline_portal(arch, borne_tmp->zline, curs.neutre, start))
			draw_portal(arch, *pillar, borne_tmp, start);
		cursor_increment(&curs);
		arch->px.x++;
	}
}
