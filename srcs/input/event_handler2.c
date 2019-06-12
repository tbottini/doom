/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:33:51 by magrab            #+#    #+#             */
/*   Updated: 2019/05/05 15:45:29 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void		window_event(t_doom *doom, SDL_Event e)
{
	t_vct2 tmp;

	if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED || e.window.event == SDL_WINDOWEVENT_RESIZED)
	{
		tmp = doom->edit.size;
		SDL_GetWindowSize(doom->edit.win, &(doom->edit.size.x), &(doom->edit.size.y));
		doom->edit.mappos.x += (doom->edit.size.x - tmp.x) / 2;
		doom->edit.mappos.y += (doom->edit.size.y - tmp.y) / 2;
		doom->edit.sectbox.h = doom->edit.size.y - doom->edit.sectbox.y - doom->edit.sectbox.x;
		
	}
	else if (e.window.event == SDL_WINDOWEVENT_CLOSE)
	{
		close_editor(doom);
	}
}

/*
** Here are event which trigger on win2 (editor window)
** New event shouldn't be needed
*/

int event_handler2(t_doom *doom, SDL_Event e)
{
	if (doom->edit.status != 1)
		doom->edit.status = 1;
	if (e.type == SDL_QUIT)
		return (close_editor(doom));
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
		doom_exit(doom);
	else if (e.type == SDL_WINDOWEVENT)
		window_event(doom, e);
	else if (e.type == SDL_CONTROLLERDEVICEADDED)
	{
		if (!(doom->controller) && SDL_NumJoysticks() && SDL_IsGameController(0))
			doom->controller = SDL_GameControllerOpen(0);
	}
	else if (e.type == SDL_CONTROLLERDEVICEREMOVED && doom->controller)
		SDL_GameControllerClose(doom->controller);
	else if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		editor_key_press(e.key.keysym.sym, doom);
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		editor_key_release(e.key.keysym.sym, doom);
	else if (e.type == SDL_MOUSEMOTION)
		editor_mouse_move(e.motion, doom);
	else if (e.type == SDL_MOUSEBUTTONDOWN)
		editor_mouse_press(e.button.button, e.button.x, e.button.y, &doom->edit);
	else if (e.type == SDL_MOUSEWHEEL)
		editor_mouse_wheel(e.wheel, &(doom->edit));
	else if (e.type == SDL_MOUSEBUTTONUP)
		editor_mouse_release(e.button.button, e.button.x, e.button.y, doom);
	return (0);
}
