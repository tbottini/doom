/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 20:45:19 by magrab            #+#    #+#             */
/*   Updated: 2019/04/19 20:45:20 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int loop_hook(t_wolf *wolf)
{
	t_tab pos;
	int key;

	pos = wolf->sdl.keys;
	while (pos)
	{
		key = pos->data;
		if (key == SDLK_e)
		{
			if (wolf->rot - 5.0 < -180.0)
				wolf->rot += 355.0;
			else
				wolf->rot -= 5;
		}
		else if (key == SDLK_q)
		{
			if (wolf->rot + 5.0 > 180.0)
				wolf->rot -= 355.0;
			else
				wolf->rot += 5;
		}
		else if (key == SDLK_w)
		{
			if (wolf->map[(int)(wolf->pos.y + 0.1)][(int)wolf->pos.x] != '#')
				wolf->pos.y += 0.1;
		}
		else if (key == SDLK_s)
		{
			if (wolf->map[(int)(wolf->pos.y - 0.1)][(int)wolf->pos.x] != '#')
				wolf->pos.y -= 0.1;
		}
		else if (key == SDLK_d)
		{
			if (wolf->map[(int)wolf->pos.y][(int)(wolf->pos.x + 0.1)] != '#')
				wolf->pos.x += 0.1;
		}
		else if (key == SDLK_a)
		{
			if (wolf->map[(int)wolf->pos.y][(int)(wolf->pos.x - 0.1)] != '#')
				wolf->pos.x -= 0.1;
		}
		pos = pos->next;
	}
	return (0);
}
