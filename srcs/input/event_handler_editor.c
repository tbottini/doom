/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler_editor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:33:51 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 07:00:40 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	window_event(t_doom *doom, SDL_Event e)
{
	t_vct2 tmp;

	if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED
	|| e.window.event == SDL_WINDOWEVENT_RESIZED)
	{
		tmp = doom->edit.size;
		SDL_GetWindowSize(doom->edit.win,
		&(doom->edit.size.x), &(doom->edit.size.y));
		doom->edit.mappos.x += (doom->edit.size.x - tmp.x) / 2;
		doom->edit.mappos.y += (doom->edit.size.y - tmp.y) / 2;
		doom->edit.sectbox.h = doom->edit.size.y - doom->edit.sectbox.y;
		doom->edit.optbox.h = doom->edit.size.y - doom->edit.optbox.y;
		doom->edit.optbox.x = doom->edit.size.x - doom->edit.optbox.w;
		doom->edit.txtrbox.x = doom->edit.size.x
		/ 2.1 - doom->edit.txtrbox.w / 2;
		doom->edit.txtrbox.h = doom->edit.size.y - doom->edit.txtrbox.y;
	}
	else if (e.window.event == SDL_WINDOWEVENT_CLOSE)
		close_editor(doom);
}

/*
** Here are event which trigger on win2 (editor window)
** New event shouldn't be needed
*/

int			event_handler_editor(t_doom *doom, SDL_Event e)
{
	if (!doom->edit.status)
		doom->edit.status = ED_LOADED;
	if (e.type == SDL_QUIT)
		return (close_editor(doom));
	else if (e.type == SDL_WINDOWEVENT)
		window_event(doom, e);
	else if (ISWRITING(doom->edit.status))
	{
		if (e.type == SDL_KEYDOWN)
			write_hook(doom, doom->edit.filename, e.key);
	}
	else
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			editor_key_press(e.key.keysym.sym, doom);
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
			editor_key_release(e.key.keysym.sym, doom);
		else if (e.type == SDL_MOUSEMOTION)
			editor_mouse_move(e.motion, &doom->edit);
		else if (e.type == SDL_MOUSEBUTTONDOWN)
			editor_mouse_press(e.button, &doom->edit);
		else if (e.type == SDL_MOUSEWHEEL)
			editor_mouse_wheel(e.wheel, &(doom->edit));
	}
	return (0);
}
