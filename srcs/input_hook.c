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

int		key_press(int key, t_doom *doom)
{
	if (key == SDLK_BACKQUOTE)
	{
		doom->ui.curr_btn = NULL;
		sdl_set_status(doom, 1);
	}
	else if (key == SDLK_5)
	{
		ft_printf("controller:%d\n", SDL_GameControllerEventState(SDL_ENABLE));
	}
	else
	{
		ft_nodeadd_int(&(doom->sdl.keys), key);
	}
	return (0);
}

int		key_release(int key, t_doom *doom)
{
	ft_noderm_int(&(doom->sdl.keys), key);
	if (key == SDLK_w || key == SDLK_s)
	{
		doom->vel.x = 0;
	}
	else if (key == SDLK_a || key == SDLK_d)
	{
		doom->vel.y = 0;
	}
	else if (key == SDLK_q || key == SDLK_e)
	{
		doom->nrot = 0;
	}
	return (0);
}

int		mouse_press(int btn, int x, int y, t_doom *doom)
{
	t_btn *curr_btn;

	if (btn == SDL_BUTTON_LEFT)
	{
		doom->ui.curr_btn = NULL;
		curr_btn = btn_hover(doom, x, y);
		if (curr_btn && curr_btn->func)
			(*curr_btn->func)(doom);
		else
			btn_click(doom, x, y);
	}
	else if (btn == SDL_BUTTON_RIGHT)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	return (0);
}

int		mouse_release(int btn, int x, int y, t_doom *doom)
{
	doom->ui.currslid = NULL;
	(void)x;
	(void)y;
	(void)btn;
	return (0);
}

int		mouse_move(int x, int y, t_doom *doom)
{
	int		xload;
	t_btn	*curr_btn;
	t_slid	*tmp;

	doom->sdl.m_pos.x = x;
	doom->sdl.m_pos.y = y;
	curr_btn = btn_hover(doom, x, y);
	if (doom->ui.curr_btn != curr_btn)
	{
		if ((curr_btn && (curr_btn->func || curr_btn->data)) || !curr_btn)
			draw_hover(doom, curr_btn, doom->ui.curr_btn);
		doom->ui.curr_btn = curr_btn;
	}
	if (doom->ui.currslid)
	{
		tmp = doom->ui.currslid;
		xload = ((x - tmp->loc.area.x) / (double)tmp->loc.area.w
								* (tmp->max - tmp->min)) + tmp->min;
		if (tmp->min <= xload && xload <= tmp->max)
		{
			update_slider_value(doom, tmp, xload);
			draw_slid(doom, tmp);
		}
	}
	return (0);
}
