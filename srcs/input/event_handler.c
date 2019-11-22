/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:33:51 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 07:01:03 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Here are event which trigger on no window
** New event shouldn't be needed
*/

int				event_handler(t_doom *doom)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_DROPFILE)
			dropfile_event(doom, event);
		else if (event.type == SDL_KEYDOWN
		&& event.key.keysym.sym == SDLK_ESCAPE)
			doom_exit(doom);
		else if (event.window.windowID == DOOM_WINDOW)
			event_handler_doom(doom, event);
		else if (event.window.windowID == EDITOR_WINDOW)
			event_handler_editor(doom, event);
		else if (event.type == SDL_QUIT)
			doom_exit(doom);
	}
	return (1);
}
