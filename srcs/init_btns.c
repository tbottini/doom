/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_btns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/04/16 00:18:29 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_btn add_wolf_button(t_wolf *wolf)
{
	t_btn tmp;
	SDL_Surface *btntext;
	SDL_Rect rect;

	tmp.pos.x = 50;
	tmp.pos.y = 5;
	tmp.snapx = 1;
	tmp.snapy = 0;
	tmp.bgcolor.r = 191;
	tmp.bgcolor.g = 35;
	tmp.bgcolor.b = 44;
	tmp.fgcolor.r = 255;
	tmp.fgcolor.g = 255;
	tmp.fgcolor.b = 255;
	btntext = TTF_RenderText_Shaded(wolf->sdl.font128, " wolfenstein ", tmp.fgcolor, tmp.bgcolor);
	SDL_GetClipRect(btntext, &rect);
	tmp.area.w = rect.w;
	tmp.area.h = rect.h;
	tmp.txture = SDL_CreateTextureFromSurface(wolf->sdl.rend, btntext);
	SDL_FreeSurface(btntext);
	return (tmp);
}

t_btn add_mapmenu_button(t_wolf *wolf)
{
	t_btn tmp;
	SDL_Surface *btntext;
	SDL_Rect rect;

	tmp.pos.x = 50;
	tmp.pos.y = 5;
	tmp.snapx = 1;
	tmp.snapy = 0;
	tmp.bgcolor.r = 191;
	tmp.bgcolor.g = 35;
	tmp.bgcolor.b = 44;
	tmp.fgcolor.r = 255;
	tmp.fgcolor.g = 255;
	tmp.fgcolor.b = 255;
	btntext = TTF_RenderText_Shaded(wolf->sdl.font, " Maps ", tmp.fgcolor, tmp.bgcolor);
	SDL_GetClipRect(btntext, &rect);
	tmp.area.w = rect.w;
	tmp.area.h = rect.h;
	tmp.txture = SDL_CreateTextureFromSurface(wolf->sdl.rend, btntext);
	SDL_FreeSurface(btntext);
	return (tmp);
}

t_btn add_start_button(t_wolf *wolf)
{
	t_btn tmp;
	SDL_Surface *btntext;
	SDL_Rect rect;

	tmp.pos.x = 50;
	tmp.snapx = 1;
	tmp.snapy = 3;
	tmp.fgcolor.r = 150;
	tmp.fgcolor.g = 150;
	tmp.fgcolor.b = 150;
	tmp.bgcolor.r = 255;
	tmp.bgcolor.g = 255;
	tmp.bgcolor.b = 255;
	btntext = TTF_RenderText_Shaded(wolf->sdl.font, " START ", tmp.fgcolor, tmp.bgcolor);
	SDL_GetClipRect(btntext, &rect);
	tmp.area.w = rect.w;
	tmp.area.h = rect.h;
	tmp.txture = SDL_CreateTextureFromSurface(wolf->sdl.rend, btntext);
	SDL_FreeSurface(btntext);
	return (tmp);
}

t_btn add_opt_button(t_wolf *wolf)
{
	t_btn tmp;
	SDL_Surface *btntext;
	SDL_Rect rect;

	tmp.pos.x = 50;
	tmp.pos.y = 20;
	tmp.snapx = 1;
	tmp.snapy = 3;
	tmp.fgcolor.r = 150;
	tmp.fgcolor.g = 150;
	tmp.fgcolor.b = 150;
	tmp.bgcolor.r = 255;
	tmp.bgcolor.g = 255;
	tmp.bgcolor.b = 255;
	btntext = TTF_RenderText_Shaded(wolf->sdl.font, " Options? ", tmp.fgcolor, tmp.bgcolor);
	SDL_GetClipRect(btntext, &rect);
	tmp.area.w = rect.w;
	tmp.area.h = rect.h;
	tmp.txture = SDL_CreateTextureFromSurface(wolf->sdl.rend, btntext);
	SDL_FreeSurface(btntext);
	return (tmp);
}

t_btn add_quit_button(t_wolf *wolf)
{
	t_btn tmp;
	SDL_Surface *btntext;
	SDL_Rect rect;

	tmp.pos.x = 95;
	tmp.pos.y = 95;
	tmp.snapx = 2;
	tmp.snapy = 2;
	tmp.fgcolor.r = 191;
	tmp.fgcolor.g = 35;
	tmp.fgcolor.b = 44;
	tmp.bgcolor.r = 255;
	tmp.bgcolor.g = 255;
	tmp.bgcolor.b = 255;
	btntext = TTF_RenderText_Shaded(wolf->sdl.font, " Quit ", tmp.fgcolor, tmp.bgcolor);
	SDL_GetClipRect(btntext, &rect);
	tmp.area.w = rect.w;
	tmp.area.h = rect.h;
	tmp.txture = SDL_CreateTextureFromSurface(wolf->sdl.rend, btntext);
	SDL_FreeSurface(btntext);
	return (tmp);
}
