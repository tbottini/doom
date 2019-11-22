/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 15:30:27 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/22 17:09:45 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#define BIGPIXELSIZE 5

int		fill_pixel(Uint32 *screen, t_vct2 size, t_vct2 pos, Uint32 color)
{
	if (0 <= pos.x && pos.x < size.x && 0 <= pos.y && pos.y < size.y)
	{
		screen[pos.x + pos.y * size.x] = color;
		return (1);
	}
	return (0);
}

void	big_pixel(Uint32 *screen, t_vct2 size, t_vct2 pos, Uint32 color)
{
	t_vct2 big;

	big.x = BIGPIXELSIZE + pos.x;
	big.y = BIGPIXELSIZE + pos.y;
	pos.x -= BIGPIXELSIZE;
	while (pos.x < big.x)
	{
		pos.y = big.y - BIGPIXELSIZE - BIGPIXELSIZE;
		while (pos.y < big.y)
		{
			fill_pixel(screen, size, pos, color);
			++pos.y;
		}
		++pos.x;
	}
}

void	fill_line(t_sdl *sdl, t_vct2 pos0, t_vct2 pos1, Uint32 color)
{
	t_vct3	decal;
	t_vct2	orig;
	int		err;
	int		e2;

	orig.x = ft_abs(pos1.x - pos0.x);
	orig.y = ft_abs(pos1.y - pos0.y);
	decal.x = (pos0.x < pos1.x ? 1 : -1);
	decal.y = (pos0.y < pos1.y ? 1 : -1);
	err = (orig.x > orig.y ? orig.x : -orig.y) / 2;
	fill_pixel(sdl->screen, sdl->size, pos0, color);
	while ((pos0.x != pos1.x || pos0.y != pos1.y)
			&& fill_pixel(sdl->screen, sdl->size, pos0, color))
	{
		e2 = err;
		if (e2 > -orig.x && ((err -= orig.y) || 1))
			pos0.x += decal.x;
		if (e2 < orig.y && ((err += orig.x) || 1))
			pos0.y += decal.y;
	}
}
