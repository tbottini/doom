/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 07:47:52 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 07:53:26 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	lil_editor_loop(t_doom *d, int key)
{
	if (d->edit.currstat && d->edit.currmur
	&& (ISWALLPROP(d->edit.currstat->type)))
	{
		if (key == SDLK_UP && d->edit.currstat->roty + 2.0 < 100.0)
			d->edit.currstat->roty += 2.0;
		else if (key == SDLK_DOWN && d->edit.currstat->roty - 2.0 > 0.0)
			d->edit.currstat->roty -= 2.0;
		d->edit.currstat->pos = line_percent(d->edit.currmur->pil1->pos,
		d->edit.currmur->pil2->pos, d->edit.currstat->roty / 100);
	}
	else
	{
		key == SDLK_UP && d->edit.sectscroll + 5 < 0
			? d->edit.sectscroll += 5 : 0;
		key == SDLK_DOWN ? d->edit.sectscroll -= 5 : 0;
	}
}

static void	editor_loop(t_doom *d, int key)
{
	if (key == SDLK_KP_PLUS || key == SDLK_KP_MINUS)
		scroll_limits(&d->edit.mappos.z, (key == SDLK_KP_PLUS ? 2 : -2)
		* (d->edit.mappos.z / 400 * ZOOMSPEED + 1), MINZOOM, MAXZOOM);
	else if (key == SDLK_KP_4 || key == SDLK_KP_6)
		d->edit.mappos.x += (key == SDLK_KP_4 ? 2 : -2);
	else if (key == SDLK_KP_8 || key == SDLK_KP_2)
		d->edit.mappos.y += (key == SDLK_KP_8 ? 2 : -2);
	else if (d->edit.selecttxtr != NOSELECT)
	{
		key == SDLK_UP && d->edit.txtrscroll + 5 < 0
			? d->edit.txtrscroll += 5 : 0;
		key == SDLK_DOWN ? d->edit.txtrscroll -= 5 : 0;
	}
	else
		lil_editor_loop(d, key);
}

void		editor_loop_hook(t_doom *doom)
{
	t_tab pos;

	pos = doom->edit.keys;
	while (pos)
	{
		editor_loop(doom, pos->data);
		pos = pos->next;
	}
	SDL_RenderClear(doom->edit.rend);
	draw_map(&doom->edit);
	draw_sector_menu(&doom->edit, doom->ui.fonts);
	if (doom->edit.map || doom->edit.currmur || doom->edit.currstat)
		draw_inspect_menu(&doom->edit);
	if (ISWRITING(doom->edit.status))
		draw_writer(&doom->edit);
	sdl_int_put((t_ip){doom->edit.rend, doom->ui.fonts.s32, (t_vct2){180, 10},
		"x: ", doom->edit.mapmouse.x, (SDL_Color){250, 50, 50, 255}});
	sdl_int_put((t_ip){doom->edit.rend, doom->ui.fonts.s32, (t_vct2){180, 40},
		"y: ", doom->edit.mapmouse.y, (SDL_Color){250, 50, 50, 255}});
	SDL_RenderPresent(doom->edit.rend);
}

void		outgame_loop_hook(t_doom *doom)
{
	if (doom->ui.m_status == MENU_IGMAIN
		|| doom->ui.m_status == MENU_IGOPTION)
		sdl_multirendercopy(&doom->sdl);
	else
	{
		fire(&doom->ui.fire);
		sdl_multirendercopy(&doom->sdl);
	}
	draw_menu(doom);
}
