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

static void draw_buttons(t_wolf *wolf, int arr)
{
	int x;

	x = -1;
	SDL_RenderClear(wolf->sdl.rend);
	if (arr == 1)
	{
		while (wolf->sdl.btnarr[++x].txture)
		{
			SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.btnarr[x].txture, NULL, &(wolf->sdl.btnarr[x].area));
		}
	}
	else if (arr == 2)
	{
		while (wolf->sdl.btnmap[++x].txture)
		{
			SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.btnmap[x].txture, NULL, &(wolf->sdl.btnmap[x].area));
		}
	}
	SDL_RenderPresent(wolf->sdl.rend);
}

static void update_loc_buttons(t_wolf *wolf, t_btn *arr)
{
	t_btn *tmp;
	int x;
	int y;

	x = -1;
	y = 0;
	while (arr[++x].txture)
	{
		tmp = &(arr[x]);
		arr[x].area.x = wolf->sdl.size.x * (tmp->pos.x / 100); //controls the rect's x coordinate
		arr[x].area.y = wolf->sdl.size.y * (tmp->pos.y / 100);
		if (tmp->snapx == 1)
			arr[x].area.x -= tmp->area.w / 2;
		else if (tmp->snapx == 2)
			arr[x].area.x -= tmp->area.w;
		else if (tmp->snapx == 3)
			arr[x].area.x = x + tmp->pos.x;
		if (tmp->snapy == 1)
			arr[x].area.y -= tmp->area.h / 2;
		else if (tmp->snapy == 2)
			arr[x].area.y -= tmp->area.h;
		else if (tmp->snapy == 3)
			arr[x].area.y = y + tmp->pos.y;
		y = tmp->area.y + tmp->area.h;
	}
}

void draw_menu(t_wolf *wolf)
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
}
