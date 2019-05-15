/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/05/06 17:46:28 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#define CLICKRANGE 12

t_lstpil	find_pilier(t_lstpil start, int x, int y)
{
	t_lstpil curr;

	curr = start;
	while (curr)
	{
		if (x - CLICKRANGE < curr->pos.x && curr->pos.x < x + CLICKRANGE
			&& y - CLICKRANGE < curr->pos.y && curr->pos.y < y + CLICKRANGE)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

static void	map_draw_line(t_editor *editor, t_vct2 pos0, t_vct2 pos1, Uint32 color)
{
	pos0.x += editor->mappos.x;
	pos0.y += editor->mappos.y;
	pos1.x += editor->mappos.x;
	pos1.y += editor->mappos.y;
	editor_fill_line(editor, pos0, pos1, color);
}

void		draw_grid(t_editor *editor, t_vct2 center, int cases, int dist)
{
	t_vct2 curr;
	t_vct2 pos;

	curr.x = center.x - cases * dist;
	curr.y = center.y - cases * dist;
	pos.x = center.x - cases * dist;
	pos.y = center.y + cases * dist;
	if (pos.x < 0)
		pos.x = 0;
	if (pos.y > editor->size.y)
		pos.y = editor->size.y;
	while (curr.x < center.x + cases * dist && curr.x < editor->size.x)
	{
		if (curr.x >= 0)
			editor_fill_line(editor, curr, (t_vct2){curr.x, pos.y}, 0x50505050);
		curr.x += dist;
	}
	editor_fill_line(editor, curr, (t_vct2){curr.x, pos.y}, 0x50505050);
	while (curr.y < pos.y && curr.y < editor->size.y)
	{
		if (curr.y >= 0)
			editor_fill_line(editor, curr, (t_vct2){pos.x, curr.y}, 0x50505050);
		curr.y += dist;
	}
	editor_fill_line(editor, curr, (t_vct2){pos.x, curr.y}, 0x50505050);
}

void	draw_map(t_editor *editor)
{
	t_lstpil	curr;
	t_vct2		loc;

	draw_grid(editor, editor->mappos, 50, editor->mapzoom);
	curr = editor->map;
	while (curr)
	{
		loc.x = editor->mappos.x + curr->pos.x;
		loc.y = editor->mappos.y + curr->pos.y;
		if (curr->next)
			map_draw_line(editor, curr->pos, curr->next->pos, 0xFFFFFFFF);
		if (curr == editor->currpilier)
			big_pixel(editor->screen, editor->size, loc, 0xFF0000FF);
		else
			big_pixel(editor->screen, editor->size, loc, 0xFFFFFFFF);
		curr = curr->next;
	}
}
