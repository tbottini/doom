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

#include "wolf3d.h"

static void		limit_walk(t_wolf *wolf, t_fvct2 n)
{
	if (n.x < wolf->map_size.x - 0.1 && n.y < wolf->map_size.y - 0.1
		&& n.x > 0.1 && n.y > 0.1)
	{
		wolf->pos.x = n.x;
		wolf->pos.y = n.y;
	}
}

static void		lil_lil_loop(t_wolf *wolf, int key)
{
	double		dx;
	double		dy;
	t_fvct2		new_pos;

	new_pos.x = 0.0;
	new_pos.y = 0.0;
	dx = sin(wolf->rot * PI180) / 10;
	dy = cos(wolf->rot * PI180) / 10;
	if ((key == SDLK_w
		&& wolf->map[(int)(wolf->pos.y + dx)][(int)(wolf->pos.x + dy)] != '#')
		|| (key == SDLK_s
		&& wolf->map[(int)(wolf->pos.y - dx)][(int)(wolf->pos.x - dy)] != '#'))
	{
		new_pos.x += (key == SDLK_w ? dy : -dy) + wolf->pos.x;
		new_pos.y += (key == SDLK_w ? dx : -dx) + wolf->pos.y;
	}
	else if ((key == SDLK_a
		&& wolf->map[(int)(wolf->pos.y + dy)][(int)(wolf->pos.x - dx)] != '#')
		|| (key == SDLK_d
		&& wolf->map[(int)(wolf->pos.y - dy)][(int)(wolf->pos.x + dx)] != '#'))
	{
		new_pos.x += (key == SDLK_a ? -dx : dx) + wolf->pos.x;
		new_pos.y += (key == SDLK_a ? dy : -dy) + wolf->pos.y;
	}
	limit_walk(wolf, new_pos);
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
	while (pos && wolf->map)
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
