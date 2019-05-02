/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 21:00:34 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/25 21:00:36 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		sdl_start(t_doom *doom, const char *title)
{
	void	*tmp;
	int		pitch;

	doom->sdl.size.x = WIDTH;
	doom->sdl.size.y = HEIGHT;
	doom->ui.m_status = 1;
	if (!(doom->sdl.win = SDL_CreateWindow(title, 0, 0, WIDTH, HEIGHT, 32)))
		return (prog_quit(doom));
	if (!(doom->edit.win = SDL_CreateWindow("Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_HIDDEN)))
		return (prog_quit(doom));
	if (!(doom->sdl.rend = SDL_CreateRenderer(doom->sdl.win, -1, 1)))
		return (prog_quit(doom));
	if (!(doom->edit.rend = SDL_CreateRenderer(doom->edit.win, -1, 1)))
		return (prog_quit(doom));
	if (!(doom->ui.fonts.s64 = TTF_OpenFont(TTFWOLF, 64)))
		return (prog_quit(doom));
	if (!(doom->ui.fonts.s128 = TTF_OpenFont(TTFWOLF, 128)))
		return (prog_quit(doom));
	if (!(doom->ui.fonts.s32 = TTF_OpenFont(TTFIMPACT, 32)))
		return (prog_quit(doom));
	SDL_SetWindowMinimumSize(doom->sdl.win, MINWIDTH, MINHEIGHT);
	doom->sdl.txture = SDL_CreateTexture(doom->sdl.rend,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	if (SDL_LockTexture(doom->sdl.txture, NULL, &tmp, &pitch))
		return (prog_quit(doom));
	doom->sdl.screen = (uint32_t*)tmp;
	if (!(doom->sdl.format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888)))
		return (prog_quit(doom));
	return (0);
}
