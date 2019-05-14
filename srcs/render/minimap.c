/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:13:54 by akrache           #+#    #+#             */
/*   Updated: 2019/05/14 22:55:30 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

typedef struct			s_minimap
{
	t_vct2	d;
	t_vct2	a;
	t_vct2	size;
	t_vct2	mid;
}						t_minimap;

#define UNIT 20.0
#define CWALL 0xFFFF00FF
#define CPERS 0x0C1597FF
#define WHITE 0xFFFFFFFF


void		bold_point2(t_vct2 v, uint32_t color, t_doom *doom, t_minimap mini)
{
	int tmp;

	tmp = v.y * doom->sdl.size.x;
	if (v.y > mini.d.y && v.y < mini.a.y - 1 && v.x < mini.a.x - 1 && v.x > mini.d.x)
	{
		doom->sdl.screen[v.x + tmp] = color;
		doom->sdl.screen[v.x + 1 + tmp] = color;
		doom->sdl.screen[v.x - 1 + tmp] = color;
		doom->sdl.screen[v.x + 1 + tmp + doom->sdl.size.x] = color;
		doom->sdl.screen[v.x - 1 + tmp + doom->sdl.size.x] = color;
		doom->sdl.screen[v.x + 1 + tmp - doom->sdl.size.x] = color;
		doom->sdl.screen[v.x - 1 + tmp - doom->sdl.size.x] = color;
		doom->sdl.screen[v.x + tmp + doom->sdl.size.x] = color;
		doom->sdl.screen[v.x + tmp - doom->sdl.size.x] = color;
	}
}

void			trait_id2(t_doom *doom, t_vct2 vct1, t_vct2 vct2, t_minimap mini)
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
	d = (dy << 1) + dx;
	while (vct1.x != vct2.x)
	{
		vct1.x++;
		bold_point2(vct1, CWALL, doom, mini);
		if (d > 0)
		{
			vct1.y += yi;
			d -= dx << 1;
		}
		d += dy << 1;
	}
}

void			trait_iu2(t_doom *doom, t_vct2 vct1, t_vct2 vct2, t_minimap mini)
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
	d = (dx << 1) + dy;
	while (vct1.y != vct2.y)
	{
		vct1.y++;
		bold_point2(vct1, CWALL, doom, mini);
		if (d > 0)
		{
			vct1.x += xi;
			d -= dy << 1;
		}
		d += dx << 1;
	}
}

void			trait2(t_doom *doom, t_vct2 vct1, t_vct2 vct2, t_minimap mini)
{
	if (vct2.x != -1 && vct2.y != -1
		&& vct1.x != -1 && vct1.y != -1)
	{
		if (abs(vct2.y - vct1.y) < abs(vct2.x - vct1.x))
		{
			if (vct1.x > vct2.x)
				trait_id2(doom, vct2, vct1, mini);
			else
				trait_id2(doom, vct1, vct2, mini);
		}
		else
		{
			if (vct1.y > vct2.y)
				trait_iu2(doom, vct2, vct1, mini);
			else
				trait_iu2(doom, vct1, vct2, mini);
		}
	}
}

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

Uint32			hcol(int health)
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

t_vct2		minipoint(t_doom *d, t_fvct2 vct, t_minimap mini)
{
	t_vct2	px;
	//double	rap;

	px.x = (mini.a.x - (mini.size.x >> 1)) + ((vct.x - d->player.pos.x)) * (UNIT);// * (10.0);
	px.y = (mini.a.y - (mini.size.y >> 1)) + ((vct.y - d->player.pos.y)) * (UNIT);// * (10.0);
	//px.x = ((vct.x + 10.0) / 20.0) * mini.size.x;
	//rap = 20.0 / mini.size.x * mini.size.y;
	//px.y = (((vct.y + rap/2.0) / rap) * mini.size.y);
	return (px);
}

void        miniwalls(t_doom *doom, t_minimap mini, uint32_t color)
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
		trait2(doom, cursor, cursor2, mini);
		i++;
		cursor = cursor2;
	}
	trait2(doom, cursor, tmp, mini);
}


void		minicursor(t_doom *d, int c, t_minimap mini)
{
	t_vct2	cursor;

	cursor.x = mini.a.x - (mini.size.x >> 1);
	cursor.y = mini.a.y - (mini.size.y >> 1);
	bold_point2(cursor, c, d, mini);
}

void		minifield(t_doom *d, t_minimap mini, double angle)
{

	t_vct2	pix;

	pix.x = 128 * cos(angle * PI180) + mini.mid.x;
	pix.y = -128 * sin(angle * PI180) + mini.mid.y;
	fill_line(&d->sdl, mini.mid, pix, hcol(d->player.health));
}

void		minimap(t_doom *d)
{
	t_minimap	mini;
	int			i;
	int			j;

	mini.d.x = (d->sdl.size.x >> 6);
	mini.a.x = d->sdl.size.x >> 3;
	mini.d.y = d->sdl.size.y - (d->sdl.size.y >> 2);
	mini.a.y = d->sdl.size.y - (d->sdl.size.y >> 5);
	mini.size.x = mini.a.x - mini.d.x;
	mini.size.y = mini.a.y - mini.d.y;
	mini.mid.x = mini.a.x - (mini.size.x >> 1);
	mini.mid.y = mini.a.y - (mini.size.y >> 1);
	i = mini.d.x;
	while (i < mini.a.x)
	{
		j = d->sdl.size.y - (d->sdl.size.y >> 2);
		d->sdl.screen[i + j * d->sdl.size.x] = WHITE;
		while (++j < mini.a.y - 1)
		{
			d->sdl.screen[i + j * d->sdl.size.x] = (i == (d->sdl.size.x >> 6)
				|| i == mini.a.x - 1) ? WHITE : opacity(hcol(d->player.health), d->sdl.screen[i + j * d->sdl.size.x], 0.5);
		}
		d->sdl.screen[i + j * d->sdl.size.x] = WHITE;
		++i;
	}
	miniwalls(d, mini, CWALL);
	i = (d->player.rot.y - (d->player.fov >> 1));
	while (i < (d->player.rot.y + (d->player.fov >> 1)))
	{
		minifield(d, mini, i);
		i += d->player.fov / 4;
	}
	miniwalls(d, mini, CWALL);
	//minifield(d, mini, (d->player.rot.y + (d->player.fov >> 1)));
	//minifield(d, mini, (d->player.rot.y - (d->player.fov >> 1)));
	//minifield(d, mini, (d->player.rot.y));
	minicursor(d, CPERS, mini); //mid
	debug_player(d->player);
	SDL_RenderCopy(d->sdl.rend, d->sdl.txture, NULL, NULL);
}
