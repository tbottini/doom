/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:50 by magrab            #+#    #+#             */
/*   Updated: 2019/05/05 09:26:02 by tbottini         ###   ########.fr       */
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
	t_sector	*sector;
	t_player	player;
	t_doom		*doom;
	player.fov = 90;
	player.rot.y = atof(av[2]);
	player.rot.x = 1.0;
	player.pos.x = 1.0;
	player.pos.y = 1.0;
	player.d_scrn = (1920 / 2.0) / tan(player.fov * PI180 / 2.0);
	if (ac < 2)
	{
		printf("pas assez d'arg\n");
		return (0);
	}
	if (!init())
	{
		printf("test\n");
		return (0);
	}
	if (!(doom = doom_init()))
		return (-1);
	if (!(sector = parsing(av[1])))
	{
		printf("bad parsing\n");
		return (0);
	}
	while (1)
	{
		if (!(event_handler(doom)))
			return (0);
		loop_hook(doom);
	}
	portal_engine(player, sector);

	SDL_RenderCopy(doom->sdl.rend, doom->sdl.txture, NULL, NULL);
	SDL_RenderPresent(doom->sdl.rend);

	SDL_Delay(2000);
	return (0);
}
