/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cinematri.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 01:54:40 by akrache           #+#    #+#             */
/*   Updated: 2019/08/10 17:28:32 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		cine_events(t_doom *doom, int *i)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT
				|| (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			doom_exit(doom);
		else if ((e.type == SDL_KEYDOWN
		&& (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_RETURN)))
			*i = 3000;
		else if (e.type == SDL_DROPFILE)
			dropfile_event(doom, e);
		else if (e.window.windowID == 1)
		{
			if (e.type == SDL_WINDOWEVENT)
				event_handler_doom(doom, e);
		}
		else if (e.window.windowID == 2)
		{
			if (e.type == SDL_WINDOWEVENT)
				event_handler_editor(doom, e);
		}
	}
}

static void	cine_delay(t_doom *doom, int *i)
{
	int wait;

	cine_events(doom, i);
	wait = SDL_GetTicks() - doom->timestamp - 39;
	if (wait < 0)
		SDL_Delay(-wait);
	doom->timestamp = SDL_GetTicks();
}

void		concat_atoi(char *str, int i)
{
	str[0] = i / 1000 + '0';
	i %= 1000;
	str[1] = i / 100 + '0';
	i %= 100;
	str[2] = i / 10 + '0';
	i %= 10;
	str[3] = i + '0';
}

static void	super_cinematrique(t_doom *doom, SDL_Surface *image,
	SDL_Texture *texture, int i)
{
	char		deb[36];
	int			max;

	max = i == 200 ? 3000 : 138;
	ft_strcpy(deb, "ressources/cinematic/frame_0000.png");
	while (i <= max && (image = IMG_Load(deb)))
	{
		concat_atoi(&deb[27], i);
		if (!(texture = SDL_CreateTextureFromSurface(doom->sdl.rend, image)))
			return ;
		SDL_RenderCopy(doom->sdl.rend, texture, NULL, NULL);
		SDL_RenderPresent(doom->sdl.rend);
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(image);
		cine_delay(doom, &i);
		i += 2;
	}
	if (!image || i == 3002)
		return ;
	else
		super_cinematrique(doom, image, texture, 200);
}

void		cinematrique(t_doom *doom)
{
	char		deb[48];
	int			i;
	SDL_Surface	*image;
	SDL_Texture	*texture;

	i = 0;
	ft_strcpy(deb, "ressources/cinematic/frame_0000.png");
	if (!(image = IMG_Load("ressources/cinematic/frame_0000.png")))
		return ;
	if (!(texture = SDL_CreateTextureFromSurface(doom->sdl.rend, image)))
		return ;
	SDL_RenderCopy(doom->sdl.rend, texture, NULL, NULL);
	SDL_RenderPresent(doom->sdl.rend);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	while (i < 120)
	{
		cine_delay(doom, &i);
		i += 2;
	}
	if (i == 3002)
		return ;
	else
		super_cinematrique(doom, image, texture, i);
}
