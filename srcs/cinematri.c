/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cinematri.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 01:54:40 by akrache           #+#    #+#             */
/*   Updated: 2019/06/05 22:34:28 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void cine_events(t_doom *doom, int *i)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			doom_exit(doom);
		else if ((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE))
			*i = 3000;
		else if (e.type == SDL_WINDOWEVENT)
			event_handler1(doom, e);
		else if (e.type == SDL_CONTROLLERDEVICEADDED)
		{
			ft_printf("Controller Added\n");
			doom->controller = SDL_GameControllerOpen(0);
		}
		else if (e.type == SDL_CONTROLLERDEVICEREMOVED)
		{
			ft_printf("Controller Removed\n");
		}
		else if (e.type == SDL_CONTROLLERAXISMOTION
			|| e.type == SDL_CONTROLLERBUTTONDOWN
				|| e.type == SDL_CONTROLLERBUTTONUP)
			controller_handler(doom, e);
	}
}

static void	cine_delay(t_doom *doom, int *i)
{
	cine_events(doom, i);
	if (doom->sdl.timp == SDL_GetTicks() / 1000)
		++doom->sdl.fps;
	else
	{
		ft_printf("\r%d FPS\n", doom->sdl.fps);
		doom->sdl.fps = 0;
		doom->sdl.timp = SDL_GetTicks() / 1000;
	}
	while (SDL_GetTicks() - doom->timestamp < 39)
		; 
	doom->timestamp = SDL_GetTicks();
}

static void	concat_atoi(char *deb, int i)
{
	deb[39] = i / 1000 + '0';
	i %= 1000;
	deb[40] = i / 100 + '0';
	i %= 100;
	deb[41] = i / 10 + '0';
	i %= 10;
	deb[42] = i + '0';
}

static void	super_cinematrique(t_doom *doom, SDL_Surface *image, SDL_Texture *texture, int i)
{
	char		deb[48];
	int			max;

	max = i == 200 ? 3000 : 138;
	ft_strcpy(deb, "/Users/akrache/Desktop/cinematic/frame_0000.png");//change path
	while (i <= max && (image = IMG_Load(deb)))
	{
		concat_atoi(deb, i);
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

void	cinematrique(t_doom *doom)
{
	char		deb[48];
	int			i;
	SDL_Surface	*image;
	SDL_Texture	*texture;

	i = 0;
	ft_strcpy(deb, "/Users/akrache/Desktop/cinematic/frame_0000.png");//change path
	if (!(image = IMG_Load("/Users/akrache/Desktop/cinematic/frame_0000.png")))//change path
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
