/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_effect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 21:55:18 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/13 02:08:13 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"


int				fish_bowl_px(t_arch *arch, t_pillar pillar)
{
	int			px;
	int			sx;

	sx = (arch->sdl->size.x / 2.0);
	px = sx - (tan(pillar.angle * PI180) * arch->cam->d_screen);
	if (px >= arch->sdl->size.x)
		px = arch->sdl->size.x - 1;
	return (px);
}

void			fish_eyes(double *dist, double angle)
{
	*dist = cos(angle * PI180) * *dist;
}
