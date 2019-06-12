/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_controller.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:33:51 by magrab            #+#    #+#             */
/*   Updated: 2019/05/05 11:52:02 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void controller_input(t_doom *doom, SDL_Event e)
{
	if (doom->ui.curr_btn_controller < 0)
		doom->ui.curr_btn_controller = -doom->ui.curr_btn_controller;
	else if (doom->ui.m_status > 0)
	{
		if (e.jbutton.state && e.jbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP)
		{
			if (doom->ui.m_status == 1 && doom->ui.curr_btn_controller > 2)
				--doom->ui.curr_btn_controller;
			else if (doom->ui.m_status == 2)
			{
				if (doom->ui.curr_btn_controller == 3)
					doom->ui.curr_btn_controller -= 2;
				else if (doom->ui.curr_btn_controller > 3)
					--doom->ui.curr_btn_controller;
			}
		}
		else if (e.jbutton.state && e.jbutton.button == SDL_CONTROLLER_BUTTON_A)
		{
			doom->ui.curr_btn->func(doom);
		}
		if (e.jbutton.state && e.jbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
		{
			if (doom->ui.m_status == 1 && doom->ui.btnarr[doom->ui.curr_btn_controller].func)
				++doom->ui.curr_btn_controller;
			else if (doom->ui.m_status == 2)
			{
				if (doom->ui.curr_btn_controller == 1 && doom->ui.btnmap[doom->ui.curr_btn_controller + 1].txture)
					doom->ui.curr_btn_controller += 2;
				else if (doom->ui.btnmap[doom->ui.curr_btn_controller].txture)
					++doom->ui.curr_btn_controller;
			}
			else if (doom->ui.m_status == 3 && doom->ui.btnopt[doom->ui.curr_btn_controller].func)
				++doom->ui.curr_btn_controller;
		}
	}
	if (e.jbutton.button == SDL_CONTROLLER_BUTTON_START || e.jbutton.button == SDL_CONTROLLER_BUTTON_B)
		sdl_set_status(doom, 1);
	ft_printf("%d\t%d\tcurr : %d\tStatus : %d\n", e.jbutton.button, e.jbutton.state, doom->ui.curr_btn_controller, doom->ui.m_status);
}

void controller_handler(t_doom *doom, SDL_Event e)
{
	if (e.type == SDL_CONTROLLERAXISMOTION)
	{
		if (e.jaxis.axis == 0) // Move x
		{
			if (JOYSTICK_DEAD_ZONE < e.jaxis.value || e.jaxis.value < -JOYSTICK_DEAD_ZONE)
				doom->player.vel.y = e.jaxis.value;
			else
				doom->player.vel.y = 0;
		}
		else if (e.jaxis.axis == 1) // Move y
		{
			if (JOYSTICK_DEAD_ZONE < e.jaxis.value || e.jaxis.value < -JOYSTICK_DEAD_ZONE)
				doom->player.vel.x = -e.jaxis.value;
			else
				doom->player.vel.x = 0;
		}
		else if (e.jaxis.axis == 2) // Cam y
		{
			if (JOYSTICK_DEAD_ZONE < e.jaxis.value || e.jaxis.value < -JOYSTICK_DEAD_ZONE)
			{
				if (ft_abs(e.jaxis.value) > 30000)
					doom->player.rotvel.y = -e.jaxis.value / 5000.0;
				else
					doom->player.rotvel.y = -e.jaxis.value / 10000.0;
			}
			else
				doom->player.rotvel.y = 0.0;
		}
		else if (e.jaxis.axis == 3) // Cam x
		{
			if (JOYSTICK_DEAD_ZONE < e.jaxis.value || e.jaxis.value < -JOYSTICK_DEAD_ZONE)
			{
				if (ft_abs(e.jaxis.value) > 30000)
					doom->player.rotvel.x = -e.jaxis.value / 5000.0;
				else
					doom->player.rotvel.x = -e.jaxis.value / 10000.0;
			}
			else
				doom->player.rotvel.x = 0.0;
		}
	}
	else
		controller_input(doom, e);
}
