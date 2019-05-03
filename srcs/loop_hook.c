/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 20:45:19 by magrab            #+#    #+#             */
/*   Updated: 2019/04/28 15:16:10 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void lil_loop(t_doom *doom, int key)
{
	if (key == SDLK_w || key == SDLK_s)
		doom->vel.x = (key == SDLK_w ? -32700 : 32700);
	else if (key == SDLK_a || key == SDLK_d)
		doom->vel.y = (key == SDLK_a ? 32700 : -32700);
	else if (key == SDLK_q || key == SDLK_e)
		doom->nrot = (key == SDLK_q ? 5 : -5);
}

int loop_hook(t_doom *doom)
{
	t_tab pos;
	struct timespec spec;

	pos = doom->sdl.keys;
	while (pos && doom->map)
	{
		lil_loop(doom, pos->data);
		pos = pos->next;
	}
	if (doom->ui.m_status == 0)
	{
		move(doom, doom->vel.x, doom->vel.y);
		raycasting(doom);
		clock_gettime(CLOCK_REALTIME, &spec);
		while ((spec.tv_sec * 1000000 + spec.tv_nsec / 1000) - doom->timestamp < 25000)
			clock_gettime(CLOCK_REALTIME, &spec);
		doom->timestamp = spec.tv_sec * 1000000 + spec.tv_nsec / 1000;
	}
	return (0);
}
