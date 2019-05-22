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


t_lstpil	find_pilier(t_editor *editor, t_lstpil start, int x, int y)
{
	t_lstpil curr;

	curr = start;
	x = (x - editor->mappos.x) * EDITORPRECISION / editor->mapzoom;
	y = (y - editor->mappos.y) * EDITORPRECISION / editor->mapzoom;
	while (curr)
	{
		if (x - MAXZOOM / editor->mapzoom < curr->pos.x && curr->pos.x < x + MAXZOOM / editor->mapzoom
			&& y - MAXZOOM / editor->mapzoom < curr->pos.y && curr->pos.y < y + MAXZOOM / editor->mapzoom)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
/*
t_lstpil	find_pilier(t_lstpil start, t_vct2 p)
{
	t_lstpil curr;

	curr = start;
	while (curr)
	{
		if (p.x - CLICKRANGE < curr->pos.x && curr->pos.x < p.x + CLICKRANGE
			&& p.y - CLICKRANGE < curr->pos.y && curr->pos.y < p.y + CLICKRANGE)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
*/

static void	map_draw_line(t_editor *editor, t_vct2 pos0, t_vct2 pos1)
{
	pos0.x = pos0.x * editor->mapzoom / EDITORPRECISION + editor->mappos.x;
	pos0.y = pos0.y * editor->mapzoom / EDITORPRECISION + editor->mappos.y;
	pos1.x = pos1.x * editor->mapzoom / EDITORPRECISION + editor->mappos.x;
	pos1.y = pos1.y * editor->mapzoom / EDITORPRECISION + editor->mappos.y;
	SDL_SetRenderDrawColor(editor->rend, 255, 255, 255, 255);
	SDL_RenderDrawLine(editor->rend, pos0.x, pos0.y, pos1.x, pos1.y);
}

void		draw_grid(t_editor *editor, t_vct2 center, int dist, int master)
{
	t_vct2 curr;

	//if (master)
	//	printf("%d\n", master);
	if (dist >= 400)
		draw_grid(editor, center, dist / 10, dist);
	if (dist >= 400)
		SDL_SetRenderDrawColor(editor->rend, 110, 110, 110, 255);
	else
		SDL_SetRenderDrawColor(editor->rend, 70, 70, 70, 255);
	curr.x = center.x % dist - dist;
	curr.y = center.y % dist - dist;
	while (curr.x < editor->size.x)
	{
		SDL_RenderDrawLine(editor->rend, curr.x, 0, curr.x, editor->size.y);
		curr.x += dist;
	}
	while (curr.y < editor->size.y)
	{
		SDL_RenderDrawLine(editor->rend, 0, curr.y, editor->size.x, curr.y);
		curr.y += dist;
	}
}

void	draw_map(t_editor *editor)
{
	t_lstpil	curr;
	t_vct2		loc;
	SDL_Rect	tmp;

	loc.x = editor->mappos.x;
	loc.y = editor->mappos.y;

	draw_grid(editor, loc, editor->mapzoom, 0);
	curr = editor->map;
	while (curr)
	{
		loc.x = editor->mappos.x + curr->pos.x * editor->mapzoom / EDITORPRECISION;
		loc.y = editor->mappos.y + curr->pos.y * editor->mapzoom / EDITORPRECISION;
		//printf("pillard : %d\t%d\n", curr->pos.x, curr->pos.y);
		tmp.x = loc.x - 5;
		tmp.y = loc.y - 5;
		tmp.w = 10;
		tmp.h = 10;
		if (curr->next)
			map_draw_line(editor, curr->pos, curr->next->pos);
		if (curr == editor->currpilier)
			SDL_SetRenderDrawColor(editor->rend, 255, 0, 0, 255);
		else if (curr == editor->hoverpilier)
			SDL_SetRenderDrawColor(editor->rend, 0, 255, 0, 255);
		else
			SDL_SetRenderDrawColor(editor->rend, 255, 255, 255, 255);
		SDL_RenderFillRect(editor->rend, &tmp);
		curr = curr->next;
	}
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 255);
}
