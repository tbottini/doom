/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/05/06 17:46:28 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		close_editor(t_doom *doom)
{
	fire_on_off(doom->sdl.screen, doom->sdl.size, 1);
	if (doom->edit.win)
	{
		doom->edit.status = 0;
		SDL_HideWindow(doom->edit.win);
		return (0);
	}
	return (-1);
}

void	start_editor(t_doom *doom)
{
	fire_on_off(doom->sdl.screen, doom->sdl.size, 0);
	SDL_ShowWindow(doom->edit.win);
	doom->edit.status = 1;
}
