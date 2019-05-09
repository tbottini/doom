/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:13:54 by akrache           #+#    #+#             */
/*   Updated: 2019/05/09 19:50:13 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** returns the color c as if it passes throught a transparent screen of color s.
** float f determines the opacity of the "screen".
** f must be between 0 and 1, returning the color s, 0 the color c.
*/

int			opacity(int s, int c, float f)
{
	return (((int)((c >> 8 & 255) + f * ((s >> 8 & 255) - (c >> 8 & 255))) << 8)
	+ ((int)((c >> 16 & 255) + f * ((s >> 16 & 255) - (c >> 16 & 255))) << 16)
	+ ((int)((c >> 24 & 255) + f * ((s >> 24 & 255) - (c >> 24 & 255))) << 24));
}

void		big_point(t_doom *d, t_vct2 v, int c)
{
	d->sdl.screen[v.x + v.y * d->sdl.size.x] = c;
	d->sdl.screen[v.x + 1 + v.y * d->sdl.size.x] = c;
	d->sdl.screen[v.x - 1 + v.y * d->sdl.size.x] = c;
	d->sdl.screen[v.x + 1 + (v.y + 1) * d->sdl.size.x] = c;
	d->sdl.screen[v.x - 1 + (v.y + 1) * d->sdl.size.x] = c;
	d->sdl.screen[v.x + 1 + (v.y - 1) * d->sdl.size.x] = c;
	d->sdl.screen[v.x - 1 + (v.y - 1) * d->sdl.size.x] = c;
	d->sdl.screen[v.x + (v.y + 1) * d->sdl.size.x] = c;
	d->sdl.screen[v.x + (v.y - 1) * d->sdl.size.x] = c;
}

void		minicursor(t_doom *d, int x, int y, int c)
{
	t_vct2	cursor;

	cursor.x = x - ((x - (d->sdl.size.x >> 6)) >> 1);
	cursor.y = y - ((y - (d->sdl.size.y - (d->sdl.size.y >> 2))) >> 1);
	big_point(d, cursor, c);
}

/*
void        miniwalls(t_doom *doom)
{
    int i;
    t_vct2    cursor;
    t_vct2    cursor2;
    t_wall    *wall;

    i = 0;
    wall = doom->sector->wall;
    cursor = hot_point(doom->player.pos, doom->sdl.size);
    bold_point(cursor, RED_WALL, doom);
    i = 0;
    cursor = hot_point(wall[0].pillar, doom->sdl.size);
    while (i < doom->sector->len)
    {
        cursor2 = hot_point(wall[i + 1].pillar, doom->sdl.size);
        bold_point(cursor, INT_MAX, doom);
        trait(doom, cursor, cursor2, INT_MAX);
        i++;
        cursor = cursor2;
    }
    sdl_present(&doom->sdl);
}
*/

void		minimap(t_doom *d)
{
	int x;
	int y;
	int c;
	int i;
	int j;

	i = (d->sdl.size.x >> 6);
	x = d->sdl.size.x >> 3;

	y = d->sdl.size.y - (d->sdl.size.y >> 5);
	c = 0xFFFFFFFF;
	while (i < x)
	{
		j = d->sdl.size.y - (d->sdl.size.y >> 2);
		d->sdl.screen[i + j * d->sdl.size.x] = c;
		while (++j < y - 1)
		{
			d->sdl.screen[i + j * d->sdl.size.x] = (i == (d->sdl.size.x >> 6)
				|| i == x - 1) ? c : opacity(0xA53333FF, d->sdl.screen[i + j * d->sdl.size.x], 0.5);
		}
		d->sdl.screen[i + j * d->sdl.size.x] = c;
		i++;
	}
	minicursor(d, x, y, 0x4DFFFFFF);
}
