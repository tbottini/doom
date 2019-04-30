/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:18:09 by magrab            #+#    #+#             */
/*   Updated: 2019/04/26 19:40:19 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			key_press(int key, t_doom *doom)
{
	if (key == SDLK_BACKQUOTE)
	{
		doom->ui.m_status = 1;
		wolf_clear_map(doom);
		draw_menu(doom);
	}
	else if (key == SDLK_5)
	{
		ft_printf("controller : %d\n", SDL_GameControllerEventState(SDL_ENABLE));
	}
	else
	{
		ft_nodeadd_int(&(doom->sdl.keys), key);
	}
	return (0);
}

int			key_release(int key, t_doom *doom)
{
	ft_noderm_int(&(doom->sdl.keys), key);
	return (0);
}

int			mouse_press(int btn, int x, int y, t_doom *doom)
{
	if (btn == SDL_BUTTON_LEFT)
		btn_click(doom, x, y);
	return (0);
}

int			mouse_release(int btn, int x, int y, t_doom *doom)
{
	doom->ui.currslid = NULL;
	(void)x;
	(void)y;
	(void)btn;
	return (0);
}

int			mouse_move(int x, int y, t_doom *doom)
{
	int		xload;
	int		size;
	t_slid	*tmp;

	doom->sdl.m_pos.x = x;
	doom->sdl.m_pos.y = y;
	if (doom->ui.currslid)
	{
		tmp = doom->ui.currslid;
		size = tmp->loc.area.h;
		xload = ((x - tmp->loc.area.x) / (double)tmp->loc.area.w
			* (tmp->max - tmp->min)) + tmp->min;
		if (tmp->min <= xload && xload <= tmp->max)
		{
			*tmp->val = xload;
			draw_slid(doom, tmp);
		}
	}
	return (0);
}
