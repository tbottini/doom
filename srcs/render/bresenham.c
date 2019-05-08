/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 15:30:27 by tbottini          #+#    #+#             */
/*   Updated: 2019/05/08 21:23:52 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			trait_id(t_doom *doom, t_vct2 vct1, t_vct2 vct2, uint32_t col)
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
		bold_point(vct1, col, doom);
		if (d > 0)
		{
			vct1.y += yi;
			d -= 2 * dx;
		}
		d += 2 * dy;
	}
}

void			trait_iu(t_doom *doom, t_vct2 vct1, t_vct2 vct2, uint32_t col)
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
		bold_point(vct1, col, doom);
		if (d > 0)
		{
			vct1.x += xi;
			d -= 2 * dy;
		}
		d += 2 * dx;
	}
}

void			trait(t_doom *doom, t_vct2 vct1, t_vct2 vct2, uint32_t col)
{
	if (vct2.x != -1 && vct2.y != -1
		&& vct1.x != -1 && vct1.y != -1)
	{
		if (abs(vct2.y - vct1.y) < abs(vct2.x - vct1.x))
		{
			if (vct1.x > vct2.x)
				trait_id(doom, vct2, vct1, col);
			else
				trait_id(doom, vct1, vct2, col);
		}
		else
		{
			if (vct1.y > vct2.y)
				trait_iu(doom, vct2, vct1, col);
			else
				trait_iu(doom, vct1, vct2, col);
		}
	}
}
