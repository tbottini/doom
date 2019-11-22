/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_function_option.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 13:53:19 by magrab            #+#    #+#             */
/*   Updated: 2019/08/16 13:53:20 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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

void	option_button(t_doom *doom)
{
	sdl_set_status(doom, MENU_OPTION);
}

void	ignoption_button(t_doom *doom)
{
	sdl_set_status(doom, MENU_IGOPTION);
}
