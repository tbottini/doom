/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_btns2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/04/16 00:18:29 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Button for all maps
*/

t_btn	add_map_button(t_doom *doom, const char *str)
{
	t_btn			tmp;
	SDL_Rect		rect;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = &start_map_button;
	tmp.fgcolor = (SDL_Color){150, 150, 150, 0};
	tmp.bgcolor = (SDL_Color){255, 255, 255, 0};
	tmp.loc.pos.x = 50;
	tmp.loc.pos.y = 5;
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 3;
	updatetext((t_updatetext){doom->sdl.rend, doom->ui.fonts.s32, &tmp.txture,
	&rect, str, tmp.fgcolor, tmp.bgcolor});
	tmp.loc.area.w = rect.w;
	tmp.loc.area.h = rect.h;
	return (tmp);
}

/*
** Map Menu button (Not really a button)
*/

t_btn	add_mapmenu_button(t_doom *doom)
{
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.loc.pos.x = 50;
	tmp.loc.pos.y = 5;
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 0;
	tmp.fgcolor = (SDL_Color){255, 255, 255, 0};
	tmp.bgcolor = (SDL_Color){191, 35, 44, 0};
	updatetext((t_updatetext){doom->sdl.rend, doom->ui.fonts.s64, &tmp.txture,
	&tmp.loc.area, " Maps ", tmp.fgcolor, tmp.bgcolor});
	return (tmp);
}

/*
** Editor button
*/

t_btn	add_editor_button(t_doom *doom)
{
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = &open_editor;
	tmp.loc.pos.x = 50;
	tmp.loc.pos.y = 20;
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 3;
	tmp.fgcolor = (SDL_Color){150, 150, 150, 0};
	tmp.bgcolor = (SDL_Color){255, 255, 255, 0};
	updatetext((t_updatetext){doom->sdl.rend, doom->ui.fonts.s64, &tmp.txture,
	&tmp.loc.area, " Editor ", tmp.fgcolor, tmp.bgcolor});
	return (tmp);
}
