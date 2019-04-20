/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:19:51 by magrab            #+#    #+#             */
/*   Updated: 2019/04/19 18:19:52 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void start_btn(t_wolf *wolf)
{
	wolf->sdl.m_status = 2;
	load_map_btns(wolf);
	draw_menu(wolf);
}

void btn_click(t_wolf *wolf, int x, int y)
{
	int i;
	t_btn tmp;

	i = -1;
	if (wolf->sdl.m_status == 1)
	{
		while (wolf->sdl.btnarr[++i].txture)
		{
			tmp = wolf->sdl.btnarr[i];
			if (tmp.area.x <= x && x <= tmp.area.x + tmp.area.w && tmp.area.y <= y && y <= tmp.area.y + tmp.area.h)
			{
				ft_printf("Click on btn %d\n", i);
				if (i == 1)
				{
					start_btn(wolf);
				}
				else if (i == 3)
					prog_quit(wolf);
			}
		}
	}
	else if (wolf->sdl.m_status == 2)
	{
		while (wolf->sdl.btnmap[++i].txture)
		{
			//ft_printf("LoadBTN\n");
			tmp = wolf->sdl.btnmap[i];
			if (tmp.area.x <= x && x <= tmp.area.x + tmp.area.w && tmp.area.y <= y && y <= tmp.area.y + tmp.area.h)
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
				/*	if (i == 1)
					start_btn(wolf);
				else if (i == 3)
					prog_quit(wolf);
			*/
			}
		}
	}
}
