/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:50 by magrab            #+#    #+#             */
/*   Updated: 2019/07/10 14:18:15 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int	init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_GAMECONTROLLER|SDL_INIT_TIMER) != 0)
	{
		ft_printf("SDL_Init: %s\n", SDL_GetError());
		return (0);
	}
	if (TTF_Init() == -1)
	{
		ft_printf("TTF_Init: %s\n", TTF_GetError());
		return (0);
	}
	if (IMG_Init(IMG_INIT_PNG) == -1)
	{
		ft_printf("IMG: %s\n", IMG_GetError());
		return (0);
	}
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0)
	{
		ft_printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		return (0);
	}
	return (1);
}

int			main(int ac, char **av)
{
	t_doom		*doom;

	if (!init())
		return (0);
	if (!(doom = doom_init()))
		return (0);
	if (ac == 2)
	{
		if (parsing(doom, av[1]))
			sdl_set_status(doom, 0);
		else
			sdl_set_status(doom, 1);
	}
	else
		sdl_set_status(doom, 1);
	event_handler(doom);
	Mix_FadeInMusic(doom->game.sound.tab_music[0], -1, 18000);
	cinematrique(doom);
	while ('^' == '^')
	{
		if (!(event_handler(doom)))
			return (0);
		loop_hook(doom);
	}
	return (0);
}
