/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu_wheel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 02:08:31 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 02:08:32 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int			opt_menu_wheel(SDL_MouseWheelEvent e, t_editor *edit)
{
	e.x = (edit->mouse.y - edit->sectscroll) / SBH;
	if (e.x == 0 && edit->currstat)
	{
		if (edit->currstat == &edit->player.stat)
			scroll_limits(&edit->currstat->type, e.y, 10, 250);
		else if (ISPROP(edit->currstat->type))
			scroll_limits(&edit->currstat->type, e.y, MINPROPSPOS, MAXPROPSPOS);
		else if (ISWALLPROP(edit->currstat->type))
			scroll_limits(&edit->currstat->type, e.y,
				MINWPROPSPOS, MAXWPROPSPOS);
	}
	else if (e.x == 2 && edit->map)
		scroll_limits(&edit->map->htop, e.y * 5, 0, MAXEDITVAR);
	else if (e.x == 3 && edit->map)
		scroll_limits(&edit->map->hsol, e.y * 5, 0, MAXEDITVAR);
	return (0);
}
