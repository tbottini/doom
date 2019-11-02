/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/07/11 21:01:47 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_ecoord		*find_player(t_editor *edit, int x, int y)
{
	t_vct2		loc;
	SDL_Rect	ppos;
	t_entity	*curr;

	loc = get_screen_mappos(edit, edit->player.stat.pos.x,
		edit->player.stat.pos.y);
	ppos = (SDL_Rect){loc.x - 10, loc.y - 10, 20, 20};
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

t_pilier		*find_pilier(t_editor *editor, t_lstpil start, int x, int y)
{
	t_pilier	*curr;
	t_vct2		p;

	curr = start;
	p = g_r_mp(editor, x, y);
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

static SDL_Rect	init_locator(t_mur *curr, int precs)
{
	SDL_Rect	tbox;

	tbox.x = (curr->pil1->pos.x < curr->pil2->pos.x ?
			curr->pil1->pos.x : curr->pil2->pos.x);
	tbox.y = (curr->pil1->pos.y < curr->pil2->pos.y ?
			curr->pil1->pos.y : curr->pil2->pos.y);
	tbox.w = (curr->pil1->pos.x > curr->pil2->pos.x ?
			curr->pil1->pos.x : curr->pil2->pos.x) - tbox.x + precs * 8;
	tbox.h = (curr->pil1->pos.y > curr->pil2->pos.y ?
			curr->pil1->pos.y : curr->pil2->pos.y) - tbox.y + precs * 8;
	tbox.x -= precs * 4;
	tbox.y -= precs * 4;
	return (tbox);
}

static bool		check_on_line(t_mur *curr, int precs, t_vct2 p)
{
	t_fvct2		coef;

	coef.x = (double)(curr->pil1->pos.y - curr->pil2->pos.y)
		/ (double)(curr->pil1->pos.x - curr->pil2->pos.x);
	coef.y = (double)curr->pil1->pos.y - (double)curr->pil1->pos.x * coef.x;
	if (p.y >= (p.x * coef.x + coef.y) - precs * 4
			&& p.y <= (p.x * coef.x + coef.y) + precs * 4)
		return (true);
	coef.x = (double)(curr->pil1->pos.x - curr->pil2->pos.x)
		/ (double)(curr->pil1->pos.y - curr->pil2->pos.y);
	coef.y = (double)curr->pil1->pos.x - (double)curr->pil1->pos.y * coef.x;
	if (p.x >= (p.y * coef.x + coef.y) - precs * 4
			&& p.x <= (p.y * coef.x + coef.y) + precs * 4)
		return (true);
	return (false);
}

t_mur			*find_mur(t_editor *editor, t_lstsec start, int x, int y)
{
	SDL_Rect	tbox;
	t_mur		*curr;
	t_vct2		p;
	int			precs;

	if (!start)
		return (NULL);
	curr = start->murs;
	p = g_r_mp(editor, x, y);
	precs = (EDITPREC) / editor->mappos.z + 1;
	while (curr)
	{
		tbox = init_locator(curr, precs);
		if (pos_in_rect(tbox, p.x, p.y))
		{
			if (check_on_line(curr, precs, p))
				return (curr);
		}
		if (curr->next != start->murs)
			curr = curr->next;
		else
			curr = NULL;
	}
	return (NULL);
}
