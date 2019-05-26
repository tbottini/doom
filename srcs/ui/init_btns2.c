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
	SDL_Surface		*btntext;
	t_btn			tmp;
	SDL_Rect		rect;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.fgcolor = (SDL_Color){150, 150, 150, 0};
	tmp.bgcolor = (SDL_Color){255, 255, 255, 0};
	tmp.loc.pos.x = 50;
	tmp.loc.pos.y = 5;
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 3;
	btntext = TTF_RenderText_Shaded(doom->ui.fonts.s32, str,
		tmp.fgcolor, tmp.bgcolor);
	SDL_GetClipRect(btntext, &rect);
	tmp.loc.area.w = rect.w;
	tmp.loc.area.h = rect.h;
	tmp.txture = SDL_CreateTextureFromSurface(doom->sdl.rend, btntext);
	SDL_FreeSurface(btntext);
	return (tmp);
}

/*
** Map Menu button (Not really a button)
*/

t_btn	add_mapmenu_button(t_doom *doom)
{
	SDL_Surface		*btntext;
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.loc.pos.x = 50;
	tmp.loc.pos.y = 5;
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 0;
	tmp.fgcolor = (SDL_Color){255, 255, 255, 0};
	tmp.bgcolor = (SDL_Color){191, 35, 44, 0};
	btntext = TTF_RenderText_Shaded(doom->ui.fonts.s64, " Maps ",
		tmp.fgcolor, tmp.bgcolor);
	SDL_GetClipRect(btntext, &tmp.loc.area);
	tmp.txture = SDL_CreateTextureFromSurface(doom->sdl.rend, btntext);
	SDL_FreeSurface(btntext);
	return (tmp);
}

/*
** Editor button
*/

t_btn	add_editor_button(t_doom *doom)
{
	SDL_Surface		*btntext;
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = &open_editor;
	tmp.loc.pos.x = 50;
	tmp.loc.pos.y = 20;
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 3;
	tmp.fgcolor = (SDL_Color){150, 150, 150, 0};
	tmp.bgcolor = (SDL_Color){255, 255, 255, 0};
	btntext = TTF_RenderText_Shaded(doom->ui.fonts.s64, " Editor ",
		tmp.fgcolor, tmp.bgcolor);
	SDL_GetClipRect(btntext, &tmp.loc.area);
	tmp.txture = SDL_CreateTextureFromSurface(doom->sdl.rend, btntext);
	SDL_FreeSurface(btntext);
	return (tmp);
}
