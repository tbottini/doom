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

static void		limit_walk(t_doom *doom, t_fvct2 n)
{
	if (n.x < doom->map_size.x - 0.1 && n.y < doom->map_size.y - 0.1
		&& n.x > 0.1 && n.y > 0.1)
	{
		doom->pos.x = n.x;
		doom->pos.y = n.y;
	}
}

static void		lil_lil_loop(t_doom *doom, int key)
{
	double		dx;
	double		dy;
	t_fvct2		new_pos;

	new_pos.x = 0.0;
	new_pos.y = 0.0;
	dx = sin(doom->rot * PI180) / 10;
	dy = cos(doom->rot * PI180) / 10;
	if ((key == SDLK_w
		&& doom->map[(int)(doom->pos.y + dx)][(int)(doom->pos.x + dy)] != '#')
		|| (key == SDLK_s
		&& doom->map[(int)(doom->pos.y - dx)][(int)(doom->pos.x - dy)] != '#'))
	{
		new_pos.x += (key == SDLK_w ? dy : -dy) + doom->pos.x;
		new_pos.y += (key == SDLK_w ? dx : -dx) + doom->pos.y;
	}
	else if ((key == SDLK_a
		&& doom->map[(int)(doom->pos.y + dy)][(int)(doom->pos.x - dx)] != '#')
		|| (key == SDLK_d
		&& doom->map[(int)(doom->pos.y - dy)][(int)(doom->pos.x + dx)] != '#'))
	{
		new_pos.x += (key == SDLK_a ? -dx : dx) + doom->pos.x;
		new_pos.y += (key == SDLK_a ? dy : -dy) + doom->pos.y;
	}
	limit_walk(doom, new_pos);
}

static void		lil_loop(t_doom *doom, int key)
{
	if (key == SDLK_e)
	{
		if (doom->rot - 5.0 < 0.0)
			doom->rot += 355.0;
		else
			doom->rot -= 5.0;
	}
	else if (key == SDLK_q)
	{
		if (doom->rot + 5.0 > 360.0)
			doom->rot -= 355.0;
		else
			doom->rot += 5.0;
	}
	else
		lil_lil_loop(doom, key);
}

int				loop_hook(t_doom *doom)
{
	t_tab			pos;
	struct timespec	spec;

	pos = doom->sdl.keys;
	while (pos && doom->map)
	{
		lil_loop(doom, pos->data);
		pos = pos->next;
	}
	if (doom->ui.m_status == 0)
	{
		raycasting(doom);
		clock_gettime(CLOCK_REALTIME, &spec);
		while ((spec.tv_sec * 1000000 + spec.tv_nsec / 1000)
									- doom->timestamp < 25000)
			clock_gettime(CLOCK_REALTIME, &spec);
		doom->timestamp = spec.tv_sec * 1000000 + spec.tv_nsec / 1000;
	}
	return (0);
}
