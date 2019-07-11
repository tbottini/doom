/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:13:54 by akrache           #+#    #+#             */
/*   Updated: 2019/07/10 20:43:21 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define UNIT 8.0
#define CWALL 0xDADADAFF
#define CPORT 0xE6E678FF
#define WHITE 0xFFFFFFFF

static Uint32		hcol(int health, int boost)
{
	if (boost)
		return (0x76F7FFFF);
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

static t_minimap	miniinit(t_sdl *s, int health, int boost)
{
	t_minimap	mini;
	int			i;
	int			j;

	mini.d.x = (s->size.x >> 6);
	mini.a.x = s->size.x >> 3;
	mini.d.y = s->size.y - (s->size.y >> 2);
	mini.a.y = s->size.y - (s->size.y >> 5);
	mini.size.x = mini.a.x - mini.d.x;
	mini.size.y = mini.a.y - mini.d.y;
	mini.mid.x = mini.a.x - (mini.size.x >> 1);
	mini.mid.y = mini.a.y - (mini.size.y >> 1);
	mini.sdl = s;
	i = mini.d.x;
	while (i < mini.a.x - 1)
	{
		j = s->size.y - (s->size.y >> 2);
		while (++j < mini.a.y - 1)
			s->screen[i + j * s->size.x] = opacity(hcol(health, boost),
				s->screen[i + j * s->size.x], 0.5);
		++i;
	}
	return (mini);
}

static void			miniline(t_sdl *sdl, t_vct2 pos0, t_vct2 pos1, Uint32 color)
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

static void			minifield(t_player *player, t_minimap mini)
{
	int		i;
	t_vct2	pix;

	i = (player->stat.rot.y - (player->fov >> 1));
	while (i < (player->stat.rot.y + (player->fov >> 1)))
	{
		pix.x = 256 * cos(i * PI180) + mini.mid.x;
		pix.y = -256 * sin(i * PI180) + mini.mid.y;
		miniline(mini.sdl, mini.mid, pix,
			hcol(player->stat.health, player->boost));
		i += player->fov >> 3;
	}
}

void				minimap(t_doom *d)
{
	t_minimap	mini;

	mini = miniinit(&d->sdl, d->game.player.stat.health, d->game.player.boost);
	miniwalls(d, d->game.player.stat.sector, mini);
	minibord(d, mini);
	minifield(&d->game.player, mini);
	bold_point2(mini, mini.mid, WHITE);
}
