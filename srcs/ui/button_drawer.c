/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_drawer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:29:18 by magrab            #+#    #+#             */
/*   Updated: 2019/04/19 17:29:19 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	draw_buttons(t_doom *doom, t_btn *btnarr)
{
	int x;

	x = -1;
	while (btnarr[++x].txture)
		SDL_RenderCopy(doom->sdl.rend, btnarr[x].txture,
			NULL, &(btnarr[x].loc.area));
}

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

void		draw_menu(t_doom *doom)
{
	int status;

	status = doom->ui.m_status;
	if (status == 1)
	{
		update_loc_buttons(doom->sdl.size, doom->ui.btnarr);
		draw_buttons(doom, doom->ui.btnarr);
		if (doom->ui.curr_btn_controller > 0 && doom->ui.btnarr[doom->ui.curr_btn_controller - 1].func)
			doom->ui.curr_btn = &(doom->ui.btnarr[doom->ui.curr_btn_controller - 1]);
	}
	else if (status == 2)
	{
		update_loc_buttons(doom->sdl.size, doom->ui.btnmap);
		draw_buttons(doom, doom->ui.btnmap);
		if (doom->ui.curr_btn_controller > 0 && doom->ui.btnmap[doom->ui.curr_btn_controller - 1].txture)
			doom->ui.curr_btn = &(doom->ui.btnmap[doom->ui.curr_btn_controller - 1]);
	}
	else if (status == 3 || status == 5)
	{
		update_loc_buttons(doom->sdl.size, doom->ui.btnopt);
		draw_buttons(doom, doom->ui.btnopt);
		draw_slid(doom, &doom->ui.slidopt[0]);
		draw_slid(doom, &doom->ui.slidopt[1]);
		draw_slid(doom, &doom->ui.slidopt[2]);
		if (doom->ui.curr_btn_controller > 0 && doom->ui.btnopt[doom->ui.curr_btn_controller - 1].func)
			doom->ui.curr_btn = &(doom->ui.btnopt[doom->ui.curr_btn_controller - 1]);
	}
	else if (status == 4)
	{
		update_loc_buttons(doom->sdl.size, doom->ui.btnpse);
		draw_buttons(doom, doom->ui.btnpse);
	}
	if (doom->ui.curr_btn)
	{
		if (((doom->ui.curr_btn->func || doom->ui.curr_btn->data)))
			draw_hover(doom, doom->ui.curr_btn, NULL);
	}
}
