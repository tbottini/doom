/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_quit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:28:16 by magrab            #+#    #+#             */
/*   Updated: 2019/04/18 19:28:17 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		prog_quit(t_wolf *wolf)
{
	int x;

	TTF_CloseFont(wolf->sdl.font);
	TTF_Quit();
	SDL_DestroyRenderer(wolf->sdl.rend);
	SDL_DestroyWindow(wolf->sdl.win);
	SDL_Quit();
	x = -1;
	while (wolf->sdl.btnarr[++x].txture)
		SDL_DestroyTexture(wolf->sdl.btnarr[x].txture);
	SDL_UnlockTexture(wolf->sdl.txture);
	SDL_DestroyTexture(wolf->sdl.txture);
	free(wolf);
	wolf = NULL;
	while (1)
		;
	exit(0);
	return (0);
}
