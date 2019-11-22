/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler_doom.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:33:51 by magrab            #+#    #+#             */
/*   Updated: 2019/08/26 17:01:27 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		resize_event(t_doom *doom)
{
	doom->game.camera.d_screen = (doom->sdl.size.x / 2.0)
	/ tan(doom->game.player.fov / 2.0 * PI180);
	fire_init(doom);
	draw_menu(doom);
}

static void	event2(t_doom *d, SDL_Event e, bool f)
{
	if (f)
	{
		if (d->ui.m_status == MENU_MAP)
		{
			load_map_btns(d);
			draw_menu(d);
		}
		else if (d->ui.m_status == MENU_IGMAIN
			|| d->ui.m_status == MENU_IGOPTION)
			doom_render(d);
	}
	else
	{
		if (d->ui.m_status == MENU_INGAME)
			mouse_move(e.motion.xrel, e.motion.yrel, d);
		else
			mouse_move(e.motion.x, e.motion.y, d);
	}
}

static void	window_event(t_doom *d, SDL_Event e)
{
	void	*tmp;
	int		pitch;

	if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED
		|| e.window.event == SDL_WINDOWEVENT_RESIZED)
	{
		SDL_GetWindowSize(d->sdl.win, &(d->sdl.size.x), &(d->sdl.size.y));
		d->sdl.size.x % 4 ? SDL_SetWindowSize(d->sdl.win, d->sdl.size.x +=
			d->sdl.size.x % 4, d->sdl.size.y) : 0;
		d->sdl.txture ? SDL_DestroyTexture(d->sdl.txture) : 0;
		d->sdl.txture = SDL_CreateTexture(d->sdl.rend, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING, d->sdl.size.x, d->sdl.size.y);
		SDL_LockTexture(d->sdl.txture, NULL, &tmp, &pitch) ? doom_exit(d) : 0;
		d->sdl.screen = (Uint32 *)tmp;
		resize_event(d);
	}
	else if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST
	&& d->ui.m_status == MENU_INGAME)
		sdl_set_status(d, MENU_IGMAIN);
	else if (e.window.event == SDL_WINDOWEVENT_CLOSE)
		doom_exit(d);
	event2(d, e, true);
}

void		dropfile_event(t_doom *doom, SDL_Event e)
{
	(void)doom;
	SDL_free(e.drop.file);
}

/*
** Here are event which trigger on win1 (game window)
** New event shouldn't be needed
*/

int			event_handler_doom(t_doom *doom, SDL_Event e)
{
	if (doom->edit.status)
		doom->edit.status = ED_CLOSED;
	if (e.type == SDL_QUIT)
		doom_exit(doom);
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		if (!doom->ui.m_status)
			game_key_press(e.key.keysym.sym, doom);
		else
			key_press(e.key.keysym.sym, doom);
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		key_release(e.key.keysym.sym, doom);
	else if (e.type == SDL_WINDOWEVENT)
		window_event(doom, e);
	else if (e.type == SDL_MOUSEMOTION)
		event2(doom, e, false);
	else if (e.type == SDL_MOUSEBUTTONDOWN)
		mouse_press(e.button.button, e.button.x, e.button.y, doom);
	else if (e.type == SDL_MOUSEBUTTONUP)
		mouse_release(e.button.button, e.button.x, e.button.y, doom);
	else if (e.type == SDL_MOUSEWHEEL)
		mouse_wheel(e.wheel, doom);
	return (0);
}
