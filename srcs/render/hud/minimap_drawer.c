/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_drawer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 11:42:04 by akrache           #+#    #+#             */
/*   Updated: 2019/07/20 16:54:07 by akrache          ###   ########.fr       */
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

static t_vct2	minipoint(t_player *player, t_fvct2 v, t_minimap m)
{
	t_vct2	px;

	px.x = (m.a.x - (m.size.x / 2)) + ((v.x - player->stat.pos.x)) * (UNIT);
	px.y = (m.a.y - (m.size.y / 2)) + ((player->stat.pos.y - v.y)) * (UNIT);
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

static void			miniwallprops(t_minimap mini, t_wall *wall, t_fvct3 pos)
{
	int		i;
	t_vct2	tmp;

	i = 0;
	while (i < wall->nb_props)
	{
		//if (sector->props[i].tex)
		//{
			tmp.x = (mini.a.x - (mini.size.x / 2))
				+ ((wall->props[i].pos.x - pos.x)) * (UNIT);
			tmp.y = (mini.a.y - (mini.size.y / 2))
				+ ((pos.y - wall->props[i].pos.y)) * (UNIT);
			bold_point2(mini, tmp, DEEPBLUE);
			tmp.x = (mini.a.x - (mini.size.x / 2))
				+ ((( wall->props[i].hitbox.x) - pos.x)) * (UNIT);
			tmp.y = (mini.a.y - (mini.size.y / 2))
				+ ((pos.y - ( wall->props[i].hitbox.y))) * (UNIT);
			bold_point2(mini, tmp, 0xFF0000FF);
			
			tmp.x = (mini.a.x - (mini.size.x / 2))
				+ ((( wall->props[i].hitbox.x) - pos.x)) * (UNIT);
			tmp.y = (mini.a.y - (mini.size.y / 2))
				+ ((pos.y - ( wall->props[i].hitbox.l))) * (UNIT);
			bold_point2(mini, tmp, 0xFF0000FF);
			
			tmp.x = (mini.a.x - (mini.size.x / 2))
				+ ((( wall->props[i].hitbox.w) - pos.x)) * (UNIT);
			tmp.y = (mini.a.y - (mini.size.y / 2))
				+ ((pos.y - ( wall->props[i].hitbox.y))) * (UNIT);
			bold_point2(mini, tmp, 0xFF0000FF);
			
			tmp.x = (mini.a.x - (mini.size.x / 2))
				+ ((( wall->props[i].hitbox.w) - pos.x)) * (UNIT);
			tmp.y = (mini.a.y - (mini.size.y / 2))
				+ ((pos.y - ( wall->props[i].hitbox.l))) * (UNIT);
			bold_point2(mini, tmp, 0xFF0000FF);
			/* 
			tmp.x = (mini.a.x - (mini.size.x / 2))
				+ ((( wall->props[i].pos.x + -HITBOXSIZE) - pos.x)) * (UNIT);
			tmp.y = (mini.a.y - (mini.size.y / 2))
				+ ((pos.y - ( wall->props[i].pos.y + -HITBOXSIZE))) * (UNIT);
			bold_point2(mini, tmp, 0);
			tmp.x = (mini.a.x - (mini.size.x / 2))
				+ ((( wall->props[i].pos.x + -HITBOXSIZE) - pos.x)) * (UNIT);
			tmp.y = (mini.a.y - (mini.size.y / 2))
				+ ((pos.y - ( wall->props[i].pos.y + HITBOXSIZE))) * (UNIT);
			bold_point2(mini, tmp, 0);
			tmp.x = (mini.a.x - (mini.size.x / 2))
				+ ((( wall->props[i].pos.x + HITBOXSIZE) - pos.x)) * (UNIT);
			tmp.y = (mini.a.y - (mini.size.y / 2))
				+ ((pos.y - ( wall->props[i].pos.y + -HITBOXSIZE))) * (UNIT);
		//}*/
		i++;
	}
}

void			miniwalls(t_doom *doom, t_sector *sector, t_minimap mini)
{
	int			i;
	t_vct2		cursor;
	t_vct2		cursor2;
	t_wall		*wall;

	wall = sector->wall;
	i = -1;
	while (++i < sector->len)
	{
		cursor = minipoint(&doom->game.player, wall[i].pillar->p, mini);
		cursor2 = minipoint(&doom->game.player, wall[i].next->p, mini);
		mbl(cursor, cursor2, mini, wall[i].status
			!= PORTAL ? CWALL : CPORT);
		cursor = minipoint(&doom->game.player, wall[i].pillar->p, mini);
		miniwallprops(mini, &wall[i], doom->game.player.stat.pos);
	}
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
