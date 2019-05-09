/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:18:09 by magrab            #+#    #+#             */
/*   Updated: 2019/05/09 12:57:55 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int			key_press(int key, t_doom *doom)
{
	if (key == SDLK_BACKQUOTE)
		sdl_set_status(doom, 1);
	else if (key == SDLK_5)
		ft_printf("controller : %d\n", SDL_GameControllerEventState(SDL_ENABLE));
	else if (key == SDLK_5)
		ft_printf("controller : %d\n", SDL_GameControllerEventState(SDL_ENABLE));
	else if (key == SDLK_SPACE)
		;//jump();
	else if (key == SDLK_v)
		;//kick(&(doom->player), /*sector*/);
	else if (key == SDLK_r)
		reload(&(doom->player.weapons[doom->player.hand]));
	else if (key == SDLK_e)
		action(doom);
	else
		ft_nodeadd_int(&(doom->sdl.keys), key);
	return (0);
}

int			key_release(int key, t_doom *doom)
{
	ft_noderm_int(&(doom->sdl.keys), key);
	if (key == SDLK_w || key == SDLK_s)
	{
		//doom->vel.x = 0;
	}
	else if (key == SDLK_a || key == SDLK_d)
	{
		//doom->vel.y = 0;
	}
	else if (key == SDLK_q || key == SDLK_e)
	{
		//doom->nrot = 0;
	}
	else if (key == SDLK_LGUI)
		crouch_release(doom);
	return (0);
}

int			mouse_press(int btn, int x, int y, t_doom *doom)
{
	if (btn == SDL_BUTTON_LEFT)
	{
		if (doom->ui.m_status != 0)
			btn_click(doom, x, y);
		else if (!(doom->player.weapons[doom->player.hand].rate))
			shoot(doom);
		else
			ft_nodeadd_int(&(doom->sdl.keys), SDL_BUTTON_LEFT);
	}
	else if (btn == SDL_BUTTON_X1)
		next_weapon(&(doom->player));
	else if (btn == SDL_BUTTON_X2)
		prev_weapon(&(doom->player));
	return (0);
}

int			mouse_release(int btn, int x, int y, t_doom *doom)
{
	doom->ui.currslid = NULL;
	(void)x;
	(void)y;
	if (btn == SDL_BUTTON_LEFT && doom->player.weapons[doom->player.hand].rate)
		ft_noderm_int(&(doom->sdl.keys), btn);
	return (0);
}

int			mouse_move(int x, int y, t_doom *doom)
{
	int		xload;
	int		size;
	t_btn	*curr_btn;
	t_slid	*tmp;

	curr_btn = btn_hover(doom, x, y);
	if (doom->ui.curr_btn != curr_btn)
	{
		draw_hover(doom, curr_btn, doom->ui.curr_btn);
		doom->ui.curr_btn = curr_btn;
	}
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
