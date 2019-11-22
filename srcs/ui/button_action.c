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

static void		use_slider(t_doom *doom, int x, int y)
{
	t_slid	stmp;
	int		i;

	i = 0;
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
	if (doom->ui.m_status == MENU_OPTION || doom->ui.m_status == MENU_IGOPTION)
		use_slider(doom, x, y);
}
