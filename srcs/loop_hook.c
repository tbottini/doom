/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 20:45:19 by magrab            #+#    #+#             */
/*   Updated: 2019/04/22 13:46:06 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		lil_lil_loop(t_wolf *wolf, int key)
{
	double x_dir;
	double y_dir;

	x_dir = sin(wolf->rot * PI180) / 10;
	y_dir = cos(wolf->rot * PI180) / 10;
	if (key == SDLK_w)
	{
		if (wolf->map[(int)(wolf->pos.y + x_dir)][(int)(wolf->pos.x + y_dir)] != '#')
		{
			wolf->pos.x += y_dir;
			wolf->pos.y += x_dir;
		}
	}
	else if (key == SDLK_a)
	{
		if (wolf->map[(int)(wolf->pos.y + y_dir)][(int)(wolf->pos.x - x_dir)] != '#')
		{
			wolf->pos.x -= x_dir;
			wolf->pos.y += y_dir;
		}
	}
	else if (key == SDLK_s)
	{
		if (wolf->map[(int)(wolf->pos.y - x_dir)][(int)(wolf->pos.x - y_dir)] != '#')
		{
			wolf->pos.x -= y_dir;
			wolf->pos.y -= x_dir;
		}
	}
	else if (key == SDLK_d)
	{
		if (wolf->map[(int)(wolf->pos.y - y_dir)][(int)(wolf->pos.x + x_dir)] != '#')
		{
			wolf->pos.x += x_dir;
			wolf->pos.y -= y_dir;
		}
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
	t_tab pos;
	struct timespec spec;

	pos = wolf->sdl.keys;
	while (pos)
	{
		lil_loop(wolf, pos->data);
		pos = pos->next;
	}
	if (wolf->sdl.m_status == 0)
	{
		raycasting(wolf);
		clock_gettime(CLOCK_REALTIME, &spec);
		while ((spec.tv_sec * 1000000 + spec.tv_nsec / 1000) - wolf->timestamp < 40000)
			clock_gettime(CLOCK_REALTIME, &spec);
		ft_printf("FPS : %d\n", (spec.tv_sec * 1000000 + spec.tv_nsec / 1000) - wolf->timestamp);
		wolf->timestamp = spec.tv_sec * 1000000 + spec.tv_nsec / 1000;
		//printf("pos x : %d\t%d\t%c\t%f\n", (int)wolf->pos.x, (int)wolf->pos.y, wolf->map[(int)wolf->pos.y][(int)wolf->pos.x], wolf->rot);
	}
	return (0);
}
