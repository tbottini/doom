/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_render_method.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 04:11:23 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 16:17:23 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

extern inline void	wall_pillar_render(t_arch *arch, t_pil_render *render_stuff
	, double len_pillar)
{
	if (zline_wall(arch, render_stuff, len_pillar))
	{
		draw_wall(arch, render_stuff);
		props_draw_column(arch->wall->props, arch, render_stuff->pillar);
	}
}

extern inline void	door_pillar_render(t_arch *arch, t_pil_render *render_stuff
	, double len_pillar)
{
	if ((arch->px.x >= render_stuff->px_inter) ^ render_stuff->open_invert)
	{
		if (zline_portal(arch, render_stuff, len_pillar))
			draw_door(arch, render_stuff, PORTAL);
	}
	else if (zline_wall(arch, render_stuff, len_pillar))
		draw_door(arch, render_stuff, WALL);
}

extern inline void	window_pillar_render(t_arch *arch
	, t_pil_render *render_stuff
	, double len_pillar)
{
	(void)len_pillar;
	draw_window(arch, render_stuff);
}

extern inline void	portal_pillar_render(t_arch *arch
	, t_pil_render *render_stuff
	, double len_pillar)
{
	if (zline_portal(arch, render_stuff, len_pillar))
		draw_portal(arch, render_stuff);
}

/*
**	on affecte a l'arch ses methodes de rendu
*/

void				arch_set_method(t_arch *arch)
{
	arch->render_method[WALL] = &wall_pillar_render;
	arch->render_method[OPEN_DOOR] = &door_pillar_render;
	arch->render_method[CLOSE_DOOR] = &door_pillar_render;
	arch->render_method[WINDOW] = &window_pillar_render;
	arch->render_method[PORTAL] = &portal_pillar_render;
}
