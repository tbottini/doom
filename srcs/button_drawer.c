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

static void		draw_buttons(t_wolf *wolf, int arr)
{
	int x;

	x = -1;
	SDL_RenderClear(wolf->sdl.rend);
	if (arr == 1)
	{
		while (wolf->sdl.btnarr[++x].txture)
		{
			SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.btnarr[x].txture,
					NULL, &(wolf->sdl.btnarr[x].loc.area));
		}
	}
	else if (arr == 2)
	{
		while (wolf->sdl.btnmap[++x].txture)
		{
			SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.btnmap[x].txture,
					NULL, &(wolf->sdl.btnmap[x].loc.area));
		}
	}
	else if (arr == 3)
	{
		while (wolf->sdl.btnopt[++x].txture)
		{
			SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.btnopt[x].txture,
					NULL, &(wolf->sdl.btnopt[x].loc.area));
		}
	}
	SDL_RenderPresent(wolf->sdl.rend);
}

static void		update_loc_buttons(t_wolf *wolf, t_btn *arr)
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

void			draw_menu(t_wolf *wolf)
{
	int status;

	status = wolf->sdl.m_status;
	if (status == 1)
	{
		update_loc_buttons(wolf, wolf->sdl.btnarr);
		draw_buttons(wolf, status);
	}
	else if (status == 2)
	{
		update_loc_buttons(wolf, wolf->sdl.btnmap);
		draw_buttons(wolf, status);
	}
	else if (status == 3)
	{
		update_loc_buttons(wolf, wolf->sdl.btnopt);
		draw_buttons(wolf, status);
	}
}
