/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:18:09 by magrab            #+#    #+#             */
/*   Updated: 2019/04/18 18:18:11 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int key_press(int key, t_wolf *wolf)
{
	if (key == SDLK_BACKQUOTE)
	{
		wolf->sdl.m_status = 1;
		draw_menu(wolf);
	}
	else
	{
		ft_nodeadd_int(&(wolf->sdl.keys), key);
	}
	//ft_printf("Key %d : %s pressed\n", key, SDL_GetKeyName(key));
	return (0);
}

int key_release(int key, t_wolf *wolf)
{
	ft_noderm_int(&(wolf->sdl.keys), key);
	//ft_printf("Key %d : %s released\n", key, SDL_GetKeyName(key));
	return (0);
}

int mouse_press(int btn, int x, int y, t_wolf *wolf)
{
	if (btn == SDL_BUTTON_LEFT)
		btn_click(wolf, x, y);
	else if (btn == 4)
		wolf->fov++;
	else if (btn == 5)
		wolf->fov--;
	//ft_printf("Mouse p %d at %d : %d\n", btn, x, y);
	return (0);
}

int mouse_release(int btn, int x, int y, t_wolf *wolf)
{
	(void)wolf;
	(void)x;
	(void)y;
	(void)btn;
	//ft_printf("Mouse r %d at %d : %d\n", btn, x, y);
	return (0);
}

int mouse_move(int x, int y, t_wolf *wolf)
{
	wolf->sdl.m_pos.x = x;
	wolf->sdl.m_pos.y = y;
	return (0);
}
