/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:04:20 by magrab            #+#    #+#             */
/*   Updated: 2019/07/16 15:04:22 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_vct2	g_r_mp(t_editor *editor, int x, int y)
{
	t_vct2 pos;

	pos.x = (x - editor->mappos.x) * EDITPREC / editor->mappos.z;
	pos.y = (y - editor->mappos.y) * EDITPREC / editor->mappos.z;
	return (pos);
}

t_vct2	get_screen_mappos(t_editor *editor, int x, int y)
{
	t_vct2 pos;

	pos.x = x * editor->mappos.z / EDITPREC + editor->mappos.x;
	pos.y = y * editor->mappos.z / EDITPREC + editor->mappos.y;
	return (pos);
}

t_vct2	line_percent(t_vct2 pos1, t_vct2 pos2, double percent)
{
	t_vct2 middle;

	middle.x = pos1.x - (pos1.x - pos2.x) * percent;
	middle.y = pos1.y - (pos1.y - pos2.y) * percent;
	return (middle);
}

int		ft_walllen(t_lstmur start)
{
	int x;

	x = 0;
	while (start)
	{
		++x;
		start = start->next;
	}
	return (x);
}

void	ft_movewall(t_mur *wall, int addx, int addy, int zoom)
{
	t_lstent wprops;

	wall->pil1->pos.x += addx * (EDITPREC) / zoom;
	wall->pil1->pos.y += addy * (EDITPREC) / zoom;
	wall->pil2->pos.x += addx * (EDITPREC) / zoom;
	wall->pil2->pos.y += addy * (EDITPREC) / zoom;
	wprops = wall->wproplist;
	while (wprops)
	{
		wprops->stat.pos = line_percent(wall->pil1->pos, wall->pil2->pos,
			wprops->stat.roty / 100);
		wprops = wprops->next;
	}
}
