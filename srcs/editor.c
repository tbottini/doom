/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/07/03 13:31:36 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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

t_ecoord *find_player(t_editor *edit, int x, int y)
{
	t_vct2 loc;
	SDL_Rect ppos;
	t_entity *curr;

	loc = get_screen_mappos(edit, edit->player.stat.pos.x, edit->player.stat.pos.y);
	ppos.x = loc.x - 10;
	ppos.y = loc.y - 10;
	ppos.w = 20;
	ppos.h = 20;
	if (pos_in_rect(ppos, x, y))
		return (&edit->player.stat);
	if (edit->hovermur)
		curr = edit->hovermur->wproplist;
	else
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
	//	printf("%d\n", master % dist);
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
	else if (editor->player.stat.sector == editor->map)
		SDL_SetRenderDrawColor(editor->rend, 100, 205, 100, 255);
	else
		SDL_SetRenderDrawColor(editor->rend, 100, 150, 100, 255);
	loc = get_screen_mappos(editor, editor->player.stat.pos.x, editor->player.stat.pos.y);
	tmp.x = loc.x - 10;
	tmp.y = loc.y - 10;
	tmp.w = 20;
	tmp.h = 20;
	SDL_RenderDrawRect(editor->rend, &tmp);
	tmp.x = cos(editor->player.stat.roty * PI180) * 50.0;
	tmp.y = sin(editor->player.stat.roty * PI180) * 50.0;
	SDL_RenderDrawLine(editor->rend, loc.x, loc.y, loc.x + tmp.x, loc.y + tmp.y);
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 255);
}

static void draw_props(t_editor *editor, t_entity *curr, SDL_Texture **sprites, int proppos)
{
	SDL_Rect tmp;
	t_vct2 loc;
	int type;

	if (editor->currstat == &(curr->stat))
		SDL_SetRenderDrawColor(editor->rend, 75, 100, 255, 255);
	else if (curr->stat.sector == editor->map)
		SDL_SetRenderDrawColor(editor->rend, 50, 75, 150, 255);
	else
		SDL_SetRenderDrawColor(editor->rend, 50, 75, 100, 255);
	loc = get_screen_mappos(editor, curr->stat.pos.x, curr->stat.pos.y);
	tmp = (SDL_Rect){loc.x - 10, loc.y - 10, 20, 20};
	type = curr->stat.type - proppos;
	SDL_RenderCopy(editor->rend, sprites[type], NULL, &tmp);
	tmp = (SDL_Rect){tmp.x - 1, tmp.y - 1, tmp.w + 2, tmp.h + 2};
	SDL_RenderDrawRect(editor->rend, &tmp);
	tmp = (SDL_Rect){tmp.x - 1, tmp.y - 1, tmp.w + 2, tmp.h + 2};
	SDL_RenderDrawRect(editor->rend, &tmp);
	tmp = (SDL_Rect){tmp.x - 1, tmp.y - 1, tmp.w + 2, tmp.h + 2};
	SDL_RenderDrawRect(editor->rend, &tmp);
}

static void draw_enemies(t_editor *editor, t_entity *curr)
{
	SDL_Rect tmp;
	t_vct2 loc;

	if (editor->currstat == &(curr->stat))
		SDL_SetRenderDrawColor(editor->rend, 220, 105, 255, 255);
	else if (curr->stat.sector == editor->map)
		SDL_SetRenderDrawColor(editor->rend, 170, 100, 205, 255);
	else
		SDL_SetRenderDrawColor(editor->rend, 120, 100, 155, 255);
	loc = get_screen_mappos(editor, curr->stat.pos.x, curr->stat.pos.y);
	if (curr->stat.type <= 2)
		tmp = (SDL_Rect){loc.x - 5, loc.y - 5, 10, 10};
	else
		tmp = (SDL_Rect){loc.x - curr->stat.type * 2 - 2, loc.y - curr->stat.type * 2 - 2, curr->stat.type * 4 + 4, curr->stat.type * 4 + 4};
	if (curr->stat.type % 2)
		SDL_RenderDrawRect(editor->rend, &tmp);
	else
		SDL_RenderFillRect(editor->rend, &tmp);
	if (curr->stat.type <= 2)
	{
		tmp.x = cos(curr->stat.roty * PI180) * 20;
		tmp.y = sin(curr->stat.roty * PI180) * 20;
	}
	else
	{
		tmp.x = cos(curr->stat.roty * PI180) * curr->stat.type * 8;
		tmp.y = sin(curr->stat.roty * PI180) * curr->stat.type * 8;
	}
	SDL_RenderDrawLine(editor->rend, loc.x, loc.y, loc.x + tmp.x, loc.y + tmp.y);
}

