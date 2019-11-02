/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_txtrbox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 17:11:06 by magrab            #+#    #+#             */
/*   Updated: 2019/07/20 13:41:42 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

SDL_Texture	*txtr_menu_click(t_editor *editor, int x, int y, int max)
{
	SDL_Rect	tmp;
	int			i;

	tmp.x = editor->txtrbox.x + EDPADDING;
	tmp.y = editor->txtrbox.y + EDPADDING + editor->txtrscroll;
	tmp.w = TXTRSIZE;
	tmp.h = TXTRSIZE;
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

int			txtr_menu_click_int(t_editor *editor, t_vct2 m, int pos, int max)
{
	SDL_Rect	tmp;
	int			i;

	tmp.x = editor->txtrbox.x + EDPADDING;
	tmp.y = editor->txtrbox.y + EDPADDING + editor->txtrscroll;
	tmp.w = TXTRSIZE;
	tmp.h = TXTRSIZE;
	i = 0;
	while (i < max)
	{
		if (pos_in_rect(tmp, m.x, m.y))
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

static void	lil_texturebox_click(t_editor *edit, SDL_MouseButtonEvent e)
{
	SDL_Texture *txtrclick;

	if ((edit->selecttxtr == FILL_TXTR || edit->selecttxtr == FILL_SOL)
		&& (txtrclick = txtr_menu_click(edit, e.x, e.y, MAXTXTRNUMBER)))
	{
		if (edit->currmur)
			edit->currmur->txtr = txtrclick;
		else if (edit->map)
		{
			if (edit->selecttxtr == FILL_TXTR)
				edit->map->top = txtrclick;
			else if (edit->selecttxtr == FILL_SOL)
				edit->map->sol = txtrclick;
		}
		edit->selecttxtr = NOSELECT;
	}
}

int			texturebox_click(t_editor *edit, SDL_MouseButtonEvent e)
{
	if (edit->selecttxtr == FILL_PROP && edit->currstat
		&& ISPROP(edit->currstat->type) && (e.x = txtr_menu_click_int(edit,
		(t_vct2){e.x, e.y}, MINPROPSPOS, MAXPROPSNUMBER)))
	{
		edit->currstat->type = e.x;
		edit->selecttxtr = NOSELECT;
	}
	else if (edit->selecttxtr == FILL_WPROP && edit->currstat
		&& ISWALLPROP(edit->currstat->type)
		&& (e.x = txtr_menu_click_int(edit, (t_vct2){e.x, e.y},
		MINWPROPSPOS, MAXWPROPSNUMBER)))
	{
		edit->currstat->type = e.x;
		edit->selecttxtr = NOSELECT;
	}
	else
		lil_texturebox_click(edit, e);
	return (0);
}
