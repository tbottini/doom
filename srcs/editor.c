/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/05/27 16:22:57 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#define SECTORBOXHEIGHT 50

t_vct2 get_rel_mappos(t_editor *editor, int x, int y)
{
	t_vct2 pos;

	pos.x = (x - editor->mappos.x) * EDITORPRECISION / editor->mappos.z;
	pos.y = (y - editor->mappos.y) * EDITORPRECISION / editor->mappos.z;
	return (pos);
}

t_lstpil find_pilier(t_editor *editor, t_lstpil start, int x, int y)
{
	t_lstpil curr;
	t_vct2 p;

	curr = start;
	p = get_rel_mappos(editor, x, y);
	while (curr)
	{
		if (p.x - MAXZOOM / editor->mappos.z * 2 <= curr->pos.x
				&& curr->pos.x <= p.x + MAXZOOM / editor->mappos.z * 2
				&& p.y - MAXZOOM / editor->mappos.z * 2 <= curr->pos.y
				&& curr->pos.y <= p.y + MAXZOOM / editor->mappos.z * 2)
			return (curr);
		if (curr->next != start)
			curr = curr->next;
		else
			curr = NULL;
	}
	return (NULL);
}

static void map_draw_line(t_editor *editor, t_vct2 pos0, t_vct2 pos1, char c[4])
{
	pos0.x = pos0.x * editor->mappos.z / EDITORPRECISION + editor->mappos.x;
	pos0.y = pos0.y * editor->mappos.z / EDITORPRECISION + editor->mappos.y;
	pos1.x = pos1.x * editor->mappos.z / EDITORPRECISION + editor->mappos.x;
	pos1.y = pos1.y * editor->mappos.z / EDITORPRECISION + editor->mappos.y;
	SDL_SetRenderDrawColor(editor->rend, c[0], c[1], c[2], c[3]);
	SDL_RenderDrawLine(editor->rend, pos0.x, pos0.y, pos1.x, pos1.y);
}

void draw_grid(t_editor *editor, t_vct2 center, int dist, int master)
{
	t_vct2 curr;

	(void)master;
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

void draw_map(t_editor *editor)
{
	t_lstsec currsec;
	t_lstpil curr;
	t_vct2 loc;
	SDL_Rect tmp;

	loc.x = editor->mappos.x;
	loc.y = editor->mappos.y;

	draw_grid(editor, loc, editor->mappos.z, 0);
	currsec = editor->sectors;
	while (currsec)
	{
		curr = currsec->root;
		while (curr)
		{
			loc.x = editor->mappos.x + curr->pos.x * editor->mappos.z / EDITORPRECISION;
			loc.y = editor->mappos.y + curr->pos.y * editor->mappos.z / EDITORPRECISION;
			tmp.x = loc.x - 5;
			tmp.y = loc.y - 5;
			tmp.w = 10;
			tmp.h = 10;
			if (curr->next)
			{
				if (currsec->root == editor->map)
					map_draw_line(editor, curr->pos, curr->next->pos, (char[4]){150, 170, 250, 0xAA});
				else
					map_draw_line(editor, curr->pos, curr->next->pos, (char[4]){150, 150, 150, 0xFF});
			}
			if (curr == editor->currpilier)
				SDL_SetRenderDrawColor(editor->rend, 255, 0, 0, 255);
			else if (curr == editor->hoverpilier)
				SDL_SetRenderDrawColor(editor->rend, 0, 255, 0, 255);
			else if (currsec->root == editor->map)
				SDL_SetRenderDrawColor(editor->rend, 255, 255, 255, 255);
			else
				SDL_SetRenderDrawColor(editor->rend, 150, 150, 150, 255);
			SDL_RenderFillRect(editor->rend, &tmp);
			if (curr->next != currsec->root)
				curr = curr->next;
			else
				curr = NULL;
		}
		currsec = currsec->next;
	}
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 255);
}

void draw_sector_menu(t_editor *editor, t_font font)
{
	SDL_Rect box;
	t_lstsec currsec;
	int x;

	x = 0;
	box = editor->sectbox;
	SDL_SetRenderDrawColor(editor->rend, 66, 66, 66, 255);
	SDL_RenderFillRect(editor->rend, &box);
	SDL_SetRenderDrawColor(editor->rend, 255, 255, 255, 255);
	//SDL_RenderDrawLine(editor->rend, box.x + box.w, box.y, box.x + )
	box.h = SECTORBOXHEIGHT;
	box.y += editor->sectscroll;
	currsec = editor->sectors;
	while (currsec)
	{
		SDL_RenderDrawRect(editor->rend, &box);
		if (currsec->root == editor->map)
			sdl_int_put(editor->rend, font.s32, (t_vct2){box.x + 5, box.y + 5}, "Sect ", x, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
		else
			sdl_int_put(editor->rend, font.s32, (t_vct2){box.x + 5, box.y + 5}, "Sect ", x, (SDL_Color){0x88, 0xAA, 0xBB, 0xFF});
		sdl_string_put(editor->rend, font.s32, (t_vct2){box.x + box.w - 40, box.y + 5}, "[X]", (SDL_Color){0xFF, 0x55, 0x55, 0xFF});
		box.y += box.h;
		currsec = currsec->next;
		++x;
	}
	sdl_string_put(editor->rend, font.s32, (t_vct2){box.x + box.w / 2 - 20, box.y + 5}, "(+)", (SDL_Color){0xFF, 0xFF, 0xFF, 0xFF});
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 255);
}

void	change_sector(t_editor *edit, int pos, int del)
{
	t_lstsec sec;
	pos = (pos - edit->sectscroll) / SECTORBOXHEIGHT;
	edit->currpilier = NULL;
	sec = edit->sectors;
	while (pos > 0 && sec->next)
	{
		sec = sec->next;
		pos--;
	}
	if (pos == 0)
	{
		if (del)
		{
			edit->map = NULL;
			if (sec->prvs)
				sec->prvs->next = sec->next;
			else if (sec == edit->sectors)
			{
				if (sec->next)
				{
					edit->sectors = sec->next;
					edit->sectors->prvs = NULL;
				}
				else
					edit->sectors = init_secteur();
			}
			if (sec->next)
				sec->next->prvs = sec->prvs;
			ft_clear_pillar_list(&sec->root);
			free(sec);
		}
		else
			edit->map = sec->root;
	}
	else if (pos == 1)
		edit->map = push_init_secteur(&(edit->sectors))->root;
	else
		edit->map = NULL;
	ft_printf("%d\n", pos);
}
