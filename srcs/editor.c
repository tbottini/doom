/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/04/16 00:18:29 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		close_editor(t_doom *doom)
{
	if (!(doom->edit.win))
	{
		doom->edit.status = 0;
		SDL_HideWindow(doom->edit.win);
		return (0);
	}
	return (-1);
}

int		start_editor(t_doom *doom)
{
	SDL_ShowWindow(doom->edit.win);
	doom->edit.status = 1;
	return (0);
}
