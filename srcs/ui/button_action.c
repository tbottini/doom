/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:19:51 by magrab            #+#    #+#             */
/*   Updated: 2019/05/05 15:43:15 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		sdl_set_status(t_doom *doom, int status)
{
	if (status == 0)
		draw_menu(doom);
	else if (status == 1)
	{
		//doom_clear_map(doom);
		draw_menu(doom);
	}
	else if (status == 2)
	{
		load_map_btns(doom);
		draw_menu(doom);
	}
	else if (status == 3)
		draw_menu(doom);
	doom->ui.m_status = status;
	return (status);
}

static void		on_menu_one(t_doom *doom, int x, int y)
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
				sdl_set_status(doom, 2);
			}
			else if (i == 2)
			{
				sdl_set_status(doom, 3);
			}
			else if (i == 3)
				start_editor(doom);
			else if (i == 4)
				doom_exit(doom);
		}
	}
}

static void		on_menu_two(t_doom *doom, int x, int y)
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
				sdl_set_status(doom, 1);
			}
			else if (i > 1)
			{
				//if (doom_parseur(doom, tmp.data))
				//{
				//	sdl_set_status(doom, 0);
				//}
			}
		}
	}
}

static void		on_menu_tree(t_doom *doom, int x, int y)
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
				sdl_set_status(doom, 1);
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

void			btn_click(t_doom *doom, int x, int y)
{
	if (doom->ui.m_status == 1)
		on_menu_one(doom, x, y);
	else if (doom->ui.m_status == 2)
		on_menu_two(doom, x, y);
	else if (doom->ui.m_status == 3)
		on_menu_tree(doom, x, y);
}
