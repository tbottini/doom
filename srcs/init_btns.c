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

t_btn add_start_button(t_wolf *wolf, int pos)
{
	t_btn tmp;
	SDL_Surface *btntext;

	tmp.pos.x = 50;
	tmp.pos.y = 40;
	tmp.snapx = 1;
	tmp.snapy = 1;
	tmp.fgcolor.r = 191;
	tmp.fgcolor.g = 35;
	tmp.fgcolor.b = 44;
	tmp.bgcolor.r = 255;
	tmp.bgcolor.g = 255;
	tmp.bgcolor.b = 255;
	tmp.area.x = 50;
	tmp.area.y = 20;
	tmp.area.w = 200;
	tmp.area.h = 150;
	btntext = TTF_RenderText_Shaded(wolf->sdl.font, "START", tmp.fgcolor, tmp.bgcolor);
	tmp.txture = SDL_CreateTextureFromSurface(wolf->sdl.rend, btntext);
	SDL_FreeSurface(btntext);
	wolf->sdl.btnarr[pos] = tmp;
	return (tmp);
}

t_btn add_wolf_button(t_wolf *wolf, int pos)
{
	t_btn tmp;
	SDL_Surface *btntext;

	tmp.pos.x = 50;
	tmp.pos.y = 0;
	tmp.snapx = 1;
	tmp.snapy = 0;
	tmp.fgcolor.r = 191;
	tmp.fgcolor.g = 35;
	tmp.fgcolor.b = 44;
	tmp.bgcolor.r = 255;
	tmp.bgcolor.g = 255;
	tmp.bgcolor.b = 255;
	tmp.area.w = 300;
	tmp.area.h = 150;
	btntext = TTF_RenderText_Shaded(wolf->sdl.font, "wolfenstein", tmp.fgcolor, tmp.bgcolor);
	tmp.txture = SDL_CreateTextureFromSurface(wolf->sdl.rend, btntext);
	SDL_FreeSurface(btntext);
	wolf->sdl.btnarr[pos] = tmp;
	return (tmp);
}

t_btn add_opt_button(t_wolf *wolf, int pos)
{
	t_btn tmp;
	SDL_Surface *btntext;

	tmp.pos.x = 50;
	tmp.pos.y = 60;
	tmp.snapx = 1;
	tmp.snapy = 1;
	tmp.fgcolor.r = 191;
	tmp.fgcolor.g = 35;
	tmp.fgcolor.b = 44;
	tmp.bgcolor.r = 255;
	tmp.bgcolor.g = 255;
	tmp.bgcolor.b = 255;
	tmp.area.w = 100;
	tmp.area.h = 75;
	btntext = TTF_RenderText_Shaded(wolf->sdl.font, "Options?", tmp.fgcolor, tmp.bgcolor);
	tmp.txture = SDL_CreateTextureFromSurface(wolf->sdl.rend, btntext);
	SDL_FreeSurface(btntext);
	wolf->sdl.btnarr[pos] = tmp;
	return (tmp);
}

t_btn add_quit_button(t_wolf *wolf, int pos)
{
	t_btn tmp;
	SDL_Surface *btntext;

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
	tmp.area.w = 100;
	tmp.area.h = 75;
	btntext = TTF_RenderText_Shaded(wolf->sdl.font, "Quit", tmp.fgcolor, tmp.bgcolor);
	tmp.txture = SDL_CreateTextureFromSurface(wolf->sdl.rend, btntext);
	SDL_FreeSurface(btntext);
	wolf->sdl.btnarr[pos] = tmp;
	return (tmp);
}
