/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/07/01 20:41:41 by akrache          ###   ########.fr       */
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

t_vct2 get_screen_mappos(t_editor *editor, int x, int y)
{
	t_vct2 pos;

	pos.x = x * editor->mappos.z / EDITORPRECISION + editor->mappos.x;
	pos.y = y * editor->mappos.z / EDITORPRECISION + editor->mappos.y;
	return (pos);
}

void sdl_draw_rect_map(t_editor *editor, SDL_Rect rect)
{
	t_vct2 tmp;
	SDL_Rect sbox;

	tmp = get_screen_mappos(editor, rect.x, rect.y);
	sbox.x = tmp.x;
	sbox.y = tmp.y;
	tmp = get_screen_mappos(editor, rect.x + rect.w, rect.y + rect.h);
	sbox.w = tmp.x - sbox.x;
	sbox.h = tmp.y - sbox.y;
	SDL_SetRenderDrawColor(editor->rend, 200, 200, 200, 255);
	SDL_RenderFillRect(editor->rend, &sbox);
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 0);
}

void sdl_draw_pixel_map(t_editor *editor, int x, int y)
{
	t_vct2 tmp;

	tmp = get_screen_mappos(editor, x, y);
	SDL_SetRenderDrawColor(editor->rend, 200, 200, 200, 255);
	SDL_RenderDrawPoint(editor->rend, tmp.x, tmp.y);
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 0);
}

t_stat *find_player(t_editor *edit, int x, int y)
{
	t_vct2 loc;
	SDL_Rect ppos;
	t_enemy *curr;

	loc = get_screen_mappos(edit, edit->player.stat.pos.x, edit->player.stat.pos.y);
	ppos.x = loc.x - 10;
	ppos.y = loc.y - 10;
	ppos.w = 20;
	ppos.h = 20;
	if (pos_in_rect(ppos, x, y))
		return (&edit->player.stat);
	curr = edit->ennlist;
	while (curr)
	{
		loc = get_screen_mappos(edit, curr->stat.pos.x, curr->stat.pos.y);
		ppos.x = loc.x - 10;
		ppos.y = loc.y - 10;
		if (pos_in_rect(ppos, x, y))
			return (&curr->stat);
		curr = curr->next;
	}
	return (NULL);
}

t_pilier *find_pilier(t_editor *editor, t_lstpil start, int x, int y)
{
	t_pilier *curr;
	t_vct2 p;

	curr = start;
	p = get_rel_mappos(editor, x, y);
	while (curr)
	{
		if (p.x - MAXZOOM / editor->mappos.z * 2 <= curr->pos.x && curr->pos.x <= p.x + MAXZOOM / editor->mappos.z * 2 && p.y - MAXZOOM / editor->mappos.z * 2 <= curr->pos.y && curr->pos.y <= p.y + MAXZOOM / editor->mappos.z * 2)
			return (curr);
		if (curr->next != start)
			curr = curr->next;
		else
			curr = NULL;
	}
	return (NULL);
}

t_mur *find_mur(t_editor *editor, t_lstsec start, int x, int y)
{
	SDL_Rect tbox;
	t_mur *curr;
	t_vct2 p;
	t_fvct2 coef;
	int precs;

	if (!start)
		return (NULL);
	curr = start->murs;
	p = get_rel_mappos(editor, x, y);
	precs = (EDITORPRECISION) / editor->mappos.z + 1;
	while (curr)
	{
		tbox.x = (curr->pil1->pos.x < curr->pil2->pos.x ? curr->pil1->pos.x : curr->pil2->pos.x);
		tbox.y = (curr->pil1->pos.y < curr->pil2->pos.y ? curr->pil1->pos.y : curr->pil2->pos.y);
		tbox.w = (curr->pil1->pos.x > curr->pil2->pos.x ? curr->pil1->pos.x : curr->pil2->pos.x) - tbox.x + precs * 8;
		tbox.h = (curr->pil1->pos.y > curr->pil2->pos.y ? curr->pil1->pos.y : curr->pil2->pos.y) - tbox.y + precs * 8;
		tbox.x -= precs * 4;
		tbox.y -= precs * 4;
		if (pos_in_rect(tbox, p.x, p.y))
		{
			coef.x = (double)(curr->pil1->pos.y - curr->pil2->pos.y) / (double)(curr->pil1->pos.x - curr->pil2->pos.x);
			coef.y = (double)curr->pil1->pos.y - (double)curr->pil1->pos.x * coef.x;
			if (p.y >= (p.x * coef.x + coef.y) - precs * 4 && p.y <= (p.x * coef.x + coef.y) + precs * 4)
				return (curr);
			coef.x = (double)(curr->pil1->pos.x - curr->pil2->pos.x) / (double)(curr->pil1->pos.y - curr->pil2->pos.y);
			coef.y = (double)curr->pil1->pos.x - (double)curr->pil1->pos.y * coef.x;
			if (p.x >= (p.y * coef.x + coef.y) - precs * 4 && p.x <= (p.y * coef.x + coef.y) + precs * 4)
				return (curr);
		}
		if (curr->next != start->murs)
			curr = curr->next;
		else
			curr = NULL;
	}
	return (NULL);
}

