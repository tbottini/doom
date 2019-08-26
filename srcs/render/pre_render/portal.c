/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 15:27:12 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 15:27:38 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
**	si un mur en traver d'un portail on coupe le mur au niveau du portail
**	en gardant que la partie derriere le portail
*/

int				portal_clipping(t_arch *arch, int flag, t_affine a_wall
	, t_affine a_portal)
{
	t_fvct2		inter;
	int			*px;
	t_affine	a_pillar;

	inter = (flag == PILLAR) ? arch->pillar : arch->next;
	px = (flag == PILLAR) ? &arch->px.x : &arch->px.y;
	if (interpolation_linear_secur(a_portal, a_wall, &inter))
		return (0);
	pillar_virtual_move(arch, inter, flag);
	a_pillar.a = inter.y / inter.x;
	a_pillar.b = 0;
	*px = arch->sdl->size.x / 2 - affine_val(a_pillar
		, arch->cam->d_screen);
	return (1);
}

/*
**	renvoie la position du mur par rapport au portail de rendu
**		0 si le portail est devant le portail
**		1 si le portail est derriere le portail
**	si le portail est derriere alors on peut rendre la surface
**	inter[0] inter pillar et portal
**	inter[1] inter next et portal
**	on fait une intersection entre les lignes de projections
**	des pilliers et le portail auquel ils appartiennent
**	si les intersections sont plus proche que les point alors
**	les points sont derriere le portail
*/

int				wall_behind_portal(t_arch *arch)
{
	t_affine	a_wall;
	t_affine	a_portal;
	t_affine	a_pillar;
	t_affine	a_pillar2;
	t_fvct2		inter[2];

	a_pillar = (t_affine){arch->pillar.y / arch->pillar.x, 0, 0};
	a_pillar2 = (t_affine){arch->next.y / arch->next.x, 0, 0};
	a_portal = affine_points_secur(arch->portal.pillar, arch->portal.next);
	if (fabs(a_pillar.a - a_pillar2.a) < 0.001)
		return (0);
	interpolation_linear_secur(a_portal, a_pillar, &inter[0]);
	interpolation_linear_secur(a_portal, a_pillar2, &inter[1]);
	if (inter[0].x > arch->pillar.x && inter[1].x > arch->next.x)
		return (0);
	if (a_portal.a == 0)
		return (0);
	a_wall = affine_points_secur(arch->pillar, arch->next);
	if (inter[0].x > arch->pillar.x
		&& !portal_clipping(arch, PILLAR, a_wall, a_portal))
		return (0);
	else if (inter[1].x > arch->next.x
		&& !portal_clipping(arch, NEXT, a_wall, a_portal))
		return (0);
	return (1);
}

/*
**	check si un point est derriere un portail
**	si le profondeur n'est pas evidente
**	alors intersection du point avec son portail
**		si l'inter est plus proche que le point il est
**		le portail
*/

int				point_behind_portal(t_arch *arch, t_player *player, t_fvct2 pos)
{
	t_affine	a_point;
	t_affine	a_portal;
	t_fvct2		inter;

	(void)player;
	if (arch->depth_portal == 0)
		return (1);
	else if (pos.x > arch->portal.pillar.x && pos.x > arch->portal.next.x)
		return (1);
	a_point = (t_affine){pos.y / pos.x, 0, 0};
	a_portal = affine_points_secur(arch->portal.pillar, arch->portal.next);
	interpolation_linear_secur(a_portal, a_point, &inter);
	return (inter.x < pos.x);
}
