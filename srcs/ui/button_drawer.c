/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_drawer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:29:18 by magrab            #+#    #+#             */
/*   Updated: 2019/07/19 11:43:06 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	update_loc_buttons(t_vct2 size, t_btn *arr)
{
	t_sloc	tmp;
	int		x;
	int		y;

	x = -1;
	y = 0;
	ft_bzero(&tmp, sizeof(t_sloc));
	while (arr[++x].txture)
	{
		if (arr[x].loc.parent)
			update_loc(size, &(arr[x].loc), *(arr[x].loc.parent));
		else
			update_loc(size, &(arr[x].loc), tmp.area);
		tmp = arr[x].loc;
	}
}

static void	draw_buttons(t_doom *doom, t_btn *btnarr)
{
	int x;

	update_loc_buttons(doom->sdl.size, btnarr);
	x = -1;
	while (btnarr[++x].txture)
		SDL_RenderCopy(doom->sdl.rend, btnarr[x].txture,
			NULL, &(btnarr[x].loc.area));
}

void		update_loc(t_vct2 size, t_sloc *loc, SDL_Rect before)
{
	loc->area.x = (int)(size.x * (loc->pos.x / 100.0));
	loc->area.y = (int)(size.y * (loc->pos.y / 100.0));
	if (loc->snapx == 1)
		loc->area.x -= loc->area.w / 2;
	else if (loc->snapx == 2)
		loc->area.x -= loc->area.w;
	else if (loc->snapx == 3)
		loc->area.x = before.x + before.w + loc->pos.x;
	else if (loc->snapx == 4)
		loc->area.x = before.x + loc->pos.x;
	else if (loc->snapx == 5)
		loc->area.x = before.x - loc->area.w - loc->pos.x;
	if (loc->snapy == 1)
		loc->area.y -= loc->area.h / 2;
	else if (loc->snapy == 2)
		loc->area.y -= loc->area.h;
	else if (loc->snapy == 3)
		loc->area.y = before.y + before.h + loc->pos.y;
	else if (loc->snapy == 4)
		loc->area.y = before.y + loc->pos.y;
	else if (loc->snapy == 5)
		loc->area.y = before.y - loc->area.h - loc->pos.y;
}

void		draw_difficulty(t_doom *doom, t_btn *arr)
{
	SDL_Rect tmp;

	if (doom->game.difficulty == EASY)
		tmp = arr[3].loc.area;
	else if (doom->game.difficulty == MEDIUM)
		tmp = arr[2].loc.area;
	else if (doom->game.difficulty == HARD)
		tmp = arr[4].loc.area;
	tmp.x -= 5;
	tmp.y -= 5;
	tmp.w += 10;
	tmp.h += 10;
	SDL_SetRenderDrawColor(doom->sdl.rend, 255, 255, 255, 255);
	SDL_RenderDrawRect(doom->sdl.rend, &tmp);
	tmp.x -= 1;
	tmp.y -= 1;
	tmp.w += 2;
	tmp.h += 2;
	SDL_RenderDrawRect(doom->sdl.rend, &tmp);
	SDL_SetRenderDrawColor(doom->sdl.rend, 0, 0, 0, 255);
}

void		draw_menu(t_doom *doom)
{
	if (doom->ui.m_status == MENU_MAIN)
	{
		draw_buttons(doom, doom->ui.btnarr);
	}
	else if (doom->ui.m_status == MENU_MAP)
	{
		draw_buttons(doom, doom->ui.btnmap);
	}
	else if (doom->ui.m_status == MENU_OPTION || doom->ui.m_status == 5)
	{
		draw_buttons(doom, doom->ui.btnopt);
		draw_difficulty(doom, doom->ui.btnopt);
		draw_slid(doom, &doom->ui.slidopt[0]);
		draw_slid(doom, &doom->ui.slidopt[1]);
		draw_slid(doom, &doom->ui.slidopt[2]);
	}
	else if (doom->ui.m_status == MENU_IGMAIN)
	{
		draw_buttons(doom, doom->ui.btnpse);
	}
	if (doom->ui.curr_btn
				&& (doom->ui.curr_btn->func || doom->ui.curr_btn->data))
		draw_hover(doom, doom->ui.curr_btn, NULL);
}
