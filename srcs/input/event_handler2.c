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
//	void	*tmp;
//	int		pitch;

	(void)doom;
	//PrintEvent(&e);
/*	SDL_GetWindowSize(doom->sdl.win, &(doom->sdl.size.x), &(doom->sdl.size.y));
	if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED
		|| e.window.event == SDL_WINDOWEVENT_RESIZED)
	{
		if (doom->sdl.txture)
			SDL_DestroyTexture(doom->sdl.txture);
		doom->sdl.txture = SDL_CreateTexture(doom->sdl.rend,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
			doom->sdl.size.x, doom->sdl.size.y);
		if (SDL_LockTexture(doom->sdl.txture, NULL, &tmp, &pitch))
			doom_exit(doom);
		doom->sdl.screen = (uint32_t *)tmp;
		draw_menu(doom);
	}
	else */
	if (e.window.event == SDL_WINDOWEVENT_CLOSE)
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
		editor_mouse_press(e.button.button, e.button.x, e.button.y, doom);
	else if (e.type == SDL_MOUSEBUTTONUP)
		editor_mouse_release(e.button.button, e.button.x, e.button.y, doom);
	return (0);
}
