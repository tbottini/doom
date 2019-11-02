/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 23:05:38 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 02:51:56 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "input.h"

void	start_button(t_doom *doom)
{
	sdl_set_status(doom, MENU_MAP);
}

void	resume_button(t_doom *doom)
{
	sdl_set_status(doom, MENU_INGAME);
}

void	main_menu_button(t_doom *doom)
{
	change_music(&doom->game.sound, 0, 0);
	free_game(&doom->game);
	doom->ui.curr_btn = NULL;
	sdl_set_status(doom, MENU_MAIN);
}

void	return_button(t_doom *doom)
{
	if (doom->ui.m_status == MENU_IGOPTION)
		sdl_set_status(doom, MENU_IGMAIN);
	else
		sdl_set_status(doom, MENU_MAIN);
}

void	start_map_button(t_doom *doom)
{
	if (!(read_file(&doom->game, doom->ui.curr_btn->data, false)))
	{
		player_init(&doom->game.player);
		change_music(&doom->game.sound, doom->game.sound.on, 5000);
		sdl_set_status(doom, MENU_INGAME);
		sector_iter(doom->game.sectors, doom->game.len.nb_sects,
			&sector_wall_props_init);
	}
	else
		ft_putendl("Error reading file");
}
