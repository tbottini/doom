/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:50 by magrab            #+#    #+#             */
/*   Updated: 2019/04/22 20:28:39 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			main(int ac, char **av)
{
	t_wolf *wolf;

	(void)ac;
	(void)av;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		ft_printf("SDL_Init: %s\n", SDL_GetError());
		return (-1);
	}
	if (TTF_Init() == -1)
	{
		ft_printf("TTF_Init: %s\n", TTF_GetError());
		return (-1);
	}
	if (IMG_Init(IMG_INIT_PNG) == -1)
	{
		ft_printf("IMG: %s\n", IMG_GetError());
		return (-1);
	}
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
