/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 17:28:11 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/23 04:18:03 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		borne_reset(t_arch *arch)
{
	int	i;

	i = 0;
	while (i < arch->sdl->size.x)
	{
		arch->portal.b_up[i] = 0;
		arch->portal.b_down[i] = arch->sdl->size.y;
		i++;
	}
	arch->portal.b_left = arch->cam->fov / 2.0;
	arch->portal.b_right = -arch->cam->fov / 2.0;
}

void		zline_reset(t_arch *arch)
{
	int	i;

	i = 0;
	while (i < arch->sdl->size.x)
	{
		arch->portal.zline[i] = 0;
		i++;
	}
}

void		architect_reset(t_arch *arch)
{
	borne_reset(arch);
	zline_reset(arch);
}

void		arch_free(t_arch *arch)
{
	free(arch->portal.zline);
}

int			arch_init(t_arch *arch, t_sdl *sdl, t_camera *cam)
{
	size_t	curseur;

	arch->portal.zline = (double*)malloc(sizeof(double) * sdl->size.x);
	if (!arch->portal.zline)
		return (0);
	curseur = sdl->size.x * (sdl->size.y - 1);
	arch->sdl = sdl;
	arch->cam = cam;
	arch->portal.b_down = (uint32_t*)malloc(sizeof(uint32_t) * sdl->size.x);
	if (!arch->portal.b_down)
		return (0);
	arch->portal.b_up = (uint32_t*)malloc(sizeof(uint32_t) * sdl->size.x);
	if (!arch->portal.b_up)
		return (0);
	arch->wall = NULL;
	arch->depth_portal = 0;
	arch_set_method(arch);
	zline_reset(arch);
	return (1);
}
