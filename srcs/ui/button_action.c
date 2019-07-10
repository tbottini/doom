/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:19:51 by magrab            #+#    #+#             */
/*   Updated: 2019/07/10 15:10:28 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
/*
static void		map_btn_click(t_doom *doom, int x, int y)
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
			if (i > 1)
			{
				if (parsing(doom, tmp.data))
					sdl_set_status(doom, 0);
				else
					ft_printf("Error reading file\n");
			}
		}
	}
}
*/
static void		use_slider(t_doom *doom, int x, int y)
{
	t_slid	stmp;
	int		i;

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
	/*
	if (doom->ui.m_status == 2)
		map_btn_click(doom, x, y);
	else */if (doom->ui.m_status == 3 || doom->ui.m_status == 5)
		use_slider(doom, x, y);
}
