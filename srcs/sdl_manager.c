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

#include "wolf3d.h"

int		sdl_start(t_wolf *wolf, const char *title)
{
	void	*tmp;
	int		pitch;

	wolf->sdl.size.x = WIDTH;
	wolf->sdl.size.y = HEIGHT;
	wolf->ui.m_status = 1;
	if (!(wolf->sdl.win = SDL_CreateWindow(title, 0, 0, WIDTH, HEIGHT, 32)))
		return (prog_quit(wolf));
	if (!(wolf->sdl.rend = SDL_CreateRenderer(wolf->sdl.win, -1, 1)))
		return (prog_quit(wolf));
	if (!(wolf->ui.fonts.s64 = TTF_OpenFont(TTFWOLF, 64)))
		return (prog_quit(wolf));
	if (!(wolf->ui.fonts.s128 = TTF_OpenFont(TTFWOLF, 128)))
		return (prog_quit(wolf));
	if (!(wolf->ui.fonts.s32 = TTF_OpenFont(TTFIMPACT, 32)))
		return (prog_quit(wolf));
	SDL_SetWindowMinimumSize(wolf->sdl.win, 640, 480);
	wolf->sdl.txture = SDL_CreateTexture(wolf->sdl.rend,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	if (SDL_LockTexture(wolf->sdl.txture, NULL, &tmp, &pitch))
		return (prog_quit(wolf));
	wolf->sdl.screen = (uint32_t*)tmp;
	if (!(wolf->sdl.format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888)))
		return (prog_quit(wolf));
	return (0);
}
