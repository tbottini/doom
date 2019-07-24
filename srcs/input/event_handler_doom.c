/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler_doom.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:33:51 by magrab            #+#    #+#             */
/*   Updated: 2019/07/24 21:05:18 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		resize_event(t_doom *doom)
{
	doom->game.camera.d_screen = (doom->sdl.size.x / 2.0) / tan(doom->game.player.fov / 2.0 * PI180);
	fire_init(doom);
	draw_menu(doom);
}

static void window_event(t_doom *doom, SDL_Event e)
{
	void *tmp;
	int pitch;

	//PrintEvent(&e);
	if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED || e.window.event == SDL_WINDOWEVENT_RESIZED)
	{
		SDL_GetWindowSize(doom->sdl.win, &(doom->sdl.size.x), &(doom->sdl.size.y));
		if (doom->sdl.size.x % 4) // Pour le Multithreading (Lignes noires si pas fait)
			SDL_SetWindowSize(doom->sdl.win, doom->sdl.size.x += doom->sdl.size.x % 4, doom->sdl.size.y);
		if (doom->sdl.txture)
			SDL_DestroyTexture(doom->sdl.txture);
		doom->sdl.txture = SDL_CreateTexture(doom->sdl.rend,
				SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
						doom->sdl.size.x, doom->sdl.size.y);
		if (SDL_LockTexture(doom->sdl.txture, NULL, &tmp, &pitch))
			doom_exit(doom);
		doom->sdl.screen = (Uint32 *)tmp;
		resize_event(doom);
	}
	else if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST && doom->ui.m_status == 0)
		sdl_set_status(doom, 4);
	else if (e.window.event == SDL_WINDOWEVENT_CLOSE)
		doom_exit(doom);
	if (doom->ui.m_status == 2)
	{
		load_map_btns(doom);
		draw_menu(doom);
	}
	else if (doom->ui.m_status == 4 || doom->ui.m_status == 5)
		doom_render(doom);
}

void dropfile_event(t_doom *doom, SDL_Event e)
{
	(void)doom;
	//if (doom->map)
	//	doom_clear_map(doom);
	//if (doom_parseur(doom, e.drop.file))
	//{
	//	sdl_set_status(doom, 0);
	//}
	//else
	//{
	//	ft_printf("Error Reading File Drop\n");
	//	sdl_set_status(doom, 1);
	//}
	SDL_free(e.drop.file);
}

/*
** Here are event which trigger on win1 (game window)
** New event shouldn't be needed
*/

int event_handler_doom(t_doom *doom, SDL_Event e)
{
	if (doom->edit.status)
		doom->edit.status = ED_CLOSED;
	if (e.type == SDL_QUIT)
		doom_exit(doom);
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		game_key_press(e.key.keysym.sym, doom);
		key_press(e.key.keysym.sym, doom);
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		key_release(e.key.keysym.sym, doom);
	else if (e.type == SDL_WINDOWEVENT)
		window_event(doom, e);
	else if (e.type == SDL_CONTROLLERDEVICEADDED)
	{
		if (!(doom->controller) && SDL_NumJoysticks() && SDL_IsGameController(0))
			doom->controller = SDL_GameControllerOpen(0);
	}
	else if (e.type == SDL_CONTROLLERDEVICEREMOVED && doom->controller)
		SDL_GameControllerClose(doom->controller);
	else if (e.type == SDL_MOUSEMOTION)
	{
		if (doom->ui.m_status == 0)
			mouse_move(e.motion.xrel, e.motion.yrel, doom);
		else
			mouse_move(e.motion.x, e.motion.y, doom);
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN)
		mouse_press(e.button.button, e.button.x, e.button.y, doom);
	else if (e.type == SDL_MOUSEBUTTONUP)
		mouse_release(e.button.button, e.button.x, e.button.y, doom);
	else if (e.type == SDL_MOUSEWHEEL)
		mouse_press((e.wheel.y > 0 ? 4 : 5), doom->sdl.m_pos.x, doom->sdl.m_pos.y, doom);
	return (0);
}
