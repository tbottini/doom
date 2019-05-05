/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_slids.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/05/04 21:55:59 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		update_slider_txt(t_doom *doom, t_slid *slid)
{
	SDL_Surface		*btntext;
	char			*str;

	str = ft_itoa(*slid->val);
	btntext = TTF_RenderText_Shaded(doom->ui.fonts.s32, str,
		slid->fgcolor, slid->bgcolor);
	slid->txture = SDL_CreateTextureFromSurface(doom->sdl.rend, btntext);
	SDL_FreeSurface(btntext);
	free(str);
}

t_slid		add_fov_slider(t_doom *doom)
{
	t_slid			tmp;

	tmp.txture = SDL_CreateTexture(doom->sdl.rend,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 200);
	tmp.loc.area.w = 500;
	tmp.loc.area.h = 50;
	tmp.loc.area.x = 0;
	tmp.loc.area.y = 0;
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 3;
	tmp.loc.pos.x = 50;
	tmp.loc.pos.y = 20;
	tmp.bgcolor.r = 191;
	tmp.bgcolor.g = 35;
	tmp.bgcolor.b = 44;
	tmp.fgcolor.r = 255;
	tmp.fgcolor.g = 255;
	tmp.fgcolor.b = 255;
	tmp.grip.w = tmp.loc.area.h;
	tmp.grip.h = tmp.loc.area.h;
	tmp.min = 30;
	tmp.val = &doom->player.fov;
	tmp.max = 175;
	update_slider_txt(doom, &tmp);
	return (tmp);
}
