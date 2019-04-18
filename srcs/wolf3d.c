/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:50 by magrab            #+#    #+#             */
/*   Updated: 2019/04/18 17:29:15 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_wolf *wolf_init()
{
	t_wolf *wolf;

	if (!(wolf = (t_wolf *)malloc(sizeof(t_wolf))))
		return (NULL);
	if (sdl_start(wolf, "Wolf 3D"))
		return (NULL);

	add_start_button(wolf, 0);
	add_wolf_button(wolf, 1);
	add_opt_button(wolf, 2);
	add_quit_button(wolf, 3);
	//wolf->sdl.btnarr[9].txture = NULL;
	wolf->pos.x = 0;
	wolf->pos.y = 0;
	return (wolf);
}

void load_buttons(t_wolf *wolf)
{
	int x;
	t_btn tmp;

	x = 0;
	SDL_RenderClear(wolf->sdl.rend);
	while (wolf->sdl.btnarr[x].txture)
	{
		tmp = wolf->sdl.btnarr[x];
		wolf->sdl.btnarr[x].area.x = wolf->sdl.size.x * (tmp.pos.x / 100); //controls the rect's x coordinate
		wolf->sdl.btnarr[x].area.y = wolf->sdl.size.y * (tmp.pos.y / 100);
		if (tmp.snapx == 1)
			wolf->sdl.btnarr[x].area.x -= tmp.area.w / 2;
		else if (tmp.snapx == 2)
			wolf->sdl.btnarr[x].area.x -= tmp.area.w;
		if (tmp.snapy == 1)
			wolf->sdl.btnarr[x].area.y -= tmp.area.h / 2;
		else if (tmp.snapy == 2)
			wolf->sdl.btnarr[x].area.y -= tmp.area.h;
		SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.btnarr[x].txture, NULL, &(wolf->sdl.btnarr[x].area));
		x++;
	}
	SDL_RenderPresent(wolf->sdl.rend);
}

void	btn_click(t_wolf *wolf, int x, int y)
{
	int		i;
	t_btn tmp;

	i = 0;
	while (wolf->sdl.btnarr[i].txture)
	{
		tmp = wolf->sdl.btnarr[i];
		if (tmp.area.x <= x && x <= tmp.area.x + tmp.area.w
			&& tmp.area.y <= y && y <= tmp.area.y + tmp.area.h)
		{
			ft_printf("Click on btn %d\n", i);
		}
		i++;
	}
}

int main(int ac, char **av)
{
	t_wolf *wolf;
	SDL_Event event;

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
	if (!wolf_parseur(ac, av, wolf))
	{
		ft_putendl("error");
		return (0);
	}
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
				key_press(event.key.keysym.sym, wolf);
			}
			else if (event.type == SDL_KEYUP && event.key.repeat == 0)
			{
				key_release(event.key.keysym.sym, wolf);
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
				mouse_move(event.motion.x, event.motion.y, wolf);
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				mouse_press(event.button.button, event.button.x, event.button.y, wolf);
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				mouse_release(event.button.button, event.button.x, event.button.y, wolf);
			}
			else// if (event.type != 771 && event.type != 768)
			{
				ft_printf("Unknown Event %d\n", event.type);
				PrintEvent(&event);
			}
			load_buttons(wolf);
			//raycasting(wolf, atoi(av[2]));
		}
	}

	return (0);
}
