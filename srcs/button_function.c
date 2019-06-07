/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 23:05:38 by magrab            #+#    #+#             */
/*   Updated: 2019/06/07 05:58:02 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	start_button(t_doom *doom)
{
	sdl_set_status(doom, 2);
}

void	option_button(t_doom *doom)
{
	sdl_set_status(doom, 3);
}

void	return_button(t_doom *doom)
{
	sdl_set_status(doom, 1);
}

void	start_map_button(t_doom *doom)
{
	if (parsing(doom, doom->ui.curr_btn->data))
	{
		change_music(&doom->sound, doom->sound.on, 5000);
		sdl_set_status(doom, 0);
	}
	else
		ft_printf("Error reading file\n");
}
