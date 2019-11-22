/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 10:57:07 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 14:07:31 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
**	on recupere la hauteur du personnage
**	on fait la difference avec le sol sur lequel il est et sa position
**		par rapport au sol
**	la difference au sol avec l'enemy est la meme que la difference avec
**		le sol ou l'enemy est
*/

t_fvct2			player_enemy_diff_heigth(t_player *player, t_enemy *enemy)
{
	t_fvct2		length;

	length.y = -player->stat.height - (player->stat.pos.z
		- enemy->stat.sector->h_floor);
	length.x = length.y + enemy->stat.height;
	return (length);
}

/*
**	on recupere la difference basse et haute d'un objet par rapport au joueur
**	avec la hauteur du secteur et celui de l'obj
*/

t_fvct2			player_diff_heigth(t_player *player, double sector_floor
	, double obj_heigth)
{
	t_fvct2		length;

	length.y = -player->stat.height - (player->stat.pos.z - sector_floor);
	length.x = length.y + obj_heigth;
	return (length);
}

int				camera_proj_heigth(t_arch *arch, t_player *player
	, double h_diff, double depth)
{
	double		wall_angle;
	int			px;
	double		player_angle;

	player_angle = (player->stat.rot.x - 90) * TO_RADIAN;
	wall_angle = atan2(h_diff, depth);
	px = arch->sdl->size.y / 2 - tan(wall_angle) * arch->cam->d_screen;
	px += (player->stat.rot.x - 90) * 15.5;
	return (px);
}

t_vct2			player_prop_heigth_surface(t_arch *arch, t_player *player
	, t_prop *prop, double depth)
{
	t_fvct2		len;
	t_vct2		surface;

	len = player_diff_heigth(player, prop->sector->h_floor, 1);
	surface.x = camera_proj_heigth(arch, player, len.x, depth);
	surface.y = camera_proj_heigth(arch, player, len.y, depth);
	return (surface);
}

/*
**	on recupere la surface que l'enemy
**	prend verticalement sur une colonne de pixel selon ca profondeur
*/

t_vct2			cam_get_enemy_surface(t_arch *arch, t_enemy *enemy
	, t_player *player, double depth)
{
	t_fvct2		len;
	t_vct2		surface;

	len = player_enemy_diff_heigth(player, enemy);
	surface.x = camera_proj_heigth(arch, player, len.x, depth);
	surface.y = camera_proj_heigth(arch, player, len.y, depth);
	return (surface);
}
