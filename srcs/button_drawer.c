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

#include "doom.h"

static void	draw_buttons(t_doom *doom, int arr)
{
	int x;

	x = -1;
	SDL_RenderClear(doom->sdl.rend);
	if (arr == 1)
	{
		while (doom->ui.btnarr[++x].txture)
			SDL_RenderCopy(doom->sdl.rend, doom->ui.btnarr[x].txture,
					NULL, &(doom->ui.btnarr[x].loc.area));
	}
	else if (arr == 2)
	{
		while (doom->ui.btnmap[++x].txture)
			SDL_RenderCopy(doom->sdl.rend, doom->ui.btnmap[x].txture,
					NULL, &(doom->ui.btnmap[x].loc.area));
	}
	else if (arr == 3)
	{
		while (doom->ui.btnopt[++x].txture)
			SDL_RenderCopy(doom->sdl.rend, doom->ui.btnopt[x].txture,
					NULL, &(doom->ui.btnopt[x].loc.area));
	}
	SDL_RenderPresent(doom->sdl.rend);
}

static void	update_loc_buttons(t_doom *doom, t_btn *arr)
{
	t_sloc	tmp;
	int		x;
	int		y;

	x = -1;
	y = 0;
	ft_bzero(&tmp, sizeof(t_sloc));
	while (arr[++x].txture)
	{
		update_loc(doom, &(arr[x].loc), tmp);
		tmp = arr[x].loc;
	}
}

void		update_loc(t_doom *doom, t_sloc *loc, t_sloc before)
{
	loc->area.x = doom->sdl.size.x * (loc->pos.x / 100.0);
	loc->area.y = doom->sdl.size.y * (loc->pos.y / 100.0);
	if (loc->snapx == 1)
		loc->area.x -= loc->area.w / 2;
	else if (loc->snapx == 2)
		loc->area.x -= loc->area.w;
	else if (loc->snapx == 3)
		loc->area.x = before.pos.x + before.area.w + loc->pos.x;
	if (loc->snapy == 1)
		loc->area.y -= loc->area.h / 2;
	else if (loc->snapy == 2)
		loc->area.y -= loc->area.h;
	else if (loc->snapy == 3)
		loc->area.y = before.area.y + before.area.h + loc->pos.y;
}

void		draw_menu(t_doom *doom)
{
	int status;

	status = doom->ui.m_status;
	if (status == 1)
	{
		update_loc_buttons(doom, doom->ui.btnarr);
		draw_buttons(doom, status);
	}
	else if (status == 2)
	{
		update_loc_buttons(doom, doom->ui.btnmap);
		draw_buttons(doom, status);
	}
	else if (status == 3)
	{
		update_loc_buttons(doom, doom->ui.btnopt);
		draw_buttons(doom, status);
		draw_slid(doom, &doom->ui.slidopt[0]);
	}
}
