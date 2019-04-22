/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_quit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:28:16 by magrab            #+#    #+#             */
/*   Updated: 2019/04/22 15:59:59 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		prog_quit(t_wolf *wolf)
{
	int x;

	x = -1;
	while (wolf->sdl.btnarr[++x].txture)
		SDL_DestroyTexture(wolf->sdl.btnarr[x].txture);
	x = -1;
	while (wolf->sdl.btnmap[++x].txture)
	{
		SDL_DestroyTexture(wolf->sdl.btnmap[x].txture);
		if (x > 1)
			free(wolf->sdl.btnmap[x].data);
	}
	x = -1;
	while (x++ < 4)
		if (wolf->wl_txture[x])
			SDL_FreeSurface(wolf->wl_txture[x]);
	if (wolf->sdl.txture)
		SDL_DestroyTexture(wolf->sdl.txture);
	if (wolf->sdl.font)
		TTF_CloseFont(wolf->sdl.font);
	if (wolf->sdl.font32)
		TTF_CloseFont(wolf->sdl.font32);
	if (wolf->sdl.font128)
		TTF_CloseFont(wolf->sdl.font128);
	if (wolf->sdl.rend)
		SDL_DestroyRenderer(wolf->sdl.rend);
	if (wolf->sdl.win)
		SDL_DestroyWindow(wolf->sdl.win);
	TTF_Quit();
	SDL_Quit();
	free(wolf);
	wolf = NULL;
	//while (1);
	exit(0);
	return (0);
}
