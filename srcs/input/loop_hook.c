/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 20:45:19 by magrab            #+#    #+#             */
/*   Updated: 2019/06/19 14:44:43 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Add here function that need to be done every frame when a key is pressed
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

void		benda(t_doom *doom, int key)
{
	static int prev = 32700.0;

	if (key == SDLK_s)
		doom->player.stat.vel.x = -doom->player.stat.speed;
	else if (key == SDLK_w)
		doom->player.stat.vel.x = doom->player.stat.speed;
	else if (key == SDLK_a)
		doom->player.stat.vel.y = -doom->player.stat.speed;
	else if (key == SDLK_d)
		doom->player.stat.vel.y = doom->player.stat.speed;
	if (!Mix_Playing(1) || prev != doom->player.stat.speed)
	{
		if (doom->player.stat.speed == 32700.0)
			Mix_PlayChannel(1, doom->sound.tab_effect[0], -1);
		else if (doom->player.stat.speed == 49050.0)
			Mix_PlayChannel(1, doom->sound.tab_effect[1], -1);
		else if (doom->player.stat.speed == 16350.0)
			Mix_PlayChannel(1, doom->sound.tab_effect[2], -1);
	}
	prev = doom->player.stat.speed;
}

static void input_loop(t_doom *doom, int key)
{
	//if (key == SDLK_w || key == SDLK_s)
	//	doom->player.stat.vel.x = (key == SDLK_w ? 32700 : -32700);
	//else if (key == SDLK_a || key == SDLK_d)
	//	doom->player.stat.vel.y = (key == SDLK_a ? -32700 : 32700);
	/*if (key == SDLK_w || key == SDLK_s)
		doom->player.stat.vel.x = (key == SDLK_w ? doom->player.stat.speed : -doom->player.stat.speed);
	else if (key == SDLK_a || key == SDLK_d)
		doom->player.stat.vel.y = (key == SDLK_a ? -doom->player.stat.speed : doom->player.stat.speed);*/
	if ((key == SDLK_w || key == SDLK_s || key == SDLK_a || key == SDLK_d) && !doom->ui.m_status)
		benda(doom, key);
	else if (key == SDLK_LSHIFT && doom->player.stat.vel.x == doom->player.stat.speed && !doom->ui.m_status)
		sprint(&doom->player.stat);
	else if (key == SDLK_SPACE && !doom->ui.m_status)
		jump(&doom->player);
	else if (key == SDLK_r && doom->player.hand && !doom->ui.m_status)
		reload(&(doom->player.weapons[doom->player.hand]));
	else if (key == SDL_BUTTON_LEFT && !doom->ui.m_status)
		shoot(&doom->player);
	else if (key == SDLK_p) //test tir
		bullet(doom, &doom->player.stat);
	else if (key == SDLK_0)//test effects
		play_effect(&doom->sound, 8);
	else if (key == SDLK_y)
		fire(doom);
}

static void editor_loop(t_doom *doom, int key)
{
	if (key == SDLK_w || key == SDLK_s)
		doom->player.stat.vel.x = (key == SDLK_w ? 32700 : -32700);
	else if (key == SDLK_a || key == SDLK_d)
		doom->player.stat.vel.y = (key == SDLK_a ? -32700 : 32700);
	else if (key == SDLK_LSHIFT)
		sprint(&doom->player.stat);
	else if (key == SDLK_r)
		reload(&(doom->player.weapons[doom->player.hand]));
	else if (key == SDL_BUTTON_LEFT)
		shoot(&doom->player);
	else if (key == SDLK_y)
		fire(doom);
}

static void delaypcmasterrace(t_doom *doom)
{
	if (doom->sdl.timp == SDL_GetTicks() / 1000)
		++doom->sdl.fps;
	else
	{
		ft_printf("\r%d FPS", doom->sdl.fps);
		doom->sdl.fps = 0;
		doom->sdl.timp = SDL_GetTicks() / 1000;
	}
	while (SDL_GetTicks() - doom->timestamp < 16)
		; // Limiteur de FPS (16)
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
		pos = doom->edit.keys;
		while (pos)
		{
			editor_loop(doom, pos->data);
			pos = pos->next;
		}
		SDL_RenderClear(doom->edit.rend);
		draw_map(&doom->edit);
		draw_sector_menu(&doom->edit, doom->ui.fonts);
		sdl_int_put(doom->edit.rend, doom->ui.fonts.s32, (t_vct2){180, 10}, "x: ", doom->edit.mapmouse.x, (SDL_Color){250, 50, 50, 255});
		sdl_int_put(doom->edit.rend, doom->ui.fonts.s32, (t_vct2){180, 40}, "y: ", doom->edit.mapmouse.y, (SDL_Color){250, 50, 50, 255});
		SDL_RenderPresent(doom->edit.rend);
	}
	else
	{
		if (doom->ui.m_status == 0)
		{
			/// Place here functions that need to be launch every frame while the game is running
			move(&doom->player.stat);
			doom_render(doom);
			/// End Comment
		}
		else
		{
			/// Place here functions that need to be launch every frame while in the menu
			if (doom->ui.m_status == 5 && doom->ui.currslid == &(doom->ui.slidopt[0]))
				doom_render(doom);
			else if (doom->ui.m_status == 4 || doom->ui.m_status == 5)
				sdl_MultiRenderCopy(&doom->sdl);
			else
				fire(doom);
			draw_menu(doom);
      
			/// End Comment
		}
    SDL_RenderPresent(doom->sdl.rend);
	}
	delaypcmasterrace(doom);
	return (0);
}
