/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   borne.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 01:28:54 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/13 02:59:00 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int			trunc_int(int value, int min, int max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	return (value);
}

void		set_borne_vertical(t_arch *arch, t_vct2 surface, int i)
{

	arch->portal.b_up[i] = (uint32_t)trunc_int(surface.x, arch->portal.b_up[arch->px.x], arch->portal.b_down[arch->px.x] - 1);
	arch->portal.b_up[i] = (uint32_t)trunc_int(arch->portal.b_up[i], 0, arch->sdl->size.y - 1);
	arch->portal.b_down[i] = (uint32_t)trunc_int(surface.y, arch->portal.b_up[arch->px.x], arch->portal.b_down[arch->px.x] - 1);
	arch->portal.b_down[i] = (uint32_t)trunc_int(arch->portal.b_down[i], 0, arch->sdl->size.y - 1);
}

void		set_borne_horizontal(t_arch *arch)
{
	arch->portal.b_left = atan2((arch->sdl->size.x / 2) - arch->px.x, arch->cam->d_screen);
	arch->portal.b_right = atan2((arch->sdl->size.x / 2) - arch->px.y, arch->cam->d_screen);
	arch->portal.b_left *= TOANGLE;
	arch->portal.b_right *= TOANGLE;
}

/*
**	sauvegarde toute les configuration de borne dans une structure
**	dans une zone (la zone est les limite de px)
*/
t_borne		*borne_svg(t_arch *arch, t_borne *borne)
{
	int		len;

	len = arch->px.y - arch->px.x;
	borne->b_left = arch->portal.b_left;
	borne->b_right = arch->portal.b_right;
	borne->pillar = arch->portal.pillar;
	borne->next = arch->portal.next;
	borne_init(borne, len);
	return (borne);
}

/*
**	recharge une borne dans la borne arch
*	(une borne anciennement sauvegarde...)
*/
void		borne_load(t_arch *arch, t_borne *borne, t_vct2 px_draw)
{
	int		i;

	i = 0;
	arch->portal.b_left = borne->b_left;
	arch->portal.b_right = borne->b_right;

	while (px_draw.x < px_draw.y)
	{
		arch->portal.b_up[px_draw.x] = borne->b_up[i];
		arch->portal.b_down[px_draw.x] = borne->b_down[i];
		arch->portal.zline[px_draw.x] = borne->zline[i];
		px_draw.x++;
		i++;
	}
	arch->portal.pillar = borne->pillar;
	arch->portal.next = borne->next;
	borne_free(borne);
}