/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 23:05:38 by magrab            #+#    #+#             */
/*   Updated: 2019/08/06 10:49:30 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	start_button(t_doom *doom)
{
	sdl_set_status(doom, MENU_MAP);
}

void	resume_button(t_doom *doom)
{
	sdl_set_status(doom, MENU_INGAME);
}

void	option_button(t_doom *doom)
{
	sdl_set_status(doom, MENU_OPTION);
}

void	ignoption_button(t_doom *doom)
{
	sdl_set_status(doom, MENU_IGOPTION);
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
	}
	else
		ft_printf("Error reading file\n");
}

void	set_easy(t_doom *doom)
{
	doom->game.difficulty = EASY;
}

void	set_medium(t_doom *doom)
{
	doom->game.difficulty = MEDIUM;
}

void	set_hard(t_doom *doom)
{
	doom->game.difficulty = HARD;
}
