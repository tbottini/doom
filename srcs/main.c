/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:50 by magrab            #+#    #+#             */
/*   Updated: 2019/05/05 16:31:10 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int	init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_GAMECONTROLLER) != 0)
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
	return (1);
}

int			main(int ac, char **av)
{
	t_doom		*doom;
	SDL_Event	event;

	if (ac < 2)
		return (-1);
	if (!init())
		return (0);
	if (!(doom = doom_init()))
		return (-1);
	if (!(parsing(doom, av[1])))
	{
		printf("bad parsing\n");
		return (0);
	}
	debug_player(doom->player);
	portal_engine(doom);
	while (1)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN)
			keyboard_input(doom, event);
	}
	return (0);
}
