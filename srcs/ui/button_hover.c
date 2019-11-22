/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_hover.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:19:51 by magrab            #+#    #+#             */
/*   Updated: 2019/05/05 09:21:21 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static t_btn	*on_menu(t_btn *btnarr, int x, int y)
{
	t_btn	tmp;
	int		i;

	i = -1;
	while (btnarr[++i].txture)
	{
		tmp = btnarr[i];
		if (tmp.loc.area.x <= x && x <= tmp.loc.area.x + tmp.loc.area.w
			&& tmp.loc.area.y <= y && y <= tmp.loc.area.y + tmp.loc.area.h)
		{
			return (&(btnarr[i]));
		}
	}
	return (NULL);
}

t_btn			*btn_hover(t_doom *doom, int x, int y)
{
	if (doom->ui.m_status == MENU_MAIN)
		return (on_menu(doom->ui.btnarr, x, y));
	else if (doom->ui.m_status == MENU_MAP)
		return (on_menu(doom->ui.btnmap, x, y));
	else if (doom->ui.m_status == MENU_OPTION
			|| doom->ui.m_status == MENU_IGOPTION)
		return (on_menu(doom->ui.btnopt, x, y));
	else if (doom->ui.m_status == MENU_IGMAIN)
		return (on_menu(doom->ui.btnpse, x, y));
	return (NULL);
}

void			draw_hover(t_doom *doom, t_btn *new, t_btn *old)
{
	SDL_Rect rect;

	if (old)
	{
		rect = old->loc.area;
		rect.x -= 3;
		rect.y -= 3;
		rect.w += 6;
		rect.h += 6;
		SDL_RenderDrawRect(doom->sdl.rend, &rect);
	}
	if (new)
	{
		rect = new->loc.area;
		rect.x -= 3;
		rect.y -= 3;
		rect.w += 6;
		rect.h += 6;
		SDL_SetRenderDrawColor(doom->sdl.rend, 255, 255, 255, 255);
		SDL_RenderCopy(doom->sdl.rend, new->txture, NULL, &(rect));
		SDL_SetRenderDrawColor(doom->sdl.rend, 0, 0, 0, 255);
	}
}
