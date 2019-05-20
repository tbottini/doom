/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 20:45:19 by magrab            #+#    #+#             */
/*   Updated: 2019/05/20 17:33:13 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Add here function that need to be done every frame when a key is pressed
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

static void input_loop(t_doom *doom, int key)
{
	if (key == SDLK_w || key == SDLK_s)
		doom->player.vel.x = (key == SDLK_w ? 32700 : -32700);
	else if (key == SDLK_a || key == SDLK_d)
		doom->player.vel.y = (key == SDLK_a ? -32700 : 32700);
	else if (key == SDLK_LSHIFT)
		sprint(&doom->player);
	else if (key == SDLK_r)
		reload(&(doom->player.weapons[doom->player.hand]));
	else if (key == SDL_BUTTON_LEFT)
		shoot(&doom->player);
	else if (key == SDLK_y)
		fire(doom);
}

static void	delaypcmasterrace(t_doom *doom)
{
	if (doom->sdl.timp == SDL_GetTicks() / 1000)
		++doom->sdl.fps;
	else
	{
		//ft_printf("\r%d FPS ", doom->sdl.fps);
		doom->sdl.fps = 0;
		doom->sdl.timp = SDL_GetTicks() / 1000;
	}
	while (SDL_GetTicks() - doom->timestamp < 16); // Limiteur de FPS (16)
	doom->timestamp = SDL_GetTicks();
}

int loop_hook(t_doom *doom)
{
	t_tab pos;

	pos = doom->sdl.keys;
	while (pos)
	{
		input_loop(doom, pos->data);
		pos = pos->next;
	}
	SDL_RenderClear(doom->sdl.rend);
	if (doom->edit.status == 1)
	{
		SDL_RenderClear(doom->edit.rend);
		sdl_cleartexture(doom->edit.screen, doom->edit.size);
		draw_map(&doom->edit);
		SDL_RenderCopy(doom->edit.rend, doom->edit.txture, NULL, NULL);
		SDL_RenderPresent(doom->edit.rend);
	}
	else
	{
		if (doom->ui.m_status == 0)
		{
/// Place here functions that need to be launch every frame while the game is running
		move(&doom->player, doom->player.vel.x, doom->player.vel.y);
		portal_engine(doom);
		minimap(doom);
/// End Comment
		}
		else
		{
/// Place here functions that need to be launch every frame while in the menu

			fire(doom);
			draw_menu(doom);

/// End Comment
		}
		SDL_RenderPresent(doom->sdl.rend);
	}
	delaypcmasterrace(doom);
	return (0);
}
