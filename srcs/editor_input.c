/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:30:42 by magrab            #+#    #+#             */
/*   Updated: 2019/07/16 14:30:43 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int opt_menu_click(t_editor *edit, int pos)
{
	pos = pos / SECTORBOXHEIGHT;
	if (pos == 0)
	{
		if (edit->map && !edit->currstat)
			edit->selecttxtr = FILL_TXTR;
		else if (edit->currstat && ISPROP(edit->currstat->type))
			edit->selecttxtr = FILL_PROP;
		else if (edit->currstat && ISWALLPROP(edit->currstat->type))
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

	tmp.x = editor->txtrbox.x + EDPADDING;
	tmp.y = editor->txtrbox.y + EDPADDING + editor->txtrscroll;
	tmp.w = 200;
	tmp.h = 200;
	i = 0;
	while (i < max && editor->txtrgame[i])
	{
		if (pos_in_rect(tmp, x, y))
			return (editor->txtrgame[i]);
		tmp.x += tmp.w + EDPADDING;
		if (editor->txtrbox.x + editor->txtrbox.w < tmp.x + tmp.w)
		{
			tmp.x = editor->txtrbox.x + EDPADDING;
			tmp.y += tmp.h + EDPADDING;
		}
		++i;
	}
	return (NULL);
}

int txtr_menu_click_int(t_editor *editor, int x, int y, int pos, int max)
{
	SDL_Rect tmp;
	int i;

	tmp.x = editor->txtrbox.x + EDPADDING;
	tmp.y = editor->txtrbox.y + EDPADDING + editor->txtrscroll;
	tmp.w = 200;
	tmp.h = 200;
	i = 0;
	while (i < max)
	{
		if (pos_in_rect(tmp, x, y))
			return (i + pos);
		tmp.x += tmp.w + EDPADDING;
		if (editor->txtrbox.x + editor->txtrbox.w < tmp.x + tmp.w)
		{
			tmp.x = editor->txtrbox.x + EDPADDING;
			tmp.y += tmp.h + EDPADDING;
		}
		++i;
	}
	return (0);
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
