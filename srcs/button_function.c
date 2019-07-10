/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 23:05:38 by magrab            #+#    #+#             */
/*   Updated: 2019/07/10 14:15:54 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	start_button(t_doom *doom)
{
	sdl_set_status(doom, 2);
}

void	resume_button(t_doom *doom)
{
	sdl_set_status(doom, 0);
}

void	option_button(t_doom *doom)
{
	sdl_set_status(doom, 3);
}

void	ignoption_button(t_doom *doom)
{
	sdl_set_status(doom, 5);
}

void	main_menu_button(t_doom *doom)
{
	change_music(&doom->game.sound, 0, 0);
	doom->ui.curr_btn = NULL;
	sdl_set_status(doom, 1);
}

void	return_button(t_doom *doom)
{
	if (doom->ui.m_status == 5)
		sdl_set_status(doom, 4);
	else
		sdl_set_status(doom, 1);
}

void	start_map_button(t_doom *doom)
{
//	if (!(read_file(doom, doom->ui.curr_btn->data)))
	if (parsing(doom, doom->ui.curr_btn->data))
	{
		player_init(&doom->game.player);
		change_music(&doom->game.sound, doom->game.sound.on, 5000);
		sdl_set_status(doom, 0);
	}
	else
		ft_printf("Error reading file\n");
}
