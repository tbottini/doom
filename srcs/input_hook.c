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

int		key_press(int key, t_wolf *wolf)
{
	ft_printf("Key %d : %s pressed\n", key, SDL_GetKeyName(key));
	return (0);
}

int		key_release(int key, t_wolf *wolf)
{
	ft_printf("Key %d : %s released\n", key, SDL_GetKeyName(key));
	return (0);
}

int		mouse_press(int btn, int x, int y, t_wolf *wolf)
{
	btn_click(wolf, x, y);
	//ft_printf("Mouse p %d at %d : %d\n", btn, x, y);
	return (0);
}

int		mouse_release(int btn, int x, int y, t_wolf *wolf)
{
	//ft_printf("Mouse r %d at %d : %d\n", btn, x, y);
	return (0);
}

int		mouse_move(int x, int y, t_wolf *wolf)
{
	return (0);
}
