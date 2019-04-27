/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:19:51 by magrab            #+#    #+#             */
/*   Updated: 2019/04/27 13:13:45 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		on_menu_one(t_wolf *wolf, int x, int y)
{
	t_btn	tmp;
	int		i;

	i = -1;
	while (wolf->ui.btnarr[++i].txture)
	{
		tmp = wolf->ui.btnarr[i];
		if (tmp.loc.area.x <= x && x <= tmp.loc.area.x + tmp.loc.area.w
			&& tmp.loc.area.y <= y && y <= tmp.loc.area.y + tmp.loc.area.h)
		{
			if (i == 1)
			{
				wolf->ui.m_status = 2;
				load_map_btns(wolf);
				draw_menu(wolf);
			}
			else if (i == 2)
			{
				wolf->ui.m_status = 3;
				draw_menu(wolf);
			}
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
	while (wolf->ui.btnmap[++i].txture)
	{
		tmp = wolf->ui.btnmap[i];
		if (tmp.loc.area.x <= x && x <= tmp.loc.area.x + tmp.loc.area.w
			&& tmp.loc.area.y <= y && y <= tmp.loc.area.y + tmp.loc.area.h)
		{
			if (i == 0)
			{
				wolf->ui.m_status = 1;
				draw_menu(wolf);
			}
			else if (i > 1)
			{
				if (wolf_parseur(wolf, tmp.data))
				{
					wolf->ui.m_status = 0;
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
	while (wolf->ui.btnopt[++i].txture)
	{
		tmp = wolf->ui.btnopt[i];
		if (tmp.loc.area.x <= x && x <= tmp.loc.area.x + tmp.loc.area.w
			&& tmp.loc.area.y <= y && y <= tmp.loc.area.y + tmp.loc.area.h)
			if (i == 0)
			{
				wolf->ui.m_status = 1;
				draw_menu(wolf);
			}
	}
	i = -1;
	while (wolf->ui.slidopt[++i].txture)
	{
		stmp = wolf->ui.slidopt[i];
		if (stmp.grip.x <= x && x <= stmp.grip.x + stmp.grip.w
				&& stmp.grip.y <= y && y <= stmp.grip.y + stmp.grip.h)
			wolf->ui.currslid = &(wolf->ui.slidopt[i]);
	}
}

void			btn_click(t_wolf *wolf, int x, int y)
{
	if (wolf->ui.m_status == 1)
		on_menu_one(wolf, x, y);
	else if (wolf->ui.m_status == 2)
		on_menu_two(wolf, x, y);
	else if (wolf->ui.m_status == 3)
		on_menu_tree(wolf, x, y);
}
