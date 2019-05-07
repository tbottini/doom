/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 23:05:38 by magrab            #+#    #+#             */
/*   Updated: 2019/05/07 23:05:39 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
