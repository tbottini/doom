/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:19:51 by magrab            #+#    #+#             */
/*   Updated: 2019/04/21 15:15:05 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		start_btn(t_wolf *wolf)
{
	wolf->sdl.m_status = 2;
	load_map_btns(wolf);
	draw_menu(wolf);
}

static void		option_btn(t_wolf *wolf)
{
	wolf->sdl.m_status = 3;
	draw_menu(wolf);
}

static void		on_menu_one(t_wolf *wolf, int x, int y)
{
	t_btn	tmp;
	int		i;

	i = -1;
	while (wolf->sdl.btnarr[++i].txture)
	{
		tmp = wolf->sdl.btnarr[i];
		if (tmp.area.x <= x && x <= tmp.area.x + tmp.area.w
			&& tmp.area.y <= y && y <= tmp.area.y + tmp.area.h)
		{
			ft_printf("Click on btn %d\n", i);
			if (i == 1)
				start_btn(wolf);
			else if (i == 2)
				option_btn(wolf);
			else if (i == 3)
				prog_quit(wolf);
		}
	}
}

static void		on_menu_two(t_wolf *wolf, int x, int y)
{
	t_btn	tmp;
	int		i;

	i = -1;
	while (wolf->sdl.btnmap[++i].txture)
	{
		tmp = wolf->sdl.btnmap[i];
		if (tmp.area.x <= x && x <= tmp.area.x + tmp.area.w
			&& tmp.area.y <= y && y <= tmp.area.y + tmp.area.h)
		{
			if (i == 0)
			{
				wolf->sdl.m_status = 1;
				draw_menu(wolf);
			}
			else if (i > 1)
			{
				if (wolf_parseur(wolf, tmp.data))
				{
					wolf->sdl.m_status = 0;
					draw_menu(wolf);
				}
			}
		}
	}
}

static void		on_menu_tree(t_wolf *wolf, int x, int y)
{
	t_btn	tmp;
	int		i;

	i = -1;
	while (wolf->sdl.btnopt[++i].txture)
	{
		ft_printf("Found btn %d\n", i);
		tmp = wolf->sdl.btnopt[i];
		if (tmp.area.x <= x && x <= tmp.area.x + tmp.area.w
			&& tmp.area.y <= y && y <= tmp.area.y + tmp.area.h)
		{
			ft_printf("Click on btn %d\n", i);
			if (i == 0)
			{
				wolf->sdl.m_status = 1;
				draw_menu(wolf);
			}
		}
	}
}

void			btn_click(t_wolf *wolf, int x, int y)
{
	if (wolf->sdl.m_status == 1)
		on_menu_one(wolf, x, y);
	else if (wolf->sdl.m_status == 2)
		on_menu_two(wolf, x, y);
	else if (wolf->sdl.m_status == 3)
		on_menu_tree(wolf, x, y);
}
