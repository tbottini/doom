/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 08:12:34 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 08:12:35 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "render.h"

void	sdl_free(t_sdl *sdl)
{
	if (sdl->txture)
		SDL_DestroyTexture(sdl->txture);
	if (sdl->rend)
		SDL_DestroyRenderer(sdl->rend);
	if (sdl->win)
		SDL_DestroyWindow(sdl->win);
}

int		sdl_set_status(t_doom *doom, t_menu_status status)
{
	SDL_SetRelativeMouseMode(SDL_FALSE);
	ft_nodeclean(&doom->sdl.keys);
	doom->ui.curr_btn = NULL;
	if (status == MENU_INGAME) // gamemode
	{
		doom->ui.m_status = MENU_INGAME;
		SDL_SetRelativeMouseMode(SDL_TRUE);
		draw_menu(doom);
	}
	else if (status == MENU_MAIN) // mainmenu
	{
		doom->ui.m_status = MENU_MAIN;
		doom->ui.curr_btn_controller = -2;
		//doom_clear_map(doom); // TODO Add map data free;
		fire_on_off(doom->sdl.screen, doom->sdl.size, 1);
		draw_menu(doom);
	}
	else if (status == MENU_MAP) // Map selection
	{
		doom->ui.m_status = MENU_MAP;
		doom->ui.curr_btn_controller = -3;
		doom->ui.btnmap[1].loc.pos.y = 5;
		load_map_btns(doom);
		draw_menu(doom);
	}
	else if (status == MENU_OPTION) // Options
	{
		doom->ui.m_status = MENU_OPTION;
		doom->ui.curr_btn_controller = -1;
		draw_menu(doom);
	}
	else if (status == MENU_IGMAIN) // Pause menu
	{
		doom->ui.m_status = MENU_IGMAIN;
		doom->ui.curr_btn_controller = -1;
	}
	else if (status == MENU_IGOPTION) // Options from pause menu
	{
		doom->ui.m_status = MENU_IGOPTION;
		doom->ui.curr_btn_controller = -1;
		draw_menu(doom);
	}
	return (status);
}

int		sdl_init(t_sdl *sdl, const char *title)
{
	void	*tmp;
	int		pitch;

	sdl->size.x = WIDTH;
	sdl->size.y = HEIGHT;
	if (!(sdl->win = SDL_CreateWindow(title, 0, 0, WIDTH, HEIGHT, 32)))
		return (0);
	if (!(sdl->rend = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_SOFTWARE)))
		return (0);
	SDL_SetWindowMinimumSize(sdl->win, MINWIDTH, MINHEIGHT);
	//SDL_SetWindowMaximumSize(sdl->win, MAXWIDTH, MAXHEIGHT);
	sdl->txture = SDL_CreateTexture(sdl->rend,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	if (SDL_LockTexture(sdl->txture, NULL, &tmp, &pitch))
		return (0);
	sdl->screen = (Uint32*)tmp;
	return (1);
}
