/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:13:54 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 07:03:38 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "doom_nukem.h"
#include "color.h"

static Uint32		hcol(int health, t_power power)
{
	if (power == FREEZE)
		return (0x76F7FFFF);
	if (power == SMOL)
		return (0xba68c8FF);
	if (power == PUNCH)
		return (0xb71c1cFF);
	if (health >= 100)
		return (0x44FF7D64);
	if (health > 75)
		return (0xB5FF444B);
	if (health > 50)
		return (0xEDFF4432);
	if (health > 25)
		return (0xFFCE4414);
	return (0xFF764401);
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

void				minifield(t_player *player, t_minimap *mini)
{
	int		i;
	t_vct2	pix;

	i = (player->stat.rot.y - (player->fov >> 1));
	while (i < (player->stat.rot.y + (player->fov >> 1)))
	{
		pix.x = 256 * cos(i * PI180) + mini->mid.x;
		pix.y = -256 * sin(i * PI180) + mini->mid.y;
		miniline(mini->sdl, mini->mid, pix,
			hcol(player->stat.health, player->power));
		i += player->fov >> 3;
	}
}

void				minifill(t_minimap *m, int h, t_power p)
{
	int i;
	int j;

	i = m->d.x;
	while (i < m->a.x - 1)
	{
		j = m->sdl->size.y - (m->sdl->size.y >> 2);
		while (++j < m->a.y - 1)
			if (m->sdl->screen[i + j * m->sdl->size.x] != CWALL
				&& m->sdl->screen[i + j * m->sdl->size.x] != CPORT)
				m->sdl->screen[i + j * m->sdl->size.x] = opacity(hcol(h, p),
				m->sdl->screen[i + j * m->sdl->size.x], 0.5);
		++i;
	}
}

t_minimap			miniinit(t_sdl *s, t_ui *ui)
{
	t_minimap	mini;

	mini.d.x = (s->size.x >> 6);
	mini.a.x = s->size.x >> 3;
	mini.d.y = s->size.y - (s->size.y >> 2);
	mini.a.y = s->size.y - (s->size.y >> 5);
	mini.size.x = mini.a.x - mini.d.x;
	mini.size.y = mini.a.y - mini.d.y;
	mini.mid.x = mini.a.x - (mini.size.x >> 1);
	mini.mid.y = mini.a.y - (mini.size.y >> 1);
	mini.sdl = s;
	mini.ui = ui;
	return (mini);
}
