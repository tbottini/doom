/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:18:09 by magrab            #+#    #+#             */
/*   Updated: 2019/06/19 17:55:32 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Add here function that need to be done when a key is pressed (wont trigger in loop_hook)
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

int		key_press(int key, t_doom *doom)
{
	if (doom->ui.curr_btn_controller > 0)
		doom->ui.curr_btn_controller = -doom->ui.curr_btn_controller;
	else if (key == SDLK_RETURN || key == SDLK_BACKQUOTE)
	{
		if (doom->ui.m_status == 0)
			sdl_set_status(doom, 4);
		else if (doom->ui.m_status == 4)
			sdl_set_status(doom, 0);
	}
	else if (key == SDLK_r && !doom->ui.m_status)
		reload(&(doom->player.weapons[doom->player.hand]));
	else if (key == SDLK_e && !doom->ui.m_status)
		action(&doom->player, &doom->player.stat);
	else if (key == SDLK_LGUI && !doom->ui.m_status)
		crouch(&doom->player);
	else if (key == SDLK_g)
		describe_player(doom->player);
	else if (key == SDLK_h)
		describe_sector(*doom->sector);
	else if (key == SDLK_9)
		change_music(&doom->sound, 10, 5000);
	else if (key == SDLK_v && !doom->ui.m_status)
		kick(doom, &doom->player);
	else
		ft_nodeadd_int(&(doom->sdl.keys), key);
	return (0);
}

/*
** Add here function that need to be done when a key is released
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

int		key_release(int key, t_doom *doom)
{
	ft_noderm_int(&(doom->sdl.keys), key);
	/*if (key == SDLK_w || key == SDLK_s)
	{
		//doom->player.stat.vel.x = 0;
	}
	else if (key == SDLK_a || key == SDLK_d)
	{
		//doom->player.stat.vel.y = 0;
	}
	else if (key == SDLK_q || key == SDLK_e)
	{
		doom->player.stat.rotvel.y = 0.0;
	}*/
	if (key == SDLK_w || key == SDLK_LSHIFT)
		sprint_release(&doom->player.stat);
	else if (key == SDLK_LGUI)
		crouch_release(&doom->player);
	return (0);
}

/*
** Add here function that need to be done when mouse is pressed
** Example :
** else if (btn == SDL_BUTTON_yourbutton)
**		action();
*/

int		mouse_press(int btn, int x, int y, t_doom *doom)
{
	t_btn *curr_btn;

	SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
	if (btn == SDL_BUTTON_LEFT)
	{
		//doom->ui.curr_btn = NULL;
		curr_btn = btn_hover(doom, x, y);
		if (curr_btn && curr_btn->func)
			(*curr_btn->func)(doom);
		else
		{
			if (doom->ui.m_status != 0)
				btn_click(doom, x, y);/* Better wait from visual implementation
			else if (!(doom->player.weapons[doom->player.hand].rate))
				shoot(doom);
			else
				ft_nodeadd_int(&(doom->sdl.keys), SDL_BUTTON_LEFT);*/
		}
	}
	//else if (btn == SDL_BUTTON_RIGHT)
		//fire_on_off(doom->sdl.screen, doom->sdl.size, 0); // Debug thing
	else if (btn == SDL_BUTTON_X1)
		next_weapon(&(doom->player));
	else if (btn == SDL_BUTTON_X2)
		prev_weapon(&(doom->player));
	return (0);
}

/*
** Add here function that need to be done when mouse is released
** Example :
** else if (btn == SDL_BUTTON_yourbutton)
**		action();
*/

int		mouse_release(int btn, int x, int y, t_doom *doom)
{
	doom->ui.currslid = NULL;
	(void)btn;
	(void)x;
	(void)y;
//	if (btn == SDL_BUTTON_LEFT && doom->player.weapons[doom->player.hand].rate)
//		ft_noderm_int(&(doom->sdl.keys), btn);
	return (0);
}

/*
** Add here function that need to be done when mouse if moved in window
** x and y are relative postions when in gamemode
*/

int		mouse_move(int x, int y, t_doom *doom)
{
	t_slid	*tmp;

	doom->sdl.m_pos.x = x;
	doom->sdl.m_pos.y = y;
	doom->ui.curr_btn = btn_hover(doom, x, y);
	if (doom->ui.curr_btn && doom->ui.curr_btn->func)
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
	else
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
	if (doom->ui.m_status == 0)
	{
		//ft_printf("mouse : %d\t%d\t%d\n", x, y);
		doom->player.stat.rot.y -= x / SENSIBILITY;
		doom->player.stat.rot.x -= y / (SENSIBILITY * 2);
		return (0);
	}
	if (doom->ui.currslid)
	{
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE));
		tmp = doom->ui.currslid;
		update_slider_value(doom, tmp, x);
		if (tmp == &(doom->ui.slidopt[0]))
			doom->camera.d_screen = (doom->sdl.size.x / 2.0) / tan(doom->player.fov / 2.0 * PI180);
		else if (tmp == &(doom->ui.slidopt[1]))
			Mix_VolumeMusic(doom->sound.musicvolume);
		else if (tmp == &(doom->ui.slidopt[2]))
			effect_volume(&doom->sound);
	}
	return (0);
}
