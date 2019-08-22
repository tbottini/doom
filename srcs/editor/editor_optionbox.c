/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_optionbox.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 17:07:24 by magrab            #+#    #+#             */
/*   Updated: 2019/08/12 15:49:37 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	if_pos_zero(t_editor *edit)
{
	if (edit->map && !edit->currstat)
		edit->selecttxtr = FILL_TXTR;
	else if (edit->currstat && ISPROP(edit->currstat->type))
		edit->selecttxtr = FILL_PROP;
	else if (edit->currstat && ISWALLPROP(edit->currstat->type))
		edit->selecttxtr = FILL_WPROP;
	else if (edit->currmur)
		edit->selecttxtr = FILL_TXTR;
	edit->txtrscroll = 0;
}

static void	if_pos_one(t_editor *edit)
{
	if (edit->currstat && edit->currstat != &edit->player.stat)
	{
		if (edit->currmur)
			ft_removeenemywithstat(&edit->currmur->wproplist, &edit->currstat);
		else
			ft_removeenemywithstat(&edit->ennlist, &edit->currstat);
		edit->selecttxtr = NOSELECT;
	}
	else if (edit->currmur)
	{
		if (edit->currmur->portal_ptr)
			edit->currmur->portal_id = WINDOW;
		else
			ft_enemypushend(&edit->currmur->wproplist,
				line_percent(edit->currmur->pil1->pos,
				edit->currmur->pil2->pos, 0.50), MINWPROPSPOS, NULL);
	}
	else if (edit->map && !edit->currstat)
		edit->selecttxtr = FILL_SOL;
}

static void	lil_opt_menu_click(t_editor *edit, int pos)
{
	if (pos == 5)
	{
		if (edit->currmur && edit->currmur->portal_ptr)
			edit->currmur->level = 0;
	}
	else if (pos == 6)
	{
		if (edit->currmur && edit->currmur->portal_ptr)
			edit->currmur->level = 1;
	}
	else if (pos == 7)
	{
		if (edit->currmur && edit->currmur->portal_ptr)
			edit->currmur->level = 2;
	}
	else if (pos == 8)
	{
		if (edit->currmur && edit->currmur->portal_ptr)
			edit->currmur->level = 3;
	}
	else
	{
		edit->selecttxtr = NOSELECT;
	}
}

static void	action_at_pos(t_editor *edit, t_portal_id newtype, int *towrite)
{
	if (edit->currmur && edit->currmur->portal_ptr)
		edit->currmur->portal_id = newtype;
	else if (edit->map && !edit->currmur && !edit->currstat)
	{
		edit->currwriter = towrite;
		edit->status = ED_WRITING;
	}
}

int			opt_menu_click(t_editor *edit, int pos)
{
	pos = pos / SBH;
	if (pos == 0)
		if_pos_zero(edit);
	else if (pos == 1)
		if_pos_one(edit);
	else if (pos == 2)
		action_at_pos(edit, CLOSE_DOOR, &edit->map->htop);
	else if (pos == 3)
		action_at_pos(edit, OPEN_DOOR, &edit->map->hsol);
	else if (pos == 4)
	{
		if (edit->currmur && edit->currmur->portal_ptr)
			edit->currmur->portal_id = PORTAL;
		else if (edit->map && !edit->currstat)
			edit->map->gravity = (edit->map->gravity ? 0 : 1);
	}
	else
		lil_opt_menu_click(edit, pos);
	return (0);
}
