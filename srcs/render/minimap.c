/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:13:54 by akrache           #+#    #+#             */
/*   Updated: 2019/05/13 19:01:36 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

typedef struct			s_minimap
{
	t_vct2	d;
	t_vct2	a;
	t_vct2	size;
	int		*tab;
}						t_minimap;

/*
** returns the color c as if it passes throught a transparent screen of color s.
** float f determines the opacity of the "screen".
** f must be between 0 and 1, returning the color s, 0 the color c.
*/

int			opacity(int s, int c, double f)
{
	if (f == 1)
		return (s);
	else if (!f)
		return (c);
	return (((int)((c >> 8 & 255) + f * ((s >> 8 & 255) - (c >> 8 & 255))) << 8)
	+ ((int)((c >> 16 & 255) + f * ((s >> 16 & 255) - (c >> 16 & 255))) << 16)
	+ ((int)((c >> 24 & 255) + f * ((s >> 24 & 255) - (c >> 24 & 255))) << 24));
}

int			hcol(int health)
{
	if (health >= 100)
		return (0x44FF7D64);
	else if (health > 75)
		return (0xB5FF444B);
	else if (health > 50)
		return (0xEDFF4432);
	else if (health > 25)
		return (0xFFCE4414);
	else
		return (0xFF764401);
}

void		big_point(t_doom *d, t_vct2 v, Uint32 c)
{
	int tmp;

	tmp = v.y * d->sdl.size.x;
	if (v.y > 0 && v.y < (d->sdl.size.y - 1) && (v.x < d->sdl.size.x - 1) && v.x > 0)
	{
		d->sdl.screen[v.x + tmp] = c;
		d->sdl.screen[v.x + 1 + tmp] = c;
		d->sdl.screen[v.x - 1 + tmp] = c;
		d->sdl.screen[v.x + 1 + tmp + d->sdl.size.x] = c;
		d->sdl.screen[v.x - 1 + tmp + d->sdl.size.x] = c;
		d->sdl.screen[v.x + 1 + tmp - d->sdl.size.x] = c;
		d->sdl.screen[v.x - 1 + tmp - d->sdl.size.x] = c;
		d->sdl.screen[v.x + tmp + d->sdl.size.x] = c;
		d->sdl.screen[v.x + tmp - d->sdl.size.x] = c;
	}
}

t_vct2		minipoint(t_doom *d, t_fvct2 vct, t_minimap mini)
{
	t_vct2	px;
	//double	rap;

	px.x = (vct.x / (double)d->sdl.size.x) * mini.size.x + mini.d.x;
	px.y = (vct.y / (double)d->sdl.size.y) * mini.size.y + mini.d.y;
	//px.x = ((vct.x + 10.0) / 20.0) * mini.size.x;
	//rap = 20.0 / mini.size.x * mini.size.y;
	//px.y = (((vct.y + rap/2.0) / rap) * mini.size.y);
	return (px);
}

void        miniwalls(t_doom *doom, t_minimap mini)
{
	int i;
	t_vct2		cursor;
	t_vct2		tmp;
	t_vct2		cursor2;
	t_wall		*wall;

	i = 0;
	wall = doom->sector->wall;
	cursor = minipoint(doom, wall[0].pillar.p, mini);
	tmp = cursor;
	while (i < doom->sector->len - 1)
	{
		cursor2 = minipoint(doom, wall[i + 1].pillar.p, mini);
		trait(doom, cursor, cursor2, 0x00FFFFFF);
		i++;
		cursor = cursor2;
	}
	trait(doom, cursor, tmp, 0x00FFFFFF);
}


void		minicursor(t_doom *d, int x, int y, int c)
{
	t_vct2	cursor;

	cursor.x = x - ((x - (d->sdl.size.x >> 6)) >> 1);
	cursor.y = y - ((y - (d->sdl.size.y - (d->sdl.size.y >> 2))) >> 1);
	bold_point(cursor, c, d);
}

void		minimap(t_doom *d)
{
	t_minimap	mini;
	Uint32 c;

	mini.d.x = (d->sdl.size.x >> 6);
	mini.a.x = d->sdl.size.x >> 3;
	mini.a.y = d->sdl.size.y - (d->sdl.size.y >> 5);
	mini.size.x = mini.a.x - mini.d.x;
	mini.size.y = mini.a.y - (d->sdl.size.y - (d->sdl.size.y >> 2));
	c = 0xFFFFFFFF;
	while (mini.d.x < mini.a.x)
	{
		mini.d.y = d->sdl.size.y - (d->sdl.size.y >> 2);
		d->sdl.screen[mini.d.x + mini.d.y * d->sdl.size.x] = c;
		while (++(mini.d.y) < mini.a.y - 1)
		{
			d->sdl.screen[mini.d.x + mini.d.y * d->sdl.size.x] = (mini.d.x == (d->sdl.size.x >> 6)
				|| mini.d.x == mini.a.x - 1) ? c : opacity(hcol(d->player.health), d->sdl.screen[mini.d.x + mini.d.y * d->sdl.size.x], 0.5);
		}
		d->sdl.screen[mini.d.x + mini.d.y * d->sdl.size.x] = c;
		++(mini.d.x);
	}
	minicursor(d, mini.a.x, mini.a.y, 0x0C1597FF);
	miniwalls(d, mini);
	debug_player(d->player);
	SDL_RenderCopy(d->sdl.rend, d->sdl.txture, NULL, NULL);
}
