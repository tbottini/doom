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

static void		on_menu_one(t_wolf *doom, int x, int y)
{
	t_btn	tmp;
	int		i;

	i = -1;
	while (doom->ui.btnarr[++i].txture)
	{
		tmp = doom->ui.btnarr[i];
		if (tmp.loc.area.x <= x && x <= tmp.loc.area.x + tmp.loc.area.w
			&& tmp.loc.area.y <= y && y <= tmp.loc.area.y + tmp.loc.area.h)
		{
			if (i == 1)
			{
				doom->ui.m_status = 2;
				load_map_btns(doom);
				draw_menu(doom);
			}
			else if (i == 2)
			{
				doom->ui.m_status = 3;
				draw_menu(doom);
			}
			else if (i == 3)
				prog_quit(doom);
		}
	}
}

static void		on_menu_two(t_wolf *doom, int x, int y)
{
	t_btn	tmp;
	int		i;

	i = -1;
	while (doom->ui.btnmap[++i].txture)
	{
		tmp = doom->ui.btnmap[i];
		if (tmp.loc.area.x <= x && x <= tmp.loc.area.x + tmp.loc.area.w
			&& tmp.loc.area.y <= y && y <= tmp.loc.area.y + tmp.loc.area.h)
		{
			if (i == 0)
			{
				doom->ui.m_status = 1;
				draw_menu(doom);
			}
			else if (i > 1)
			{
				if (wolf_parseur(doom, tmp.data))
				{
					doom->ui.m_status = 0;
					draw_menu(doom);
				}
			}
		}
	}
}

static void		on_menu_tree(t_wolf *doom, int x, int y)
{
	t_btn	tmp;
	t_slid	stmp;
	int		i;

	i = -1;
	while (doom->ui.btnopt[++i].txture)
	{
		tmp = doom->ui.btnopt[i];
		if (tmp.loc.area.x <= x && x <= tmp.loc.area.x + tmp.loc.area.w
			&& tmp.loc.area.y <= y && y <= tmp.loc.area.y + tmp.loc.area.h)
			if (i == 0)
			{
				doom->ui.m_status = 1;
				draw_menu(doom);
			}
	}
	i = -1;
	while (doom->ui.slidopt[++i].txture)
	{
		stmp = doom->ui.slidopt[i];
		if (stmp.grip.x <= x && x <= stmp.grip.x + stmp.grip.w
				&& stmp.grip.y <= y && y <= stmp.grip.y + stmp.grip.h)
			doom->ui.currslid = &(doom->ui.slidopt[i]);
	}
}

void			btn_click(t_wolf *doom, int x, int y)
{
	if (doom->ui.m_status == 1)
		on_menu_one(doom, x, y);
	else if (doom->ui.m_status == 2)
		on_menu_two(doom, x, y);
	else if (doom->ui.m_status == 3)
		on_menu_tree(doom, x, y);
}
