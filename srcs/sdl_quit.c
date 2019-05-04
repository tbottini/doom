/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_quit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:28:16 by magrab            #+#    #+#             */
/*   Updated: 2019/05/04 22:12:52 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void		free_textures(t_doom *doom)
{
	int x;

	x = -1;
	while (doom->ui.btnarr[++x].txture)
		SDL_DestroyTexture(doom->ui.btnarr[x].txture);
	x = -1;
	while (doom->ui.btnmap[++x].txture)
	{
		SDL_DestroyTexture(doom->ui.btnmap[x].txture);
		if (x > 1)
			free(doom->ui.btnmap[x].data);
	}
}

int				prog_quit(t_doom *doom)
{
	free_textures(doom);
	if (doom->sdl.txture)
		SDL_DestroyTexture(doom->sdl.txture);
	if (doom->ui.fonts.s64)
		TTF_CloseFont(doom->ui.fonts.s64);
	if (doom->ui.fonts.s32)
		TTF_CloseFont(doom->ui.fonts.s32);
	if (doom->ui.fonts.s128)
		TTF_CloseFont(doom->ui.fonts.s128);
	if (doom->edit.rend)
		SDL_DestroyRenderer(doom->edit.rend);
	if (doom->edit.win)
		SDL_DestroyWindow(doom->edit.win);
	if (doom->sdl.rend)
		SDL_DestroyRenderer(doom->sdl.rend);
	if (doom->sdl.win)
		SDL_DestroyWindow(doom->sdl.win);
	if (doom->sdl.format)
		SDL_FreeFormat(doom->sdl.format);
	//doom_clear_map(doom);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	free(doom);
	exit(0);
	return (0);
}
