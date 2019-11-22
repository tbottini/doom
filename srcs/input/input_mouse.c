/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 07:16:17 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 07:52:42 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Add here function that need to be done when mouse is pressed
** Example :
** else if (btn == SDL_BUTTON_yourbutton)
**		action();
*/

int			mouse_press(int btn, int x, int y, t_doom *doom)
{
	t_btn *curr_btn;

	SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
	if (btn == SDL_BUTTON_LEFT)
	{
		curr_btn = btn_hover(doom, x, y);
		if (curr_btn && curr_btn->func)
			(*curr_btn->func)(doom);
		else
		{
			if (doom->ui.m_status != 0)
				btn_click(doom, x, y);
			else if (!(doom->game.player.hand->rate))
				shoot(doom->timestamp, &doom->game.sound,
				&doom->game.player, doom->game.len.nb_sects);
			else
				ft_nodeadd_int(&(doom->sdl.keys), SDL_BUTTON_LEFT);
		}
	}
	return (0);
}

int			mouse_wheel(SDL_MouseWheelEvent e, t_doom *doom)
{
	if (doom->ui.m_status == MENU_INGAME)
	{
		if (e.y > 0)
			prev_weapon(&doom->game.player);
		else if (e.y < 0)
			next_weapon(&doom->game.player);
	}
	else if (doom->ui.m_status == MENU_MAP)
	{
		if (doom->ui.btnmap[1].loc.pos.y + e.y > 5)
			doom->ui.btnmap[1].loc.pos.y = 5;
		else
			doom->ui.btnmap[1].loc.pos.y += e.y;
	}
	return (0);
}

/*
** Add here function that need to be done when mouse is released
** Example :
** else if (btn == SDL_BUTTON_yourbutton)
**		action();
*/

int			mouse_release(int btn, int x, int y, t_doom *doom)
{
	doom->ui.currslid = NULL;
	(void)btn;
	(void)x;
	(void)y;
	ft_noderm_int(&(doom->sdl.keys), btn);
	return (0);
}

static void	mouse_slider(int x, int y, t_doom *doom)
{
	t_slid *tmp;

	(void)y;
	SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE));
	tmp = doom->ui.currslid;
	update_slider_value(doom, tmp, x);
	if (tmp == &(doom->ui.slidopt[0]))
		doom->game.camera.d_screen = (doom->sdl.size.x / 2.0)
		/ tan(doom->game.player.fov / 2.0 * PI180);
	else if (tmp == &(doom->ui.slidopt[1]))
		Mix_VolumeMusic(doom->game.sound.musicvolume);
	else if (tmp == &(doom->ui.slidopt[2]))
		effect_volume(&doom->game.sound);
}

/*
** Add here function that need to be done when mouse if moved in window
** x and y are relative postions when in gamemode
*/

int			mouse_move(int x, int y, t_doom *doom)
{
	doom->sdl.m_pos.x = x;
	doom->sdl.m_pos.y = y;
	doom->ui.curr_btn = btn_hover(doom, x, y);
	if (doom->ui.curr_btn && doom->ui.curr_btn->func)
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
	else
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
	if (doom->ui.m_status == MENU_INGAME)
	{
		doom->game.player.stat.rot.y -= x / SENSIBILITY;
		doom->game.player.stat.rot.x -= y / (SENSIBILITY * 2);
		return (0);
	}
	if (doom->ui.currslid)
	{
		mouse_slider(x, y, doom);
	}
	return (0);
}
