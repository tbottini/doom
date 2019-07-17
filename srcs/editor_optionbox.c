/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_optionbox.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 17:07:24 by magrab            #+#    #+#             */
/*   Updated: 2019/07/17 17:07:25 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int opt_menu_wheel(SDL_MouseWheelEvent e, t_editor *edit)
{
	e.x = (edit->mouse.y - edit->sectscroll) / SECTORBOXHEIGHT;
	if (e.x == 0 && edit->currstat)
	{
		if (edit->currstat == &edit->player.stat)
		{
			if (edit->currstat->type + e.y < 10)
				edit->currstat->type = 10;
			else if (edit->currstat->type + e.y > 250)
				edit->currstat->type = 250;
			else
				edit->currstat->type += e.y;
		}
		if (ISPROP(edit->currstat->type))
		{
			if (edit->currstat->type + e.y < MINPROPSPOS)
				edit->currstat->type = MINPROPSPOS;
			else if (edit->currstat->type + e.y >= MAXPROPSPOS)
				edit->currstat->type = MAXPROPSPOS - 1;
			else
				edit->currstat->type += e.y;
		}
		else if (ISWALLPROP(edit->currstat->type))
		{
			if (edit->currstat->type + e.y < MINWPROPSPOS)
				edit->currstat->type = MINWPROPSPOS;
			else if (edit->currstat->type + e.y >= MAXWPROPSPOS)
				edit->currstat->type = MAXWPROPSPOS - 1;
			else
				edit->currstat->type += e.y;
		}
	}
	else if (e.x == 2 && edit->map)
	{
		if (edit->map->htop + e.y * 5 < 0)
			edit->map->htop = 0;
		else
			edit->map->htop += e.y * 5;
	}
	else if (e.x == 3 && edit->map)
	{
		if (edit->map->hsol + e.y * 5 < 0)
			edit->map->hsol = 0;
		else
			edit->map->hsol += e.y * 5;
	}
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
