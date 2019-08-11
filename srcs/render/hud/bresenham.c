/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 15:30:27 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/04 11:58:54 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void		bold_point_debug(t_vct2 v, Uint32 color, t_screen *screen)
{
	int tmp;

	tmp = v.y * screen->w;
	if (v.y > 0 && v.y < (screen->h - 1) && (v.x < screen->w - 1) && v.x > 0)
	{
		screen->screen[v.x + tmp] = color;
		screen->screen[v.x + 1 + tmp] = color;
		screen->screen[v.x - 1 + tmp] = color;
		screen->screen[v.x + 1 + tmp + screen->w] = color;
		screen->screen[v.x - 1 + tmp + screen->w] = color;
		screen->screen[v.x + 1 + tmp - screen->w] = color;
		screen->screen[v.x - 1 + tmp - screen->w] = color;
		screen->screen[v.x + tmp + screen->w] = color;
		screen->screen[v.x + tmp - screen->w] = color;
	}
}

void		point(t_vct2 v, Uint32 color, t_screen *screen)
{
	if (v.x > 0 && v.y > 0 && v.x < screen->w && v.y < screen->h)
		screen->screen[v.x + v.y * screen->w] = color;
}


void			trait_id(t_screen *screen, t_vct2 vct1, t_vct2 vct2, Uint32 col)
{
	int			dx;
	int			dy;
	int			d;
	int			yi;

	dx = vct2.x - vct1.x;
	dy = vct2.y - vct1.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = 2 * dy + dx;
	while (vct1.x != vct2.x)
	{
		vct1.x++;
		point(vct1, col, screen);
		if (d > 0)
		{
			vct1.y += yi;
			d -= 2 * dx;
		}
		d += 2 * dy;
	}
}

void			trait_iu(t_screen *screen, t_vct2 vct1, t_vct2 vct2, Uint32 col)
{
	int			dx;
	int			dy;
	int			d;
	int			xi;

	dy = vct2.y - vct1.y;
	dx = vct2.x - vct1.x;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = 2 * dx + dy;
	while (vct1.y != vct2.y)
	{
		vct1.y++;
		point(vct1, col, screen);
		if (d > 0)
		{
			vct1.x += xi;
			d -= 2 * dy;
		}
		d += 2 * dx;
	}
}

void			trait(t_screen *screen, t_vct2 vct1, t_vct2 vct2, Uint32 col)
{
	if (vct2.x != -1 && vct2.y != -1
		&& vct1.x != -1 && vct1.y != -1)
	{
		if (abs(vct2.y - vct1.y) < abs(vct2.x - vct1.x))
		{
			if (vct1.x > vct2.x)
				trait_id(screen, vct2, vct1, col);
			else
				trait_id(screen, vct1, vct2, col);
		}
		else
		{
			if (vct1.y > vct2.y)
				trait_iu(screen, vct2, vct1, col);
			else
				trait_iu(screen, vct1, vct2, col);
		}
	}
}
