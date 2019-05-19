/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:13:54 by akrache           #+#    #+#             */
/*   Updated: 2019/05/19 15:49:51 by tbottini         ###   ########.fr       */
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

# define UNIT 20.0
# define CWALL 0xDADADAFF
# define CPERS 0xFFFFFFFF
# define WHITE 0xFFFFFFFF

/*
void		input_deplacement(t_doom *doom, int key)
{
	double x_dir;
	double y_dir;

	y_dir = cos(doom->player.rot.y * PI / 180) * 15;
	x_dir = sin(doom->player.rot.y * PI / 180) * 15;
	if (key == SDLK_w)
	{
		doom->player.pos.y += y_dir;
		doom->player.pos.x -= x_dir;
	}
	else if (key == SDLK_a)
	{
		doom->player.pos.y -= x_dir;
		doom->player.pos.x -= y_dir;
	}
	else if (key == SDLK_s)
	{
		doom->player.pos.y -= y_dir;
		doom->player.pos.x += x_dir;
	}
	else if (key == SDLK_d)
	{
		doom->player.pos.y += x_dir;
		doom->player.pos.x += y_dir;
	}
}*/

int			bold_point2(t_doom *doom, t_minimap mini, t_vct2 pos, Uint32 color)
{
	int tmp;

	tmp = pos.y * doom->sdl.size.x;
	if (pos.y > mini.d.y && pos.y < mini.a.y - 1 && pos.x < mini.a.x - 1 && pos.x > mini.d.x)
	{
		doom->sdl.screen[pos.x + tmp] = color;
		doom->sdl.screen[pos.x + 1 + tmp] = color;
		doom->sdl.screen[pos.x - 1 + tmp] = color;
		doom->sdl.screen[pos.x + 1 + tmp + doom->sdl.size.x] = color;
		doom->sdl.screen[pos.x - 1 + tmp + doom->sdl.size.x] = color;
		doom->sdl.screen[pos.x + 1 + tmp - doom->sdl.size.x] = color;
		doom->sdl.screen[pos.x - 1 + tmp - doom->sdl.size.x] = color;
		doom->sdl.screen[pos.x + tmp + doom->sdl.size.x] = color;
		doom->sdl.screen[pos.x + tmp - doom->sdl.size.x] = color;
	}
	return (1);
}

/*
** returns the color c as if it passes throught a transparent screen of color s.
** double f determines the opacity of the "screen".
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

	px.x = (mini.a.x - (mini.size.x >> 1)) + ((vct.x - d->player.pos.x)) * (UNIT);
	px.y = (mini.a.y - (mini.size.y >> 1)) + ((vct.y - d->player.pos.y)) * (UNIT);
	return (px);
}

void	minibigline(t_doom *doom, t_vct2 pos0, t_vct2 pos1, t_minimap mini)
{
	t_vct3	decal;
	t_vct2	orig;
	int		err;
	int		e2;

	orig.x = ft_abs(pos1.x - pos0.x);
	orig.y = ft_abs(pos1.y - pos0.y);
	decal.x = (pos0.x < pos1.x ? 1 : -1);
	decal.y = (pos0.y < pos1.y ? 1 : -1);
	err = (orig.x > orig.y ? orig.x : -orig.y) >> 1;
	bold_point2(doom, mini, pos0, CWALL);
	while ((pos0.x != pos1.x || pos0.y != pos1.y)
			&& bold_point2(doom, mini, pos0, CWALL))
	{
		e2 = err;
		if (e2 > -orig.x && ((err -= orig.y) || 1))
			pos0.x += decal.x;
		if (e2 < orig.y && ((err += orig.x) || 1))
			pos0.y += decal.y;
	}
}

void	miniline(t_sdl *sdl, t_vct2 pos0, t_vct2 pos1, Uint32 color)
{
	t_vct3	decal;
	t_vct2	orig;
	int		err;
	int		e2;

	orig.x = ft_abs(pos1.x - pos0.x);
	orig.y = ft_abs(pos1.y - pos0.y);
	decal.x = (pos0.x < pos1.x ? 1 : -1);
	decal.y = (pos0.y < pos1.y ? 1 : -1);
	err = (orig.x > orig.y ? orig.x : -orig.y) >> 1;
	fill_pixel(sdl->screen, sdl->size, pos0, color);
	while ((pos0.x != pos1.x || pos0.y != pos1.y)
			&& sdl->screen[pos0.x + pos0.y * sdl->size.x] != WHITE
			&& sdl->screen[pos0.x + pos0.y * sdl->size.x] != CWALL
			&& fill_pixel(sdl->screen, sdl->size, pos0, color))
	{
		e2 = err;
		if (e2 > -orig.x && ((err -= orig.y) || 1))
			pos0.x += decal.x;
		if (e2 < orig.y && ((err += orig.x) || 1))
			pos0.y += decal.y;
	}
}

void        miniwalls(t_doom *doom, t_minimap mini)
{
	int i;
	t_vct2		cursor;
	t_vct2		tmp;
	t_vct2		cursor2;
	t_wall		*wall;

	i = -1;
	wall = doom->sector->wall;
	cursor = minipoint(doom, wall[0].pillar.p, mini);
	tmp = cursor;
	while (++i < doom->sector->len - 1)
	{
		cursor2 = minipoint(doom, wall[i + 1].pillar.p, mini);
		minibigline(doom, cursor, cursor2, mini);
		cursor = cursor2;
	}
	minibigline(doom, cursor, tmp, mini);
}

void		minifield(t_doom *d, t_minimap mini, double angle)
{

	t_vct2	pix;

	pix.x = 256 * cos(angle * PI180) + mini.mid.x;
	pix.y = -256 * sin(angle * PI180) + mini.mid.y;
	miniline(&d->sdl, mini.mid, pix, hcol(d->player.health));
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
	miniwalls(d, mini);
	i = (d->player.rot.y - (d->player.fov >> 1));
	while (i < (d->player.rot.y + (d->player.fov >> 1)))
	{
		minifield(d, mini, i);
		i += d->player.fov >> 3;
	}
	miniwalls(d, mini);
	bold_point2(d, mini, mini.mid, CPERS);
	describe_player(d->player);
	SDL_RenderCopy(d->sdl.rend, d->sdl.txture, NULL, NULL);
}
