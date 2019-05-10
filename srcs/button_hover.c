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

#include "doom.h"

static t_btn	*on_menu_one(t_doom *doom, int x, int y)
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
			return (&(doom->ui.btnarr[i]));
		}
	}
	return (NULL);
}

static t_btn	*on_menu_two(t_doom *doom, int x, int y)
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
			return (&(doom->ui.btnmap[i]));
		}
	}
	return (NULL);
}

static t_btn	*on_menu_tree(t_doom *doom, int x, int y)
{
	t_btn	tmp;
	int		i;

	i = -1;
	while (doom->ui.btnopt[++i].txture)
	{
		tmp = doom->ui.btnopt[i];
		if (tmp.loc.area.x <= x && x <= tmp.loc.area.x + tmp.loc.area.w
			&& tmp.loc.area.y <= y && y <= tmp.loc.area.y + tmp.loc.area.h)
		{
			return (&(doom->ui.btnopt[i]));
		}
	}
	return (NULL);
}

t_btn		*btn_hover(t_doom *doom, int x, int y)
{
	if (doom->ui.m_status == 1)
		return (on_menu_one(doom, x, y));
	else if (doom->ui.m_status == 2)
		return(on_menu_two(doom, x, y));
	else if (doom->ui.m_status == 3)
		return(on_menu_tree(doom, x, y));
	return(NULL);
}

void		draw_hover(t_doom *doom, t_btn *new, t_btn *old)
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
		SDL_RenderDrawRect(doom->sdl.rend, &rect);
		SDL_SetRenderDrawColor(doom->sdl.rend, 0, 0, 0, 255);
	}
	SDL_RenderPresent(doom->sdl.rend);
}
