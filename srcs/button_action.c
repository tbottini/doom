/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:19:51 by magrab            #+#    #+#             */
/*   Updated: 2019/04/22 20:27:01 by tbottini         ###   ########.fr       */
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
		if (tmp.loc.area.x <= x && x <= tmp.loc.area.x + tmp.loc.area.w
			&& tmp.loc.area.y <= y && y <= tmp.loc.area.y + tmp.loc.area.h)
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
		if (tmp.loc.area.x <= x && x <= tmp.loc.area.x + tmp.loc.area.w
			&& tmp.loc.area.y <= y && y <= tmp.loc.area.y + tmp.loc.area.h)
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
	t_slid	stmp;
	int		i;

	i = -1;
	while (wolf->sdl.btnopt[++i].txture)
	{
		//ft_printf("Found btn %d\n", i);
		tmp = wolf->sdl.btnopt[i];
		if (tmp.loc.area.x <= x && x <= tmp.loc.area.x + tmp.loc.area.w
			&& tmp.loc.area.y <= y && y <= tmp.loc.area.y + tmp.loc.area.h)
		{
			ft_printf("Click on btn %d\n", i);
			if (i == 0)
			{
				wolf->sdl.m_status = 1;
				draw_menu(wolf);
			}
		}
	}
	i = -1;
	while (wolf->sdl.slidopt[++i].txture)
	{
		stmp = wolf->sdl.slidopt[i];
		if (stmp.grip.x <= x && x <= stmp.grip.x + stmp.grip.w
			&& stmp.grip.y <= y && y <= stmp.grip.y + stmp.grip.h)
		{
			ft_printf("Click on slid %d\n", i);
			wolf->sdl.currslid = &(wolf->sdl.slidopt[i]);
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
