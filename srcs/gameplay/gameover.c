/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:30:40 by akrache           #+#    #+#             */
/*   Updated: 2019/08/26 16:18:45 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "render.h"

/*
** returns the color c as if it passes throught a transparent screen of color s.
** double f determines the opacity of the "screen".
** f must be between 0 and 1, 1 returning the color s, 0 the color c.
*/

extern inline int	opacity(int s, int c, double f)
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

/*
**	s : additive
**	c : basique
*/

extern inline int	opacity_from_color(Uint32 add, Uint32 basique)
{
	const double	factor = (add & 255) / 255.0;

	if (factor == 1)
		return (add);
	else if (!factor)
		return (basique);
	return (((int)((basique >> 8 & 255)
			+ factor * ((add >> 8 & 255) - (basique >> 8 & 255))) << 8)
		+ ((int)((basique >> 16 & 255)
			+ factor * ((add >> 16 & 255) - (basique >> 16 & 255))) << 16)
		+ ((int)((basique >> 24 & 255)
			+ factor * ((add >> 24 & 255) - (basique >> 24 & 255))) << 24)
	+ 255);
}

static void			full_screen_opacity(t_doom *doom, Uint32 color, double bl)
{
	int				i;
	int				j;

	i = -1;
	while (++i < doom->sdl.size.x)
	{
		j = -1;
		while (++j < doom->sdl.size.y)
		{
			doom->sdl.screen[i + j * doom->sdl.size.x] =
				opacity(color, doom->sdl.screen[i + j * doom->sdl.size.x], bl);
		}
	}
}

static int			display_end(t_doom *doom, Uint32 color, double filter
	, bool win)
{
	int				wait;
	int				ex;

	full_screen_opacity(doom, color, filter);
	sdl_multirendercopy(&doom->sdl);
	if (win)
		sdl_string_put((t_sp){doom->sdl.rend, doom->ui.fonts.s128,
		(t_vct2){doom->sdl.size.x / 2 - 158,
		doom->sdl.size.y / 2 - 100}, "YOU WIN !",
		(SDL_Color){0, 0, 0, 255}});
	else
		sdl_string_put((t_sp){doom->sdl.rend, doom->ui.fonts.s128,
		(t_vct2){doom->sdl.size.x / 2 - 174,
		doom->sdl.size.y / 2 - 100}, "GAME OVER",
		(SDL_Color){250, 250, 250, 255}});
	SDL_RenderPresent(doom->sdl.rend);
	cine_events(doom, &ex);
	if (ex == 3000)
		return (-1);
	wait = SDL_GetTicks() - doom->timestamp - 39;
	if (wait < 0)
		SDL_Delay(-wait);
	doom->timestamp = SDL_GetTicks();
	return (0);
}

void				game_over(t_doom *doom, bool win)
{
	SDL_Texture		*gameover;
	double			filter;

	gameover = NULL;
	Mix_HaltChannel(-1);
	sector_render(&doom->game.arch, &doom->game.player,
	doom->game.player.stat.sector);
	if (win)
		Mix_PlayChannel(0, doom->game.sound.tab_effect[11], 0);
	else
		Mix_PlayChannel(0, doom->game.sound.tab_effect[12], 0);
	filter = 0.0;
	while (filter < 0.95)
	{
		if (win && display_end(doom, 0x42B453ff, filter, win))
			break ;
		else if (!win && display_end(doom, 0x9b0a1eff, filter, win))
			break ;
		filter += (filter < 0.07 ? 0.0005 : 0.02);
	}
	Mix_FadeOutChannel(0, 1000);
	free_game(&doom->game);
	if (!win)
		Mix_PlayChannel(0, doom->game.sound.tab_effect[13], 0);
	sdl_set_status(doom, MENU_MAIN);
}
