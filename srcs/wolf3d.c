/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:50 by magrab            #+#    #+#             */
/*   Updated: 2019/04/16 00:18:53 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_wolf *wolf_init()
{
	t_wolf *wolf;

	if (!(wolf = malloc(sizeof(t_wolf))))
		return (NULL);
	if (sdl_start(wolf, "Wolf 3D"))
		return (NULL);

	add_start_button(wolf);
	add_wolf_button(wolf);
	wolf->pos.x = 0;
	wolf->pos.y = 0;
	return (wolf);
}

void load_buttons(t_wolf *wolf)
{
	SDL_RenderClear(wolf->sdl.rend);
	wolf->sdl.btnarr[0].area.x = wolf->sdl.size.x / 2 - 100; //controls the rect's x coordinate
	wolf->sdl.btnarr[0].area.y = wolf->sdl.size.y / 2 - 75;
	wolf->sdl.btnarr[1].area.x = wolf->sdl.size.x / 2 - 200; //controls the rect's x coordinate
	wolf->sdl.btnarr[1].area.y = wolf->sdl.size.y / 5 - 100;
	SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.btnarr[0].txture, NULL, &(wolf->sdl.btnarr[0].area));
	SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.btnarr[1].txture, NULL, &(wolf->sdl.btnarr[1].area));
	SDL_RenderPresent(wolf->sdl.rend);
}

int main(int ac, char **av)
{
	t_wolf *wolf;
	SDL_Event event;
	(void)ac;
	(void)av;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		ft_printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return (-1);
	}
	if (TTF_Init() == -1)
	{
		ft_printf("TTF_Init: %s\n", TTF_GetError());
		return (-1);
	}
	if (!(wolf = wolf_init()))
		return (-1);

	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			{
				TTF_Quit();
				SDL_DestroyRenderer(wolf->sdl.rend);
				SDL_DestroyWindow(wolf->sdl.win);
				SDL_Quit();
				return (0);
			}
			if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
			{
				printf("Key %d : %s detected\n", event.key.keysym.scancode, SDL_GetKeyName(event.key.keysym.sym));
			}
			else if (event.type == SDL_KEYUP && event.key.repeat == 0)
			{
				printf("Key release detected\n");
			}
			else if (event.type == SDL_DROPBEGIN)
			{
				printf("Event DropBegin\n");
			}
			else if (event.type == SDL_DROPFILE)
			{
				printf("Event DropFile %s\n", event.drop.file);
				SDL_free(event.drop.file);
			}
			else if (event.type == SDL_DROPCOMPLETE)
			{
				printf("Event DropComplete\n");
			}
			else if (event.type == SDL_WINDOWEVENT)
			{
				PrintEvent(&event);
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					SDL_GetWindowSize(wolf->sdl.win, &(wolf->sdl.size.x), &(wolf->sdl.size.y));
				}
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
			}
			else
			{

				printf("Event %d\n", event.type);
			}
			load_buttons(wolf);
		}
	}

	return (0);
}
