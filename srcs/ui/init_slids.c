/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_slids.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/07/10 14:18:56 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_slid		add_fov_slider(t_doom *doom)
{
	SDL_Surface		*slidtext;
	t_slid			tmp;

	tmp.bgcolor = (SDL_Color){191, 35, 44, 255};
	tmp.fgcolor = (SDL_Color){255, 255, 255, 255};
	tmp.txture = SDL_CreateTexture(doom->sdl.rend,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 200);
	slidtext = TTF_RenderText_Solid(doom->ui.fonts.s32, " FOVNITE",
		tmp.fgcolor);
	SDL_GetClipRect(slidtext, &tmp.griplabel);
	tmp.label = SDL_CreateTextureFromSurface(doom->sdl.rend, slidtext);
	SDL_FreeSurface(slidtext);
	tmp.loc.area = (SDL_Rect){0, 0, 500, 40};
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 3;
	tmp.loc.pos = (t_vct2){50, 20};
	tmp.grip.w = tmp.loc.area.h;
	tmp.grip.h = tmp.loc.area.h;
	tmp.min = 30;
	tmp.val = &doom->game.player.fov;
	tmp.max = 110;
	update_slider_txt(doom, &tmp);
	return (tmp);
}

t_slid		add_music_slider(t_doom *doom)
{
	SDL_Surface		*slidtext;
	t_slid			tmp;

	tmp.bgcolor = (SDL_Color){191, 35, 44, 255};
	tmp.fgcolor = (SDL_Color){255, 255, 255, 255};
	tmp.txture = SDL_CreateTexture(doom->sdl.rend,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 200);
	slidtext = TTF_RenderText_Solid(doom->ui.fonts.s32, " Music Volume",
		tmp.fgcolor);
	SDL_GetClipRect(slidtext, &tmp.griplabel);
	tmp.label = SDL_CreateTextureFromSurface(doom->sdl.rend, slidtext);
	SDL_FreeSurface(slidtext);
	tmp.loc.area = (SDL_Rect){0, 0, 600, 40};
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 3;
	tmp.loc.pos = (t_vct2){50, 20};
	tmp.grip.w = tmp.loc.area.h;
	tmp.grip.h = tmp.loc.area.h;
	tmp.min = 0;
	tmp.val = &doom->game.sound.musicvolume;
	tmp.max = 128;
	update_slider_txt(doom, &tmp);
	return (tmp);
}

t_slid		add_effect_slider(t_doom *doom)
{
	SDL_Surface		*slidtext;
	t_slid			tmp;

	tmp.bgcolor = (SDL_Color){191, 35, 44, 255};
	tmp.fgcolor = (SDL_Color){255, 255, 255, 255};
	tmp.txture = SDL_CreateTexture(doom->sdl.rend,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 200);
	slidtext = TTF_RenderText_Solid(doom->ui.fonts.s32, " Effects Volume",
		tmp.fgcolor);
	SDL_GetClipRect(slidtext, &tmp.griplabel);
	tmp.label = SDL_CreateTextureFromSurface(doom->sdl.rend, slidtext);
	SDL_FreeSurface(slidtext);
	tmp.loc.area = (SDL_Rect){0, 0, 600, 40};
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 3;
	tmp.loc.pos = (t_vct2){50, 20};
	tmp.grip.w = tmp.loc.area.h;
	tmp.grip.h = tmp.loc.area.h;
	tmp.min = 0;
	tmp.val = &doom->game.sound.effectvolume;
	tmp.max = 128;
	update_slider_txt(doom, &tmp);
	return (tmp);
}
