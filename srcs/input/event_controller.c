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
	if (e.jbutton.button == SDL_CONTROLLER_BUTTON_START)
		sdl_set_status(doom, 1);
	ft_printf("%d\n", e.jbutton.button);
}

void controller_handler(t_doom *doom, SDL_Event e)
{
	if (e.type == SDL_CONTROLLERAXISMOTION)
	{
		if (e.jaxis.axis == 0) // Move x
		{
			if (JOYSTICK_DEAD_ZONE < e.jaxis.value || e.jaxis.value < -JOYSTICK_DEAD_ZONE)
				doom->vel.y = -e.jaxis.value;
			else
				doom->vel.y = 0;
		}
		else if (e.jaxis.axis == 1) // Move y
		{
			if (JOYSTICK_DEAD_ZONE < e.jaxis.value || e.jaxis.value < -JOYSTICK_DEAD_ZONE)
				doom->vel.x = e.jaxis.value;
			else
				doom->vel.x = 0;
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
	}
	else
		controller_input(doom, e);
}
