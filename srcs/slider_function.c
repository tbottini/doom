/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 22:35:15 by magrab            #+#    #+#             */
/*   Updated: 2019/05/07 22:35:16 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void update_slider_txt(t_doom *doom, t_slid *slid)
{
	SDL_Surface *btntext;
	char *str;

	str = ft_itoa(*slid->val);
	btntext = TTF_RenderText_Shaded(doom->ui.fonts.s32, str,
									slid->fgcolor, slid->bgcolor);
	slid->txture = SDL_CreateTextureFromSurface(doom->sdl.rend, btntext);
	SDL_FreeSurface(btntext);
	free(str);
}

void update_slider_value(t_doom *doom, t_slid *slid, int value)
{
	value = (((value - slid->loc.area.x) / (double)slid->loc.area.w
								* (slid->max - slid->min)) + slid->min);
	if (slid->min <= value && value <= slid->max && *slid->val != value)
	{
		*slid->val = value;
		update_slider_txt(doom, slid);
		//draw_slid(doom, slid); //Deactivate because menu is now rendered everyframe
	}
}

void		draw_slid(t_doom *doom, t_slid *tmp)
{
	int size;

	size = tmp->loc.area.h;
	update_loc(doom, &tmp->loc, *tmp->loc.parent);
	update_slider_txt(doom, tmp);
	tmp->grip.x = tmp->loc.area.x + ((tmp->loc.area.w - size)
		* (*tmp->val - tmp->min)) / (tmp->max - tmp->min);
	tmp->grip.y = tmp->loc.area.y;
	SDL_RenderFillRect(doom->sdl.rend, &tmp->loc.area);
	SDL_SetRenderDrawColor(doom->sdl.rend, 191, 35, 54, 255);
	SDL_RenderDrawRect(doom->sdl.rend, &tmp->loc.area);
	SDL_SetRenderDrawColor(doom->sdl.rend, 0, 0, 0, 255);
	SDL_RenderCopy(doom->sdl.rend, tmp->txture, NULL, &tmp->grip);
}
