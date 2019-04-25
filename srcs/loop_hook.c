/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 20:45:19 by magrab            #+#    #+#             */
/*   Updated: 2019/04/23 11:50:18 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		lil_lil_loop(t_wolf *wolf, int key)
{
	double dx;
	double dy;

	dx = sin(wolf->rot * PI180) / 10;
	dy = cos(wolf->rot * PI180) / 10;
	if ((key == SDLK_w
		&& wolf->map[(int)(wolf->pos.y + dx)][(int)(wolf->pos.x + dy)] != '#')
		|| (key == SDLK_s
		&& wolf->map[(int)(wolf->pos.y - dx)][(int)(wolf->pos.x - dy)] != '#'))
	{
		wolf->pos.x += (key == SDLK_w ? dy : -dy);
		wolf->pos.y += (key == SDLK_w ? dx : -dx);
	}
	else if ((key == SDLK_a
		&& wolf->map[(int)(wolf->pos.y + dy)][(int)(wolf->pos.x - dx)] != '#')
		|| (key == SDLK_d
		&& wolf->map[(int)(wolf->pos.y - dy)][(int)(wolf->pos.x + dx)] != '#'))
	{
		wolf->pos.x += (key == SDLK_a ? -dx : dx);
		wolf->pos.y += (key == SDLK_a ? dy : -dy);
	}
}

static void		lil_loop(t_wolf *wolf, int key)
{
	if (key == SDLK_e)
	{
		if (wolf->rot - 5.0 < 0.0)
			wolf->rot += 355.0;
		else
			wolf->rot -= 5.0;
	}
	else if (key == SDLK_q)
	{
		if (wolf->rot + 5.0 > 360.0)
			wolf->rot -= 355.0;
		else
			wolf->rot += 5.0;
	}
	else
		lil_lil_loop(wolf, key);
}

int				loop_hook(t_wolf *wolf)
{
	t_tab			pos;
	struct timespec	spec;

	pos = wolf->sdl.keys;
	while (pos)
	{
		lil_loop(wolf, pos->data);
		pos = pos->next;
	}
	if (wolf->ui.m_status == 0)
	{
		raycasting(wolf);
		clock_gettime(CLOCK_REALTIME, &spec);
		while ((spec.tv_sec * 1000000 + spec.tv_nsec / 1000)
									- wolf->timestamp < 25000)
			clock_gettime(CLOCK_REALTIME, &spec);
		wolf->timestamp = spec.tv_sec * 1000000 + spec.tv_nsec / 1000;
	}
	return (0);
}
