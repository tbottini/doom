/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:22:11 by magrab            #+#    #+#             */
/*   Updated: 2019/08/04 14:46:34 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "render.h"

void		draw_objs(t_editor *editor, t_entity *start)
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

static void	draw_pills(t_editor *editor)
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

static void	draw_txtrselector(t_editor *editor, int max, SDL_Texture **txtrs)
{
	SDL_Rect	tmp;
	int			x;

	SDL_SetRenderDrawColor(editor->rend, 50, 50, 50, 255);
	SDL_RenderFillRect(editor->rend, &editor->txtrbox);
	x = 0;
	tmp.x = editor->txtrbox.x + EDPADDING;
	tmp.y = editor->txtrbox.y + EDPADDING + editor->txtrscroll;
	tmp.w = TXTRSIZE;
	tmp.h = TXTRSIZE;
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
}

static void	draw_walls(t_editor *editor)
{
	t_lstsec currsec;
	t_lstmur currwall;
	t_lstsec finalsec;

	finalsec = NULL;
	currsec = editor->sectors;
	while (currsec)
	{
		if (currsec != editor->map)
			norm_draw_walls(editor, currsec);
		else
			finalsec = currsec;
		currsec = currsec->next;
	}
	if (finalsec)
	{
		currwall = finalsec->murs;
		while (currwall)
		{
			draw_one_wall(editor, currwall);
			currwall = currwall->next;
		}
	}
}

void		draw_map(t_editor *editor)
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
