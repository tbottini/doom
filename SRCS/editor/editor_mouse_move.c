/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_mouse_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 00:57:43 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 00:57:45 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int	move_optbox(SDL_MouseMotionEvent e, t_editor *edit)
{
	e.x = (e.y - edit->sectscroll) / SBH;
	if ((e.x == 0 && edit->currstat && edit->currstat == &edit->player.stat)
	|| (2 <= e.x && e.x <= 3 && edit->map && !edit->currstat && !edit->currmur)
		|| (e.x == 0 && edit->currstat && ISPROP(edit->currstat->type)))
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE));
	else
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
	return (0);
}

static void	move_left_press(SDL_MouseMotionEvent e, t_editor *edit)
{
	if (edit->currpilier)
	{
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL));
		ft_movepillar(edit->sectors, edit->currpilier,
			(t_vct2){e.xrel, e.yrel}, edit->mappos.z);
	}
	else if (edit->currstat)
	{
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL));
		if (!(edit->currmur))
		{
			edit->currstat->pos.x += e.xrel * (EDITPREC) / edit->mappos.z;
			edit->currstat->pos.y += e.yrel * (EDITPREC) / edit->mappos.z;
		}
	}
	else if (edit->currmur)
	{
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL));
		ft_movewall(edit->currmur, e.xrel, e.yrel, edit->mappos.z);
	}
}

static void	lil_editor_mouse_move(SDL_MouseMotionEvent e, t_editor *edit)
{
	if (edit->hoverpilier || edit->hovermur)
	{
		if (e.state == SDL_BUTTON_RMASK
			&& edit->hoverpilier && !edit->currpilier)
		{
			ft_remove_pillar_from_sector(edit, edit->sectors, &edit->pillist,
				&edit->hoverpilier);
			edit->hovermur = NULL;
		}
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
	}
	else
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
	if (e.state == SDL_BUTTON_LMASK)
		move_left_press(e, edit);
	else if (e.state == SDL_BUTTON_MMASK)
	{
		edit->mappos.x += e.xrel;
		edit->mappos.y += e.yrel;
	}
}

/*
** Add here function that need to be done when mouse if moved in window
*/

int			editor_mouse_move(SDL_MouseMotionEvent e, t_editor *edit)
{
	edit->mouse.x = e.x;
	edit->mouse.y = e.y;
	if (pos_in_rect(edit->sectbox, e.x, e.y))
	{
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
		return (0);
	}
	else if (pos_in_rect(edit->optbox, e.x, e.y))
		return (move_optbox(e, edit));
	else if (edit->selecttxtr && pos_in_rect(edit->txtrbox, e.x, e.y))
		return (0);
	edit->mapmouse = g_r_mp(edit, e.x, e.y);
	if (!(edit->hoverpilier = find_pilier(edit, edit->pillist, e.x, e.y)))
		edit->hovermur = find_mur(edit, edit->map, e.x, e.y);
	else
		edit->hovermur = NULL;
	lil_editor_mouse_move(e, edit);
	return (0);
}
