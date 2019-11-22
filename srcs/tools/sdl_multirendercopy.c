/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_multirendercopy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 11:05:20 by magrab            #+#    #+#             */
/*   Updated: 2019/08/16 11:05:21 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int	upper_left(void *ptr)
{
	SDL_Rect	part;
	t_sdl		*sdl;

	sdl = ptr;
	part.x = 0;
	part.y = 0;
	part.w = sdl->size.x / 2;
	part.h = sdl->size.y / 2;
	SDL_RenderCopy(sdl->rend, sdl->txture, &part, &part);
	return (0);
}

static int	upper_right(void *ptr)
{
	SDL_Rect	part;
	t_sdl		*sdl;

	sdl = ptr;
	part.x = sdl->size.x / 2;
	part.y = 0;
	part.w = part.x;
	part.h = sdl->size.y / 2;
	SDL_RenderCopy(sdl->rend, sdl->txture, &part, &part);
	return (0);
}

static int	bottom_left(void *ptr)
{
	SDL_Rect	part;
	t_sdl		*sdl;

	sdl = ptr;
	part.x = 0;
	part.y = sdl->size.y / 2;
	part.w = sdl->size.x / 2;
	part.h = part.y;
	SDL_RenderCopy(sdl->rend, sdl->txture, &part, &part);
	return (0);
}

static int	bottom_right(void *ptr)
{
	SDL_Rect	part;
	t_sdl		*sdl;

	sdl = ptr;
	part.x = sdl->size.x / 2;
	part.y = sdl->size.y / 2;
	part.w = part.x;
	part.h = part.y;
	SDL_RenderCopy(sdl->rend, sdl->txture, &part, &part);
	return (0);
}

void		sdl_multirendercopy(t_sdl *sdl)
{
	SDL_Thread *rend_ths[4];

	rend_ths[0] = SDL_CreateThread(&upper_left, "Upper Left screen", sdl);
	rend_ths[1] = SDL_CreateThread(&upper_right, "Upper Right screen", sdl);
	rend_ths[2] = SDL_CreateThread(&bottom_left, "Bottom Left screen", sdl);
	rend_ths[3] = SDL_CreateThread(&bottom_right, "Bottom Right screen", sdl);
	SDL_WaitThread(rend_ths[0], NULL);
	SDL_WaitThread(rend_ths[1], NULL);
	SDL_WaitThread(rend_ths[2], NULL);
	SDL_WaitThread(rend_ths[3], NULL);
}
