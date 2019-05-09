/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 20:45:19 by magrab            #+#    #+#             */
/*   Updated: 2019/05/09 13:07:25 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void input_loop(t_doom *doom, int key)
{
	if (key == SDLK_w || key == SDLK_s)
		doom->player.vel.x = (key == SDLK_w ? -32700 : 32700);
	else if (key == SDLK_a || key == SDLK_d)
		doom->player.vel.y = (key == SDLK_a ? 32700 : -32700);
	else if (key == SDLK_LSHIFT)
		sprint(doom);
	else if (key == SDLK_r)
		reload(&(doom->player.weapons[doom->player.hand]));
	else if (key == SDL_BUTTON_LEFT)
		shoot(doom);
	else if (key == SDLK_LGUI)
		crouch(doom);
	//else if (key == SDLK_q || key == SDLK_e)
		//doom->nrot = (key == SDLK_q ? 5 : -5);
}

int loop_hook(t_doom *doom)
{
	t_tab pos;
	struct timespec spec;

	pos = doom->sdl.keys;
	while (pos /*&& doom->map*/)
	{
		input_loop(doom, pos->data);
		pos = pos->next;
	}
	if (doom->ui.m_status == 0)
	{
		move(doom, doom->player.vel.x, doom->player.vel.y);
		//raycasting(doom);
		clock_gettime(CLOCK_REALTIME, &spec);
		while ((spec.tv_sec * 1000000 + spec.tv_nsec / 1000) - doom->timestamp < 25000)
			clock_gettime(CLOCK_REALTIME, &spec);
		doom->timestamp = spec.tv_sec * 1000000 + spec.tv_nsec / 1000;
	}
	return (0);
}
