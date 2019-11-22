/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_mouse_wheel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 00:56:57 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 00:56:58 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Add here function that need to be done when mouse wheel is used
*/

static int	in_sectbox(SDL_MouseWheelEvent e, t_editor *edit)
{
	if (edit->sectscroll + e.y * 2 > 0)
		edit->sectscroll = 0;
	else
		edit->sectscroll += e.y * 2;
	return (0);
}

static int	in_txtrbox(SDL_MouseWheelEvent e, t_editor *edit)
{
	if (edit->txtrscroll + e.y * 2 > 0)
		edit->txtrscroll = 0;
	else
		edit->txtrscroll += e.y * 2;
	return (0);
}

static int	on_wall_prop(SDL_MouseWheelEvent e, t_editor *edit)
{
	if (edit->currstat->roty + e.y < 0)
		edit->currstat->roty = 0.0;
	else if (edit->currstat->roty + e.y > 100)
		edit->currstat->roty = 100.0;
	else
		edit->currstat->roty += e.y;
	edit->currstat->pos = line_percent(edit->currmur->pil1->pos,
		edit->currmur->pil2->pos, edit->currstat->roty / 100);
	return (0);
}

static int	on_prop(SDL_MouseWheelEvent e, t_editor *edit)
{
	if (edit->currstat->roty + e.y < 0)
		edit->currstat->roty += e.y + 360.0;
	else if (edit->currstat->roty + e.y > 360)
		edit->currstat->roty += e.y - 360.0;
	else
		edit->currstat->roty += e.y;
	return (0);
}

int			editor_mouse_wheel(SDL_MouseWheelEvent e, t_editor *edit)
{
	if (pos_in_rect(edit->sectbox, edit->mouse.x, edit->mouse.y))
		return (in_sectbox(e, edit));
	else if (pos_in_rect(edit->optbox, edit->mouse.x, edit->mouse.y))
		return (opt_menu_wheel(e, edit));
	else if (edit->selecttxtr && pos_in_rect(edit->txtrbox,
		edit->mouse.x, edit->mouse.y))
		return (in_txtrbox(e, edit));
	if (edit->currstat && edit->currmur && (ISWALLPROP(edit->currstat->type)))
		return (on_wall_prop(e, edit));
	else if (edit->currstat && !(ISPROP(edit->currstat->type)))
		return (on_prop(e, edit));
	scroll_limits(&edit->mappos.z,
		e.y * (edit->mappos.z / 400 * ZOOMSPEED + 1), MINZOOM, MAXZOOM);
	return (0);
}
