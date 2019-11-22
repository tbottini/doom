/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_drawer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 11:42:04 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 05:28:18 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "doom_nukem.h"
#include "color.h"

static t_vct2	minipoint(t_fvct3 pos, t_fvct2 v, t_minimap *m)
{
	t_vct2	px;

	px.x = (m->a.x - (m->size.x / 2)) + ((v.x - pos.x)) * (UNIT);
	px.y = (m->a.y - (m->size.y / 2)) + ((pos.y - v.y)) * (UNIT);
	return (px);
}

static void		mbl(t_vct2 pos0, t_vct2 pos1, t_minimap *mini, Uint32 color)
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

static void		miniwallprops(t_minimap *mini, t_wall *wall, t_fvct3 pos)
{
	t_vct3	tmp;

	tmp.z = -1;
	while (++tmp.z < wall->nb_props)
	{
		tmp.x = (mini->a.x - (mini->size.x / 2))
			+ ((wall->props[tmp.z].pos.x - pos.x)) * (UNIT);
		tmp.y = (mini->a.y - (mini->size.y / 2))
			+ ((pos.y - wall->props[tmp.z].pos.y)) * (UNIT);
		bold_point2(mini, (t_vct2){tmp.x, tmp.y}, DEEPBLUE);
		tmp.x = (mini->a.x - (mini->size.x / 2))
			+ (((wall->props[tmp.z].pos.x + HITBOXSIZE) - pos.x)) * (UNIT);
		tmp.y = (mini->a.y - (mini->size.y / 2))
			+ ((pos.y - (wall->props[tmp.z].pos.y + HITBOXSIZE))) * (UNIT);
		bold_point2(mini, (t_vct2){tmp.x, tmp.y}, 0);
		tmp.y = (mini->a.y - (mini->size.y / 2))
			+ ((pos.y - (wall->props[tmp.z].pos.y + -HITBOXSIZE))) * (UNIT);
		bold_point2(mini, (t_vct2){tmp.x, tmp.y}, 0);
		tmp.x = (mini->a.x - (mini->size.x / 2))
			+ (((wall->props[tmp.z].pos.x + -HITBOXSIZE) - pos.x)) * (UNIT);
		bold_point2(mini, (t_vct2){tmp.x, tmp.y}, 0);
		tmp.y = (mini->a.y - (mini->size.y / 2))
			+ ((pos.y - (wall->props[tmp.z].pos.y + HITBOXSIZE))) * (UNIT);
		bold_point2(mini, (t_vct2){tmp.x, tmp.y}, 0);
	}
}

void			mini_draw_wall(t_wall *wall, t_fvct3 pos, t_minimap *mini)
{
	t_vct2		p1;
	t_vct2		p2;

	p1 = minipoint(pos, wall->pillar->p, mini);
	p2 = minipoint(pos, wall->next->p, mini);
	if (wall->status < OPEN_DOOR)
		mbl(p1, p2, mini, CWALL);
}

void			miniwalls(t_player *player, t_sector *sector, t_minimap *mini)
{
	int			i;
	t_vct2		cursor;
	t_vct2		cursor2;
	t_wall		*wall;

	wall = sector->wall;
	i = -1;
	while (++i < sector->len)
	{
		cursor = minipoint(player->stat.pos, wall[i].pillar->p, mini);
		cursor2 = minipoint(player->stat.pos, wall[i].next->p, mini);
		mbl(cursor, cursor2, mini, wall[i].status
			< OPEN_DOOR ? CWALL : CPORT);
		cursor = minipoint(player->stat.pos, wall[i].pillar->p, mini);
		miniwallprops(mini, &wall[i], player->stat.pos);
	}
}
