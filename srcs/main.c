/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:50 by magrab            #+#    #+#             */
/*   Updated: 2019/04/25 21:09:25 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
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

int			main(void)
{
	t_wolf *wolf;

	if (!init())
		return (0);
	if (!(wolf = wolf_init()))
		return (-1);
	while (0 == 0)
	{
		if (!(event_handler(wolf)))
			return (0);
		loop_hook(wolf);
	}
	return (0);
}
