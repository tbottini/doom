/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 20:45:19 by magrab            #+#    #+#             */
/*   Updated: 2019/08/04 11:29:14 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Add here function that need to be done every frame when a key is pressed
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

int			debug = 0;
int			debug_screen = 0;

void		benda(t_doom *doom, int key)
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

static void input_loop(t_doom *doom, int key)
{
	if ((key == SDLK_w || key == SDLK_s || key == SDLK_a || key == SDLK_d))
		benda(doom, key);
	else if (key == SDLK_LSHIFT && doom->game.player.stat.vel.x == doom->game.player.stat.speed)
		sprint(&doom->game.player.stat);
	else if (key == SDLK_SPACE)
		jump(&doom->game.player.stat, &doom->game.player.inv);
	else if (key == SDLK_LGUI && !doom->game.player.inv.jetpack)
		fly_down(&doom->game.player.stat);
	else if (doom->timestamp > doom->game.player.occupied)
	{
		if (key == SDL_BUTTON_LEFT)
			shoot(doom->timestamp, &doom->game.sound, &doom->game.player);
		else if (key == SDLK_0)//test effects
			play_effect(&doom->game.sound, 8);
	}
}

static void editor_loop(t_doom *doom, int key)
{
	//printf("key : %d %c\n", key, key);
	if (key == SDLK_KP_PLUS || key == SDLK_KP_MINUS)
	{
		scroll_limits(&doom->edit.mappos.z, (key == SDLK_KP_PLUS ? 2 : -2) * (doom->edit.mappos.z / 400 * ZOOMSPEED + 1), MINZOOM, MAXZOOM);
	}
	else if (key == SDLK_KP_4 || key == SDLK_KP_6)
	{
		doom->edit.mappos.x += (key == SDLK_KP_4 ? 2 : -2);
	}
	else if (key == SDLK_KP_8 || key == SDLK_KP_2)
	{
		doom->edit.mappos.y += (key == SDLK_KP_8 ? 2 : -2);
	}
}

static void delaypcmasterrace(t_doom *doom)
{
	int wait;

	debug = 0;
	// A Supprimer lorqu'il n'y aura plus besoin d'afficher les FPS
	if (doom->sdl.timp / 1000 == SDL_GetTicks() / 1000)
	{
		++doom->sdl.fps;
	}
	else
	{
		ft_printf("\r%d FPS", doom->sdl.fps);
		doom->sdl.fps = 0;
		doom->sdl.timp = SDL_GetTicks();
	}
	// END A Supprimer
	wait = SDL_GetTicks() - doom->timestamp - 16; // Nombre de ms min entre chaque frame
	if (wait < 0)
		SDL_Delay(-wait);
	doom->timestamp = SDL_GetTicks();
}

static void game_loop_hook(t_doom *doom)
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
		/// Place here functions that need to be launch every frame while the game is running
		move(&doom->game.player.stat, &doom->game.player.inv);
		pickup_prop(doom);
		check_boost(doom->timestamp, &doom->game.player);
		armandtificial_intelligence(doom);
		if (doom->game.player.stat.health <= 0)
			game_over(doom, false);
		else
		{
			doom_render(doom);
			hud_render(doom);
		}
		/// End Comment
	}
	else
	{
		/// Place here functions that need to be launch every frame while in the menu
		if (doom->ui.m_status == MENU_IGOPTION && doom->ui.currslid == &(doom->ui.slidopt[0]))
			doom_render(doom);
		else if (doom->ui.m_status == MENU_IGMAIN || doom->ui.m_status == MENU_IGOPTION)
			sdl_MultiRenderCopy(&doom->sdl);
		else
		{
			fire(&doom->ui.fire);
			sdl_MultiRenderCopy(&doom->sdl);
		}
		draw_menu(doom);
		/// End Comment
	}
	SDL_RenderPresent(doom->sdl.rend);
}

static void editor_loop_hook(t_doom *doom)
{
	t_tab pos;

	pos = doom->edit.keys;
	while (pos)
	{
		editor_loop(doom, pos->data);
		pos = pos->next;
	}
	SDL_RenderClear(doom->edit.rend);
	draw_map(&doom->edit);
	draw_sector_menu(&doom->edit, doom->ui.fonts);
	if (doom->edit.map || doom->edit.currmur || doom->edit.currstat)
		draw_inspect_menu(&doom->edit);
	if (ISWRITING(doom->edit.status))
		draw_writer(&doom->edit);
	sdl_int_put(doom->edit.rend, doom->ui.fonts.s32, (t_vct2){180, 10}, "x: ", doom->edit.mapmouse.x, (SDL_Color){250, 50, 50, 255});
	sdl_int_put(doom->edit.rend, doom->ui.fonts.s32, (t_vct2){180, 40}, "y: ", doom->edit.mapmouse.y, (SDL_Color){250, 50, 50, 255});
	SDL_RenderPresent(doom->edit.rend);
}

int loop_hook(t_doom *doom)
{
	SDL_RenderClear(doom->sdl.rend);
	if (doom->edit.status)
		editor_loop_hook(doom);
	else
		game_loop_hook(doom);
	delaypcmasterrace(doom);
	return (0);
}
