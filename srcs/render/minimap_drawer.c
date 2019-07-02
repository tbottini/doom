/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_drawer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 11:42:04 by akrache           #+#    #+#             */
/*   Updated: 2019/07/02 20:48:29 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define UNIT 8.0
#define CWALL 0xDADADAFF
#define CPORT 0xE6E678FF
#define WHITE 0xFFFFFFFF

int				bold_point2(t_minimap mini, t_vct2 pos, Uint32 color)
{
	int tmp;

	tmp = pos.y * mini.sdl->size.x;
	if (pos.y > mini.d.y && pos.y < mini.a.y - 1
		&& pos.x < mini.a.x - 1 && pos.x > mini.d.x)
	{
		mini.sdl->screen[pos.x + tmp] = color;
		mini.sdl->screen[pos.x + 1 + tmp] = color;
		mini.sdl->screen[pos.x - 1 + tmp] = color;
		mini.sdl->screen[pos.x + 1 + tmp + mini.sdl->size.x] = color;
		mini.sdl->screen[pos.x - 1 + tmp + mini.sdl->size.x] = color;
		mini.sdl->screen[pos.x + 1 + tmp - mini.sdl->size.x] = color;
		mini.sdl->screen[pos.x - 1 + tmp - mini.sdl->size.x] = color;
		mini.sdl->screen[pos.x + tmp + mini.sdl->size.x] = color;
		mini.sdl->screen[pos.x + tmp - mini.sdl->size.x] = color;
	}
	return (1);
}

static t_vct2	minipoint(t_doom *d, t_fvct2 v, t_minimap m)
{
	t_vct2	px;

	px.x = (m.a.x - (m.size.x / 2)) + ((v.x - d->player.stat.pos.x)) * (UNIT);
	px.y = (m.a.y - (m.size.y / 2)) + ((d->player.stat.pos.y - v.y)) * (UNIT);
	return (px);
}

static void		mbl(t_vct2 pos0, t_vct2 pos1, t_minimap mini, Uint32 color)
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
	bold_point2(mini, pos0, color);
	while ((pos0.x != pos1.x || pos0.y != pos1.y)
			&& bold_point2(mini, pos0, color))
	{
		e2 = err;
		if (e2 > -orig.x && ((err -= orig.y) || 1))
			pos0.x += decal.x;
		if (e2 < orig.y && ((err += orig.x) || 1))
			pos0.y += decal.y;
	}
}

void			miniwalls(t_doom *doom, t_sector sector, t_minimap mini)
{
	int			i;
	t_vct2		cursor;
	t_vct2		tmp;
	t_vct2		cursor2;
	t_wall		*wall;

	i = -1;
	while (++i < sector.len_sub)
		miniwalls(doom, sector.ssector[i], mini);
	wall = sector.wall;
	cursor = minipoint(doom, wall[0].pillar.p, mini);
	tmp = cursor;
	i = -1;
	while (++i < sector.len - 1)
	{
		cursor2 = minipoint(doom, wall[i + 1].pillar.p, mini);
		mbl(cursor, cursor2, mini, wall[i + 1].status
			!= PORTAL ? CWALL : CPORT);
		cursor = cursor2;
	}
	mbl(cursor, tmp, mini, wall[0].status != PORTAL ? CWALL : CPORT);
}

void			minibord(t_doom *d, t_minimap mini)
{
	int i;
	int j;

	i = mini.d.x - 1;
	j = mini.a.y - 1;
	while (++i < mini.a.x - 1)
	{
		d->sdl.screen[i + mini.d.y * d->sdl.size.x] = WHITE;
		d->sdl.screen[i + j * d->sdl.size.x] = WHITE;
	}
	j = d->sdl.size.y - (d->sdl.size.y >> 2) - 1;
	while (++j < mini.a.y)
	{
		d->sdl.screen[mini.d.x + j * d->sdl.size.x] = WHITE;
		d->sdl.screen[i + j * d->sdl.size.x] = WHITE;
	}
}