static void map_draw_line(t_editor *editor, t_vct2 pos0, t_vct2 pos1, SDL_Color c)
{
	pos0 = get_screen_mappos(editor, pos0.x, pos0.y);
	pos1 = get_screen_mappos(editor, pos1.x, pos1.y);
	SDL_SetRenderDrawColor(editor->rend, c.r, c.g, c.b, c.a);
	SDL_RenderDrawLine(editor->rend, pos0.x, pos0.y, pos1.x, pos1.y);
}

static void draw_grid(t_editor *editor, t_vct2 center, int dist, int master)
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

static void draw_player(t_editor *editor)
{
	t_vct2 loc;
	SDL_Rect tmp;

	if (editor->currstat == &(editor->player.stat))
		SDL_SetRenderDrawColor(editor->rend, 100, 255, 100, 255);
	else if (editor->player.stat.sector == (t_sector *)editor->map)
		SDL_SetRenderDrawColor(editor->rend, 100, 205, 100, 255);
	else
		SDL_SetRenderDrawColor(editor->rend, 100, 150, 100, 255);
	loc = get_screen_mappos(editor, editor->player.stat.pos.x, editor->player.stat.pos.y);
	tmp.x = loc.x - 10;
	tmp.y = loc.y - 10;
	tmp.w = 20;
	tmp.h = 20;
	SDL_RenderDrawRect(editor->rend, &tmp);
	tmp.x = cos(editor->player.stat.rot.y * PI180) * 50.0;
	tmp.y = sin(editor->player.stat.rot.y * PI180) * 50.0;
	SDL_RenderDrawLine(editor->rend, loc.x, loc.y, loc.x + tmp.x, loc.y + tmp.y);
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 255);
}

static void draw_enemy(t_editor *editor)
{
	t_enemy		*curr;
	SDL_Rect	tmp;
	t_vct2		loc;

	curr = editor->ennlist;
	while (curr)
	{
		if (editor->currstat == &(curr->stat))
			SDL_SetRenderDrawColor(editor->rend, 220, 105, 255, 255);
		else if (curr->stat.sector == (t_sector *)editor->map)
			SDL_SetRenderDrawColor(editor->rend, 170, 100, 205, 255);
		else
			SDL_SetRenderDrawColor(editor->rend, 120, 100, 155, 255);
		loc = get_screen_mappos(editor, curr->stat.pos.x, curr->stat.pos.y);
		tmp.x = loc.x - 10;
		tmp.y = loc.y - 10;
		tmp.w = 20;
		tmp.h = 20;
		SDL_RenderDrawRect(editor->rend, &tmp);
		tmp.x = cos(curr->stat.rot.y * PI180) * 35.0;
		tmp.y = sin(curr->stat.rot.y * PI180) * 35.0;
		SDL_RenderDrawLine(editor->rend, loc.x, loc.y, loc.x + tmp.x, loc.y + tmp.y);
		curr = curr->next;
	}
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 255);
}

static void draw_pills(t_editor *editor)
{
	t_pilier	*curr;
	SDL_Rect	tmp;
	t_vct2		loc;

	curr = editor->pillist;
	while (curr)
	{
		loc = get_screen_mappos(editor, curr->pos.x, curr->pos.y);
		tmp.x = loc.x - 5;
		tmp.y = loc.y - 5;
		tmp.w = 10;
		tmp.h = 10;
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

static void draw_walls(t_editor *editor)
{
	t_lstsec currsec;
	t_lstmur currwall;

	currsec = editor->sectors;
	while (currsec)
	{
		currwall = currsec->murs;
		while (currwall)
		{
			if (currsec == editor->map)
			{
				if (currwall == editor->currmur)
					map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos, (SDL_Color){200, 0, 70, 0xFF});
				else if (currwall == editor->hovermur)
					map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos, (SDL_Color){0, 200, 70, 0xFF});
				else if (currwall->portal_id)
					map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos, (SDL_Color){230, 230, 100, 0xFF});
				else
					map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos, (SDL_Color){180, 180, 250, 0xFF});
			}
			else
				map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos, (SDL_Color){150, 150, 150, 0xFF});
			currwall = currwall->next;
		}
		currsec = currsec->next;
	}
}

