/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:22:11 by magrab            #+#    #+#             */
/*   Updated: 2019/07/16 14:22:12 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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
		if (ISPROP(curr->stat.type))
			draw_props(editor, curr, editor->sprites, MINPROPSPOS);
		else if (ISWALLPROP(curr->stat.type))
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

static void draw_txtrselector(t_editor *editor, int max, SDL_Texture **txtrs)
{
	SDL_Rect tmp;
	int x;

	SDL_SetRenderDrawColor(editor->rend, 50, 50, 50, 255);
	SDL_RenderFillRect(editor->rend, &editor->txtrbox);
	x = 0;
	tmp.x = editor->txtrbox.x + EDPADDING;
	tmp.y = editor->txtrbox.y + EDPADDING + editor->txtrscroll;
	tmp.w = 200;
	tmp.h = 200;
	SDL_SetRenderDrawColor(editor->rend, 255, 200, 200, 255);
	while (x < max && txtrs[x])
	{
		SDL_RenderCopy(editor->rend, txtrs[x], NULL, &tmp);
		tmp.x += tmp.w + EDPADDING;
		if (editor->txtrbox.x + editor->txtrbox.w < tmp.x + tmp.w)
		{
			tmp.x = editor->txtrbox.x + EDPADDING;
			tmp.y += tmp.h + EDPADDING;
		}
		++x;
	}
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 255);
	SDL_RenderFillRect(editor->rend, &tmp);
	SDL_SetRenderDrawColor(editor->rend, 255, 255, 255, 255);
	SDL_RenderDrawRect(editor->rend, &tmp);
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
			else if (editor->currstat && editor->currstat->mur == currwall)
				map_draw_line(editor, currwall->pil1->pos, currwall->pil2->pos, (SDL_Color){75, 100, 255, 0xFF});
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
			else if (ISPROP(editor->currstat->type))
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
		else if (ISPROP(editor->currstat->type)) // If Prop
		{
			sdl_int_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + 5}, "Type: ", editor->currstat->type - MINPROPSPOS, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
			sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT + 5}, "Delete", (SDL_Color){255, 100, 100, 0xFF});
		}
		else if (ISWALLPROP(editor->currstat->type)) // If Wall Prop
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
		sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + 5}, "Ceil:", (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
		txtrpos = (SDL_Rect){box.x + 120, box.y + 4, SECTORBOXHEIGHT - 2, SECTORBOXHEIGHT - 2};
		SDL_RenderCopy(editor->rend, editor->map->top, NULL, &txtrpos);
		sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT + 5}, "Floor:", (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
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
