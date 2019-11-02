/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   borne.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 05:21:56 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 14:19:43 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void				set_borne_vertical(t_arch *arch, t_vct2 surface, int i)
{
	arch->portal.b_up[i] = (uint32_t)trunc_int(surface.x
		, arch->portal.b_up[arch->px.x], arch->portal.b_down[arch->px.x] - 1);
	arch->portal.b_up[i] = (uint32_t)trunc_int(arch->portal.b_up[i]
		, 0, arch->sdl->size.y - 1);
	arch->portal.b_down[i] = (uint32_t)trunc_int(surface.y
		, arch->portal.b_up[arch->px.x], arch->portal.b_down[arch->px.x] - 1);
	arch->portal.b_down[i] = (uint32_t)trunc_int(arch->portal.b_down[i]
		, 0, arch->sdl->size.y - 1);
}

void				set_borne_horizontal(t_arch *arch)
{
	arch->portal.b_left = atan2((arch->sdl->size.x / 2)
		- arch->px.x, arch->cam->d_screen);
	arch->portal.b_right = atan2((arch->sdl->size.x / 2)
		- arch->px.y, arch->cam->d_screen);
	arch->portal.b_left *= TOANGLE;
	arch->portal.b_right *= TOANGLE;
}

void				borne_secur(t_arch *arch)
{
	if (arch->portal.b_up[arch->px.x] > (uint32_t)arch->sdl->size.y)
		arch->portal.b_up[arch->px.x] = arch->sdl->size.y - 1;
	if (arch->portal.b_down[arch->px.x] > (uint32_t)arch->sdl->size.y)
		arch->portal.b_down[arch->px.x] = arch->sdl->size.y - 1;
}

void				save_pixels_portal(t_arch *arch, t_pil_render *render_stuff
	, t_vct2 *pixels)
{
	if (arch->wall->status == PORTAL)
		*pixels = arch->px;
	else if (arch->wall->status == OPEN_DOOR
		|| arch->wall->status == CLOSE_DOOR)
	{
		if (!render_stuff->open_invert)
		{
			pixels->x = render_stuff->px_inter;
			pixels->y = arch->px.y;
		}
		else
		{
			pixels->x = arch->px.x;
			pixels->y = render_stuff->px_inter;
		}
	}
}
