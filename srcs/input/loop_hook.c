/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 20:45:19 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 07:50:01 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Add here function that need to be done every frame when a key is pressed
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

static void	benda(t_doom *doom, int key)
{
	static int prev = 32700.0;

	if (key == SDLK_s)
		doom->game.player.stat.vel.x = -doom->game.player.stat.speed;
	else if (key == SDLK_w)
		doom->game.player.stat.vel.x = doom->game.player.stat.speed;
	else if (key == SDLK_a)
		doom->game.player.stat.vel.y = -doom->game.player.stat.speed;
	else if (key == SDLK_d)
		doom->game.player.stat.vel.y = doom->game.player.stat.speed;
	if (!Mix_Playing(1) || prev != doom->game.player.stat.speed)
	{
		if (doom->game.player.stat.speed == 32700.0)
			Mix_PlayChannel(1, doom->game.sound.tab_effect[0], -1);
		else if (doom->game.player.stat.speed == 49050.0)
			Mix_PlayChannel(1, doom->game.sound.tab_effect[1], -1);
		else if (doom->game.player.stat.speed == 16350.0)
			Mix_PlayChannel(1, doom->game.sound.tab_effect[2], -1);
	}
	prev = doom->game.player.stat.speed;
}

static void	input_loop(t_doom *doom, int key)
{
	if ((key == SDLK_w || key == SDLK_s || key == SDLK_a || key == SDLK_d))
		benda(doom, key);
	else if (key == SDLK_LSHIFT
	&& doom->game.player.stat.vel.x == doom->game.player.stat.speed)
		sprint(&doom->game.player.stat);
	else if (key == SDLK_SPACE)
		jump(&doom->game.player.stat, &doom->game.player.inv);
	else if (key == SDLK_LGUI && !doom->game.player.inv.jetpack)
		fly_down(&doom->game.player.stat);
	else if (doom->timestamp > doom->game.player.occupied)
	{
		if (key == SDL_BUTTON_LEFT)
			shoot(doom->timestamp, &doom->game.sound,
			&doom->game.player, doom->game.len.nb_sects);
	}
}

static void	delaypcmasterrace(t_doom *doom)
{
	int wait;

	wait = SDL_GetTicks() - doom->timestamp - 16;
	if (wait < 0)
		SDL_Delay(-wait);
	doom->timestamp = SDL_GetTicks();
	doom->game.arch.timestamp = doom->timestamp;
}

static void	game_loop_hook(t_doom *doom)
{
	t_tab pos;

	if (doom->ui.m_status == MENU_INGAME)
	{
		pos = doom->sdl.keys;
		while (pos)
		{
			input_loop(doom, pos->data);
			pos = pos->next;
		}
		effect_volume(&doom->game.sound);
		move(&doom->game.player.stat, &doom->game.player.inv);
		pickup_prop(doom);
		armandtificial_intelligence(doom);
		if (doom->game.player.stat.health <= 0)
			game_over(doom, false);
		else
		{
			doom_render(doom);
			hud_render(doom);
		}
	}
	else
		outgame_loop_hook(doom);
	SDL_RenderPresent(doom->sdl.rend);
}

int			loop_hook(t_doom *doom)
{
	SDL_RenderClear(doom->sdl.rend);
	if (doom->edit.status)
		editor_loop_hook(doom);
	else
		game_loop_hook(doom);
	delaypcmasterrace(doom);
	return (0);
}
