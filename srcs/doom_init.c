/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:01:30 by magrab            #+#    #+#             */
/*   Updated: 2019/05/05 13:24:25 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


static t_wall	load_texture(t_doom *doom, const char *file)
{
	SDL_RWops	*rwop;
	SDL_Surface	*surf;
	SDL_Surface	*tmp;
	t_wall		wall;

	rwop = SDL_RWFromFile(file, "rb");
	if (!(tmp = IMG_LoadXPM_RW(rwop)))
	{
		ft_printf("IMG_LoadXPM_RW: %s\n", IMG_GetError());
		prog_quit(doom);
	}
	if (!(surf = SDL_ConvertSurface(tmp, doom->sdl.format, 0)))
	{
		ft_printf("SDL_ConvertSurface: failed\n");
		prog_quit(doom);
	}
	SDL_FreeSurface(tmp);
	SDL_RWclose(rwop);
	wall.txture = surf->pixels;
	wall.surf = surf;
	wall.w = surf->w;
	wall.h = surf->h;
	return (wall);
}
