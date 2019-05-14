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
#define CLICKRANGE 10

t_pilier	find_pilier(t_pilier start, int x, int y)
{
	t_pilier curr;

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

void	draw_map(t_editor *editor)
{
	t_pilier	curr;
	t_vct2		loc;

	if (!editor->map)
		return ;
	curr = editor->map;
	editor_fill_line(editor, (t_vct2){editor->mappos.x - 20, editor->mappos.y},
		(t_vct2){editor->mappos.x + 200, editor->mappos.y}, 0xFFFFFFFF);
	editor_fill_line(editor, (t_vct2){editor->mappos.x, editor->mappos.y - 20},
		(t_vct2){editor->mappos.x, editor->mappos.y + 200}, 0xFFFFFFFF);
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
