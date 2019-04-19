/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:33:51 by magrab            #+#    #+#             */
/*   Updated: 2019/04/19 18:13:15 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int event_handler(t_wolf *wolf)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			return (prog_quit(wolf));
		if (event.type == SDL_KEYDOWN /*&& event.key.repeat == 0*/)
		{
			if (event.key.keysym.sym == SDLK_e)
				wolf->rot -= 5;
			else if (event.key.keysym.sym == SDLK_q)
				wolf->rot += 5;
			else if (event.key.keysym.sym == SDLK_w)
				wolf->pos.x += 0.3;
			else if (event.key.keysym.sym == SDLK_s)
				wolf->pos.x -= 0.3;
			else if (event.key.keysym.sym == SDLK_d)
				wolf->pos.y += 0.3;
			else if (event.key.keysym.sym == SDLK_a)
				wolf->pos.y -= 0.3;
			raycasting(wolf);
			key_press(event.key.keysym.sym, wolf);
		}
		else if (event.type == SDL_KEYUP && event.key.repeat == 0)
			key_release(event.key.keysym.sym, wolf);
		else if (event.type == SDL_DROPBEGIN)
			printf("Event DropBegin\n");
		else if (event.type == SDL_DROPFILE)
		{
			printf("Event DropFile %s\n", event.drop.file);
			SDL_free(event.drop.file);
		}
		else if (event.type == SDL_DROPCOMPLETE)
			printf("Event DropComplete\n");
		else if (event.type == SDL_WINDOWEVENT)
		{
			//PrintEvent(&event);
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				SDL_GetWindowSize(wolf->sdl.win, &(wolf->sdl.size.x), &(wolf->sdl.size.y));
		}
		else if (event.type == SDL_MOUSEMOTION)
			mouse_move(event.motion.x, event.motion.y, wolf);
		else if (event.type == SDL_MOUSEBUTTONDOWN)
			mouse_press(event.button.button, event.button.x, event.button.y, wolf);
		else if (event.type == SDL_MOUSEBUTTONUP)
			mouse_release(event.button.button, event.button.x, event.button.y, wolf);
		else // if (event.type != 771 && event.type != 768)
		{
			ft_printf("Unknown Event %d\n", event.type);
			PrintEvent(&event);
		}
		//load_buttons(wolf);
		//raycasting(wolf);
	}
	return (1);
}