static void draw_objs(t_editor *editor, t_entity *start)
{
	t_entity *curr;

	curr = start;
	while (curr)
	{
		if (MINPROPSPOS <= curr->stat.type && curr->stat.type < MAXPROPSPOS)
			draw_props(editor, curr, editor->sprites, MINPROPSPOS);
		else if (MINWPROPSPOS <= curr->stat.type && curr->stat.type < MAXWPROPSPOS)
			draw_props(editor, curr, editor->wsprites, MINWPROPSPOS);
		else
			draw_enemies(editor, curr);
		curr = curr->next;
	}
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 255);
}

static void draw_pills(t_editor *editor)
{
	t_pilier *curr;
	SDL_Rect tmp;
	t_vct2 loc;

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

#define PADDING 5

static void draw_txtrselector(t_editor *editor, int max, SDL_Texture **txtrs)
{
	SDL_Rect tmp;
	int x;

	SDL_SetRenderDrawColor(editor->rend, 50, 50, 50, 255);
	SDL_RenderFillRect(editor->rend, &editor->txtrbox);
	x = 0;
	tmp.x = editor->txtrbox.x + PADDING;
	tmp.y = editor->txtrbox.y + PADDING + editor->txtrscroll;
	tmp.w = 200;
	tmp.h = 200;
	SDL_SetRenderDrawColor(editor->rend, 255, 200, 200, 255);
	while (x < max && txtrs[x])
	{
		SDL_RenderCopy(editor->rend, txtrs[x], NULL, &tmp);
		tmp.x += tmp.w + PADDING;
		if (editor->txtrbox.x + editor->txtrbox.w < tmp.x + tmp.w)
		{
			tmp.x = editor->txtrbox.x + PADDING;
			tmp.y += tmp.h + PADDING;
		}
		++x;
	}
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 255);
}