void draw_map(t_editor *editor)
{
	t_vct2 loc;

	loc.x = editor->mappos.x;
	loc.y = editor->mappos.y;
	draw_grid(editor, loc, editor->mappos.z, 0);
	draw_walls(editor);
	draw_pills(editor);
	draw_enemy(editor);
	draw_player(editor);
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 255);
}

void draw_sector_menu(t_editor *editor, t_font font)
{
	SDL_Rect box;
	t_lstsec currsec;
	int x;

	x = 0;
	box = editor->sectbox;
	if (editor->currmur || editor->currstat)
		SDL_SetRenderDrawColor(editor->rend, 99, 99, 99, 255);
	else
		SDL_SetRenderDrawColor(editor->rend, 66, 66, 66, 255);
	SDL_RenderFillRect(editor->rend, &box);
	SDL_SetRenderDrawColor(editor->rend, 255, 255, 255, 255);
	box.h = SECTORBOXHEIGHT;
	box.y += editor->sectscroll;
	currsec = editor->sectors;
	while (currsec)
	{
		SDL_RenderDrawRect(editor->rend, &box);
		if ((editor->currmur && editor->currmur->portal_id == currsec) || (editor->currstat && editor->currstat->sector == (t_sector *)currsec))
			sdl_int_put(editor->rend, font.s32, (t_vct2){box.x + 5, box.y + 5}, "Murs: ", ft_walllen(currsec->murs), (SDL_Color){180, 180, 150, 0xFF});
		else if (currsec == editor->map)
			sdl_int_put(editor->rend, font.s32, (t_vct2){box.x + 5, box.y + 5}, "Murs: ", ft_walllen(currsec->murs), (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
		else
			sdl_int_put(editor->rend, font.s32, (t_vct2){box.x + 5, box.y + 5}, "Murs: ", ft_walllen(currsec->murs), (SDL_Color){0x88, 0xAA, 0xBB, 0xFF});
		if (!editor->currmur && !editor->currstat)
			sdl_string_put(editor->rend, font.s32, (t_vct2){box.x + box.w - 40, box.y + 5}, "[X]", (SDL_Color){0xFF, 0x55, 0x55, 0xFF});
		box.y += box.h;
		currsec = currsec->next;
		++x;
	}
	if (!editor->currmur && !editor->currstat)
		sdl_string_put(editor->rend, font.s32, (t_vct2){box.x + box.w / 2 - 20, box.y + 5}, "(+)", (SDL_Color){0xFF, 0xFF, 0xFF, 0xFF});
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 255);
}

void draw_inspect_menu(t_editor *editor)
{
	SDL_Rect box;

	box = editor->inspectbox;
	SDL_SetRenderDrawColor(editor->rend, 66, 66, 66, 255);
	SDL_RenderFillRect(editor->rend, &box);
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 255);
	update_loc(editor->size, &editor->btnarr[0].loc, *editor->btnarr[0].loc.parent);
	SDL_RenderCopy(editor->rend, editor->btnarr[0].txture, NULL, &(editor->btnarr[0].loc.area));
}

/*
** cas == 0 : selectionne le nouveau secteur
** cas == 1 : supprime le secteur selectionne
** cas == 2 : renvoie le secteur selectionne
*/

t_secteur *sector_menu_click(t_editor *edit, int pos, int cas)
{
	t_lstsec sec;

	pos = (pos - edit->sectscroll) / SECTORBOXHEIGHT;
	edit->currpilier = NULL;
	sec = edit->sectors;
	while (pos > 0 && sec)
	{
		sec = sec->next;
		pos--;
	}
	if (pos == 0)
	{
		if (cas == 2)
			return (sec);
		if (!sec)
			edit->map = push_secteur(&(edit->sectors));
		else if (cas)
		{
			edit->map = NULL;
			if (sec->prvs)
				sec->prvs->next = sec->next;
			if (sec->next)
				sec->next->prvs = sec->prvs;
			if (sec == edit->sectors)
			{
				if (edit->sectors->next)
				{
					edit->sectors = sec->next;
					edit->sectors->prvs = NULL;
				}
				else
					edit->sectors = NULL;
			}
			ft_clear_secteur(&sec);
		}
		else
			edit->map = sec;
	}
	else if (pos == 1 && cas != 2)
		edit->map = push_secteur(&(edit->sectors));
	else if (cas != 2)
		edit->map = NULL;
	return (NULL);
}
