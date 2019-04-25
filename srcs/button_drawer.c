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

#include "wolf3d.h"

static void	draw_buttons(t_wolf *wolf, int arr)
{
	int x;

	x = -1;
	SDL_RenderClear(wolf->sdl.rend);
	if (arr == 1)
	{
		while (wolf->ui.btnarr[++x].txture)
			SDL_RenderCopy(wolf->sdl.rend, wolf->ui.btnarr[x].txture,
					NULL, &(wolf->ui.btnarr[x].loc.area));
	}
	else if (arr == 2)
	{
		while (wolf->ui.btnmap[++x].txture)
			SDL_RenderCopy(wolf->sdl.rend, wolf->ui.btnmap[x].txture,
					NULL, &(wolf->ui.btnmap[x].loc.area));
	}
	else if (arr == 3)
	{
		while (wolf->ui.btnopt[++x].txture)
			SDL_RenderCopy(wolf->sdl.rend, wolf->ui.btnopt[x].txture,
					NULL, &(wolf->ui.btnopt[x].loc.area));
	}
	SDL_RenderPresent(wolf->sdl.rend);
}

static void	update_loc_buttons(t_wolf *wolf, t_btn *arr)
{
	t_btn	*tmp;
	int		x;
	int		y;

	x = -1;
	y = 0;
	while (arr[++x].txture)
	{
		tmp = &(arr[x]);
		arr[x].loc.area.x = wolf->sdl.size.x * (tmp->loc.pos.x / 100.0);
		arr[x].loc.area.y = wolf->sdl.size.y * (tmp->loc.pos.y / 100.0);
		if (tmp->loc.snapx == 1)
			arr[x].loc.area.x -= tmp->loc.area.w / 2;
		else if (tmp->loc.snapx == 2)
			arr[x].loc.area.x -= tmp->loc.area.w;
		else if (tmp->loc.snapx == 3)
			arr[x].loc.area.x = x + tmp->loc.pos.x;
		if (tmp->loc.snapy == 1)
			arr[x].loc.area.y -= tmp->loc.area.h / 2;
		else if (tmp->loc.snapy == 2)
			arr[x].loc.area.y -= tmp->loc.area.h;
		else if (tmp->loc.snapy == 3)
			arr[x].loc.area.y = y + tmp->loc.pos.y;
		y = tmp->loc.area.y + tmp->loc.area.h;
	}
}

static void	update_loc(t_wolf *wolf, t_sloc *loc, t_sloc *before)
{
	loc->area.x = wolf->sdl.size.x * (loc->pos.x / 100.0);
	loc->area.y = wolf->sdl.size.y * (loc->pos.y / 100.0);
	if (loc->snapx == 1)
		loc->area.x -= loc->area.w / 2;
	else if (loc->snapx == 2)
		loc->area.x -= loc->area.w;
	else if (loc->snapx == 3)
		loc->area.x = before->pos.x + before->area.w + loc->pos.x;
	if (loc->snapy == 1)
		loc->area.y -= loc->area.h / 2;
	else if (loc->snapy == 2)
		loc->area.y -= loc->area.h;
	else if (loc->snapy == 3)
		loc->area.y = before->area.y + before->area.h + loc->pos.y;
}

void		draw_slid(t_wolf *wolf, t_slid *tmp)
{
	int size;

	size = tmp->loc.area.h;
	update_loc(wolf, &tmp->loc, &(wolf->ui.btnopt[1].loc));
	update_slider_txt(wolf, tmp);
	tmp->grip.x = tmp->loc.area.x + ((tmp->loc.area.w - size)
		* (*tmp->val - tmp->min)) / (tmp->max - tmp->min);
	tmp->grip.y = tmp->loc.area.y;
	SDL_RenderFillRect(wolf->sdl.rend, &tmp->loc.area);
	SDL_SetRenderDrawColor(wolf->sdl.rend, 191, 35, 54, 255);
	SDL_RenderDrawRect(wolf->sdl.rend, &tmp->loc.area);
	SDL_SetRenderDrawColor(wolf->sdl.rend, 0, 0, 0, 255);
	SDL_RenderCopy(wolf->sdl.rend, tmp->txture, NULL, &tmp->grip);
	SDL_RenderPresent(wolf->sdl.rend);
}

void		draw_menu(t_wolf *wolf)
{
	int status;

	status = wolf->ui.m_status;
	if (status == 1)
	{
		update_loc_buttons(wolf, wolf->ui.btnarr);
		draw_buttons(wolf, status);
	}
	else if (status == 2)
	{
		update_loc_buttons(wolf, wolf->ui.btnmap);
		draw_buttons(wolf, status);
	}
	else if (status == 3)
	{
		update_loc_buttons(wolf, wolf->ui.btnopt);
		draw_buttons(wolf, status);
		draw_slid(wolf, &wolf->ui.slidopt[0]);
	}
}