static void draw_walls(t_editor *editor)
{
	t_lstsec currsec;
	t_lstmur currwall;
	t_lstsec finalsec;

	finalsec = NULL;
	currsec = editor->sectors;
	while (currsec)
	{
		currwall = currsec->murs;
		if (currsec != editor->map)
			while (currwall)
			{
				map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos, (SDL_Color){150, 150, 150, 0xFF});
				draw_objs(editor, currwall->wproplist);
				currwall = currwall->next;
			}
		else
			finalsec = currsec;
		currsec = currsec->next;
	}
	if (finalsec)
	{
		currwall = finalsec->murs;
		while (currwall)
		{
			if (currwall == editor->currmur)
				map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos, (SDL_Color){200, 0, 70, 0xFF});
			else if (currwall == editor->hovermur)
				map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos, (SDL_Color){0, 200, 70, 0xFF});
			else if (currwall->portal_ptr)
				map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos, (SDL_Color){230, 230, 100, 0xFF});
			else
				map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos, (SDL_Color){180, 180, 250, 0xFF});
			draw_objs(editor, currwall->wproplist);
			currwall = currwall->next;
		}
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
	draw_objs(editor, editor->ennlist);
	draw_player(editor);
	if (editor->selecttxtr == FILL_PROP)
		draw_txtrselector(editor, MAXPROPSNUMBER, editor->sprites);
	else if (editor->selecttxtr == FILL_WPROP)
		draw_txtrselector(editor, MAXWPROPSNUMBER, editor->wsprites);
	else if (editor->selecttxtr)
		draw_txtrselector(editor, MAXTXTRNUMBER, editor->txtrgame);
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
		if (editor->currmur && editor->currmur->portal_ptr == currsec)
			sdl_int_put(editor->rend, font.s32, (t_vct2){box.x + 5, box.y + 5}, "Murs: ", ft_walllen(currsec->murs), (SDL_Color){200, 200, 150, 0xFF});
		else if (editor->currstat && editor->currstat->sector == currsec)
		{
			if (editor->currstat == &editor->player.stat)
				sdl_int_put(editor->rend, font.s32, (t_vct2){box.x + 5, box.y + 5}, "Murs: ", ft_walllen(currsec->murs), (SDL_Color){100, 205, 100, 0xFF});
			else if (MINPROPSPOS <= editor->currstat->type && editor->currstat->type < MAXPROPSPOS)
				sdl_int_put(editor->rend, font.s32, (t_vct2){box.x + 5, box.y + 5}, "Murs: ", ft_walllen(currsec->murs), (SDL_Color){100, 125, 240, 0xFF});
			else
				sdl_int_put(editor->rend, font.s32, (t_vct2){box.x + 5, box.y + 5}, "Murs: ", ft_walllen(currsec->murs), (SDL_Color){170, 100, 205, 0xFF});
		}
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
	SDL_Rect txtrpos;

	box = editor->optbox;
	SDL_SetRenderDrawColor(editor->rend, 66, 66, 66, 255);
	SDL_RenderFillRect(editor->rend, &box);
	if (editor->currstat) // If Character
	{
		if (&editor->player.stat == editor->currstat) // If Player
			sdl_int_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + 5}, "Health: ", editor->currstat->type, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
		else if (MINPROPSPOS <= editor->currstat->type && editor->currstat->type < MAXPROPSPOS) // If Prop
		{
			sdl_int_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + 5}, "Type: ", editor->currstat->type - MINPROPSPOS, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
			sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT + 5}, "Delete", (SDL_Color){255, 100, 100, 0xFF});
		}
		else if (MINWPROPSPOS <= editor->currstat->type && editor->currstat->type < MAXWPROPSPOS) // If Wall Prop
		{
			sdl_int_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + 5}, "Type: ", editor->currstat->type - MINWPROPSPOS, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
			sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT + 5}, "Delete", (SDL_Color){255, 100, 100, 0xFF});
		}
		else
		{
			sdl_int_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + 5}, "Type: ", editor->currstat->type, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
			sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT + 5}, "Delete", (SDL_Color){255, 100, 100, 0xFF});
		}
	}
	else if (editor->currmur) // If mur
	{
		sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + 5}, "Texture:", (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
		txtrpos = (SDL_Rect){box.x + 120, box.y + 4, SECTORBOXHEIGHT - 2, SECTORBOXHEIGHT - 2};
		SDL_RenderCopy(editor->rend, editor->currmur->txtr, NULL, &txtrpos);
		if (editor->currmur->portal_ptr)
		{
			SDL_SetRenderDrawColor(editor->rend, 133, 133, 133, 255);
			SDL_RenderDrawLine(editor->rend, box.x, box.y + SECTORBOXHEIGHT + 5, box.x + box.w, box.y + SECTORBOXHEIGHT + 5);
			sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 1 + 5}, "Type: Window", (editor->currmur->portal_id == WINDOW ? (SDL_Color){255, 255, 200, 0xFF} : (SDL_Color){200, 200, 200, 0xFF}));
			sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 2 + 5}, " Close Door", (editor->currmur->portal_id == CLOSE_DOOR ? (SDL_Color){255, 255, 200, 0xFF} : (SDL_Color){200, 200, 200, 0xFF}));
			sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 3 + 5}, " Open Door", (editor->currmur->portal_id == OPEN_DOOR ? (SDL_Color){255, 255, 200, 0xFF} : (SDL_Color){200, 200, 200, 0xFF}));
			sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 4 + 5}, " Portal", (editor->currmur->portal_id == PORTAL ? (SDL_Color){255, 255, 200, 0xFF} : (SDL_Color){200, 200, 200, 0xFF}));
			SDL_RenderDrawLine(editor->rend, box.x, box.y + SECTORBOXHEIGHT * 5, box.x + box.w, box.y + SECTORBOXHEIGHT * 5);
		}
		else
		{
			sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 1 + 5}, "Add Prop", (SDL_Color){75, 100, 200, 0xFF});
		}
		
	}
	else if (editor->map) // If secteur
	{
		sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + 5}, "Plafond:", (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
		txtrpos = (SDL_Rect){box.x + 120, box.y + 4, SECTORBOXHEIGHT - 2, SECTORBOXHEIGHT - 2};
		SDL_RenderCopy(editor->rend, editor->map->top, NULL, &txtrpos);
		sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT + 5}, "Sol:", (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
		txtrpos = (SDL_Rect){box.x + 120, box.y + SECTORBOXHEIGHT + 4, SECTORBOXHEIGHT - 2, SECTORBOXHEIGHT - 2};
		SDL_RenderCopy(editor->rend, editor->map->sol, NULL, &txtrpos);
		sdl_int_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 2 + 5}, "Plafond: ", editor->map->htop, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
		sdl_int_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 3 + 5}, "Sol: ", editor->map->hsol, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
		if (editor->map->gravity)
			sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 4 + 5}, "Gravity: Moon", (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
		else
			sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 4 + 5}, "Gravity: Earth", (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
	}
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 255);
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
			edit->map = push_secteur(&(edit->sectors), edit->txtrgame[0], edit->txtrgame[0]);
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
		edit->map = push_secteur(&(edit->sectors), edit->txtrgame[0], edit->txtrgame[0]);
	else if (cas != 2)
		edit->map = NULL;
	return (NULL);
}

