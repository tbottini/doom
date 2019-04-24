/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:18:09 by magrab            #+#    #+#             */
/*   Updated: 2019/04/24 21:08:31 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int key_press(int key, t_wolf *wolf)
{
	int j;
	if (key == SDLK_BACKQUOTE)
	{
		wolf->sdl.m_status = 1;
		draw_menu(wolf);
	}
	if (key == SDLK_g)
	{
		j = wolf->map_size.x - 1;
		while (j + 1)
		{
			ft_putendl(wolf->map[j]);
			j--;
		}
	}
	else
	{
		ft_nodeadd_int(&(wolf->sdl.keys), key);
	}
	//printf("wolfrot %f wolfpos .x %f .y %f\n", wolf->rot, wolf->pos.x, wolf->pos.y);
	return (0);
}

int key_release(int key, t_wolf *wolf)
{
	ft_noderm_int(&(wolf->sdl.keys), key);
	return (0);
}

int mouse_press(int btn, int x, int y, t_wolf *wolf)
{
	if (btn == SDL_BUTTON_LEFT)
		btn_click(wolf, x, y);
	else if (btn == 4)
		wolf->fov++;
	else if (btn == 5)
		wolf->fov--;
	//ft_printf("Mouse p %d at %d : %d\n", btn, x, y);
	return (0);
}

int mouse_release(int btn, int x, int y, t_wolf *wolf)
{
	(void)wolf;
	(void)x;
	(void)y;
	(void)btn;
	//ft_printf("Mouse r %d at %d : %d\n", btn, x, y);
	return (0);
}

int mouse_move(int x, int y, t_wolf *wolf)
{
	wolf->sdl.m_pos.x = x;
	wolf->sdl.m_pos.y = y;
	return (0);
}
