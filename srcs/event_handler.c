/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:33:51 by magrab            #+#    #+#             */
/*   Updated: 2019/04/27 13:13:13 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		window_event(t_wolf *wolf, SDL_Event event)
{
	void	*tmp;
	int		pitch;

	SDL_GetWindowSize(wolf->sdl.win, &(wolf->sdl.size.x), &(wolf->sdl.size.y));
	if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED
		|| event.window.event == SDL_WINDOWEVENT_RESIZED)
	{
		if (wolf->sdl.txture)
			SDL_DestroyTexture(wolf->sdl.txture);
		wolf->sdl.txture = SDL_CreateTexture(wolf->sdl.rend,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
			wolf->sdl.size.x, wolf->sdl.size.y);
		if (SDL_LockTexture(wolf->sdl.txture, NULL, &tmp, &pitch))
			prog_quit(wolf);
		wolf->sdl.screen = (uint32_t *)tmp;
		draw_menu(wolf);
	}
	if (wolf->ui.m_status == 2)
	{
		load_map_btns(wolf);
		draw_menu(wolf);
	}
}

static void		dropfile_event(t_wolf *wolf, SDL_Event event)
{
	if (wolf->map)
		wolf_clear_map(wolf);
	if (wolf_parseur(wolf, event.drop.file))
	{
		wolf->ui.m_status = 0;
	}
	else
	{
		ft_printf("Error Reading File Drop\n");
		wolf->ui.m_status = 1;
		draw_menu(wolf);
	}
	SDL_free(event.drop.file);
}

void			lil_event_handler(t_wolf *wolf, SDL_Event event)
{
	if (event.type == SDL_MOUSEMOTION)
		mouse_move(event.motion.x, event.motion.y, wolf);
	else if (event.type == SDL_MOUSEBUTTONDOWN)
		mouse_press(event.button.button,
			event.button.x, event.button.y, wolf);
	else if (event.type == SDL_MOUSEBUTTONUP)
		mouse_release(event.button.button,
			event.button.x, event.button.y, wolf);
	else if (event.type == SDL_MOUSEWHEEL)
		mouse_press((event.wheel.y > 0 ? 4 : 5),
			wolf->sdl.m_pos.x, wolf->sdl.m_pos.y, wolf);
}

int				event_handler(t_wolf *wolf)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN
									&& event.key.keysym.sym == SDLK_ESCAPE))
			return (prog_quit(wolf));
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
			key_press(event.key.keysym.sym, wolf);
		else if (event.type == SDL_KEYUP && event.key.repeat == 0)
			key_release(event.key.keysym.sym, wolf);
		else if (event.type == SDL_DROPFILE)
			dropfile_event(wolf, event);
		else if (event.type == SDL_WINDOWEVENT)
			window_event(wolf, event);
		else
			lil_event_handler(wolf, event);
	}
	return (1);
}