t_vct2 line_percent(t_vct2 pos1, t_vct2 pos2, double percent)
{
	t_vct2 middle;

	middle.x = pos1.x - (pos1.x - pos2.x) * percent;
	middle.y = pos1.y - (pos1.y - pos2.y) * percent;
	return (middle);
}

int opt_menu_click(t_editor *edit, int pos)
{
	pos = pos / SECTORBOXHEIGHT;
	if (pos == 0)
	{
		if (edit->map && !edit->currstat)
			edit->selecttxtr = FILL_TXTR;
		else if (edit->currstat && MINPROPSPOS <= edit->currstat->type && edit->currstat->type < MAXPROPSPOS)
			edit->selecttxtr = FILL_PROP;
		else if (edit->currstat && MINWPROPSPOS <= edit->currstat->type && edit->currstat->type < MAXWPROPSPOS)
			edit->selecttxtr = FILL_WPROP;
		else if (edit->currmur)
			edit->selecttxtr = FILL_TXTR;
	}
	else if (pos == 1)
	{
		if (edit->currstat && edit->currstat != &edit->player.stat)
		{
			if(edit->currmur)
				ft_removeenemywithstat(&edit->currmur->wproplist, &edit->currstat);
			else
				ft_removeenemywithstat(&edit->ennlist, &edit->currstat);
			edit->selecttxtr = NOSELECT;
		}
		else if (edit->currmur)
		{
			if (edit->currmur->portal_ptr)
				edit->currmur->portal_id = pos;
			else
				ft_enemypushend(&edit->currmur->wproplist, line_percent(edit->currmur->pil1->pos, edit->currmur->pil2->pos, 0.50), MINWPROPSPOS, NULL);
		}
		else if (edit->map && !edit->currstat)
			edit->selecttxtr = FILL_SOL;
	}
	else if (pos == 2)
	{
		if (edit->currmur && edit->currmur->portal_ptr)
			edit->currmur->portal_id = pos;
	}
	else if (pos == 3)
	{
		if (edit->currmur && edit->currmur->portal_ptr)
			edit->currmur->portal_id = pos;
	}
	else if (pos == 4)
	{
		if (edit->currmur && edit->currmur->portal_ptr)
			edit->currmur->portal_id = pos;
		else if (edit->map && !edit->currstat)
			edit->map->gravity = (edit->map->gravity ? 0 : 1);
	}
	else
	{
		edit->selecttxtr = NOSELECT;
	}
	return (0);
}

SDL_Texture *txtr_menu_click(t_editor *editor, int x, int y, int max)
{
	SDL_Rect tmp;
	int i;

	tmp.x = editor->txtrbox.x + PADDING;
	tmp.y = editor->txtrbox.y + PADDING + editor->txtrscroll;
	tmp.w = 200;
	tmp.h = 200;
	i = 0;
	while (i < max && editor->txtrgame[i])
	{
		if (pos_in_rect(tmp, x, y))
			return (editor->txtrgame[i]);
		tmp.x += tmp.w + PADDING;
		if (editor->txtrbox.x + editor->txtrbox.w < tmp.x + tmp.w)
		{
			tmp.x = editor->txtrbox.x + PADDING;
			tmp.y += tmp.h + PADDING;
		}
		++i;
	}
	return (NULL);
}

int txtr_menu_click_int(t_editor *editor, int x, int y, int pos, int max)
{
	SDL_Rect tmp;
	int i;

	tmp.x = editor->txtrbox.x + PADDING;
	tmp.y = editor->txtrbox.y + PADDING + editor->txtrscroll;
	tmp.w = 200;
	tmp.h = 200;
	i = 0;
	while (i < max)
	{
		if (pos_in_rect(tmp, x, y))
			return (i + pos);
		tmp.x += tmp.w + PADDING;
		if (editor->txtrbox.x + editor->txtrbox.w < tmp.x + tmp.w)
		{
			tmp.x = editor->txtrbox.x + PADDING;
			tmp.y += tmp.h + PADDING;
		}
		++i;
	}
	return (0);
}
