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

int opt_menu_wheel(SDL_MouseWheelEvent e, t_editor *edit)
{
	e.x = (edit->mouse.y - edit->sectscroll) / SECTORBOXHEIGHT;
	if (e.x == 0 && edit->currstat)
	{
		if (edit->currstat == &edit->player.stat)
			scroll_limits(&edit->currstat->type, e.y, 10, 250);
		else if (ISPROP(edit->currstat->type))
			scroll_limits(&edit->currstat->type, e.y, MINPROPSPOS, MAXPROPSPOS);
		else if (ISWALLPROP(edit->currstat->type))
			scroll_limits(&edit->currstat->type, e.y, MINWPROPSPOS, MAXWPROPSPOS);
	}
	else if (e.x == 2 && edit->map)
		scroll_limits(&edit->map->htop, e.y * 5, 0, MAXEDITVAR);
	else if (e.x == 3 && edit->map)
		scroll_limits(&edit->map->hsol, e.y * 5, 0, MAXEDITVAR);
	return (0);
}

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
		edit->txtrscroll = 0;
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
				edit->currmur->portal_id = WINDOW;
			else
				ft_enemypushend(&edit->currmur->wproplist, line_percent(edit->currmur->pil1->pos, edit->currmur->pil2->pos, 0.50), MINWPROPSPOS, NULL);
		}
		else if (edit->map && !edit->currstat)
			edit->selecttxtr = FILL_SOL;
	}
	else if (pos == 2)
	{
		if (edit->currmur && edit->currmur->portal_ptr)
			edit->currmur->portal_id = CLOSE_DOOR;
		else if (edit->map && !edit->currmur && !edit->currstat)
		{
			edit->currwriter = &edit->map->htop;
			edit->status = ED_WRITING;
		}
	}
	else if (pos == 3)
	{
		if (edit->currmur && edit->currmur->portal_ptr)
			edit->currmur->portal_id = OPEN_DOOR;
		else if (edit->map && !edit->currmur && !edit->currstat)
		{
			edit->currwriter = &edit->map->hsol;
			edit->status = ED_WRITING;
		}
	}
	else if (pos == 4)
	{
		if (edit->currmur && edit->currmur->portal_ptr)
			edit->currmur->portal_id = PORTAL;
		else if (edit->map && !edit->currstat)
			edit->map->gravity = (edit->map->gravity ? 0 : 1);
	}
	else if (pos == 5)
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
	return (0);
}
