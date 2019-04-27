/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_quit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:28:16 by magrab            #+#    #+#             */
/*   Updated: 2019/04/26 22:28:53 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		free_textures(t_wolf *wolf)
{
	int x;

	x = -1;
	while (wolf->ui.btnarr[++x].txture)
		SDL_DestroyTexture(wolf->ui.btnarr[x].txture);
	x = -1;
	while (wolf->ui.btnmap[++x].txture)
	{
		SDL_DestroyTexture(wolf->ui.btnmap[x].txture);
		if (x > 1)
			free(wolf->ui.btnmap[x].data);
	}
	x = -1;
	while (++x < 4)
		if (wolf->wall[x].surf)
			SDL_FreeSurface(wolf->wall[x].surf);
}

int				prog_quit(t_wolf *wolf)
{
	free_textures(wolf);
	if (wolf->sdl.txture)
		SDL_DestroyTexture(wolf->sdl.txture);
	if (wolf->ui.fonts.s64)
		TTF_CloseFont(wolf->ui.fonts.s64);
	if (wolf->ui.fonts.s32)
		TTF_CloseFont(wolf->ui.fonts.s32);
	if (wolf->ui.fonts.s128)
		TTF_CloseFont(wolf->ui.fonts.s128);
	if (wolf->sdl.rend)
		SDL_DestroyRenderer(wolf->sdl.rend);
	if (wolf->sdl.win)
		SDL_DestroyWindow(wolf->sdl.win);
	if (wolf->sdl.format)
		SDL_FreeFormat(wolf->sdl.format);
	wolf_clear_map(wolf);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	free(wolf);
	exit(0);
	return (0);
}
