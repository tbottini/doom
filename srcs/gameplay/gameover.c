/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:30:40 by akrache           #+#    #+#             */
/*   Updated: 2019/07/24 11:04:59 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** returns the color c as if it passes throught a transparent screen of color s.
** double f determines the opacity of the "screen".
** f must be between 0 and 1, 1 returning the color s, 0 the color c.
*/

int					opacity(int s, int c, double f)
{
	if (f == 1)
		return (s);
	else if (!f)
		return (c);
	return (((int)((c >> 8 & 255) + f * ((s >> 8 & 255) - (c >> 8 & 255))) << 8)
	+ ((int)((c >> 16 & 255) + f * ((s >> 16 & 255) - (c >> 16 & 255))) << 16)
	+ ((int)((c >> 24 & 255) + f * ((s >> 24 & 255) - (c >> 24 & 255))) << 24)
	+ 255);
}

void		full_screen_opacity(t_doom *doom, Uint32 color, double blood)
{
	int i;
	int j;

	i = -1;
	while (++i < doom->sdl.size.x)
	{
		j = -1;
		while (++j < doom->sdl.size.y)
		{
			doom->sdl.screen[i + j * doom->sdl.size.x] =
				opacity(color, doom->sdl.screen[i + j * doom->sdl.size.x], blood);
		}
	}
}

int			display_end(t_doom *doom, Uint32 color, double filter, SDL_Texture *gameover)
{
	int		wait;
	int		ex;

	full_screen_opacity(doom, color, filter);
	//SDL_RenderCopy(doom->sdl.rend, gameover, NULL, NULL); //afficher Texture Game over 
	sdl_MultiRenderCopy(&doom->sdl);
	SDL_RenderPresent(doom->sdl.rend);
	cine_events(doom, &ex);
	if (ex == 3000)
		return (-1);
	wait = SDL_GetTicks() - doom->timestamp - 39; // Nombre de ms entre chaque frames
	if (wait < 0)
		SDL_Delay(-wait);
	doom->timestamp = SDL_GetTicks();
	return (0);
}

void		game_over(t_doom *doom, bool win)
{
	//Uint32			*last;
	SDL_Texture		*gameover;
	double			filter;

	gameover = NULL;//gameover = IMG_LoadTexture(doom->sdl.rend, "ressources/props/gameover.png");
	sector_render(&doom->game.arch, &doom->game.player, doom->game.player.stat.sector);
	//last = doom->sdl.screen;
	filter = 0.0;
	while (filter < 0.95)
	{
		//doom->sdl.screen = last;
		if (win && display_end(doom, 0x62E9AAFF, filter, gameover))//Green | YOU WIN !
			break ;
		else if (!win && display_end(doom, 0x9b0a1eff, filter, gameover))
			break ;
		filter += (filter < 0.07 ? 0.0005 : 0.02);
	}
	//SDL_DestroyTexture(gameover);
	free_game(&doom->game);
	sdl_set_status(doom, 1);
}