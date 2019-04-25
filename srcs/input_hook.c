/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:18:09 by magrab            #+#    #+#             */
/*   Updated: 2019/04/25 20:58:00 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int key_press(int key, t_wolf *wolf)
{
	int j;
	if (key == SDLK_BACKQUOTE)
	{
		wolf->ui.m_status = 1;
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
	return (0);
}

int mouse_release(int btn, int x, int y, t_wolf *wolf)
{
	wolf->ui.currslid = NULL;
	(void)x;
	(void)y;
	(void)btn;
	return (0);
}

int mouse_move(int x, int y, t_wolf *wolf)
{
	int xload;
	int size;
	t_slid *tmp;

	wolf->sdl.m_pos.x = x;
	wolf->sdl.m_pos.y = y;
	if (wolf->ui.currslid)
	{
		tmp = wolf->ui.currslid;
		size = tmp->loc.area.h;
		xload = ((x - tmp->loc.area.x) / (double)tmp->loc.area.w * (tmp->max - tmp->min)) + tmp->min;
		if (tmp->min <= xload && xload <= tmp->max)
		{
			*tmp->val = xload;
			draw_slid(wolf, tmp);
		}
	}
	return (0);
}
