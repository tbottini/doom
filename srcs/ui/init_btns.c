/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_btns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/07/23 22:17:23 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Wolf Logo (Not really a button)
*/

t_btn	add_doom_button(t_doom *doom, const char *name)
{
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = NULL;
	tmp.loc.pos.x = 50;
	tmp.loc.pos.y = 5;
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 0;
	tmp.fgcolor = (SDL_Color){255, 255, 255, 0};
	tmp.bgcolor = (SDL_Color){191, 35, 44, 0};
	updatetext((t_updatetext){doom->sdl.rend, doom->ui.fonts.s128, &tmp.txture,
	&tmp.loc.area, name, tmp.fgcolor, tmp.bgcolor});
	return (tmp);
}

/*
** Start button (main menu)
*/

t_btn	add_start_button(t_doom *doom)
{
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = &start_button;
	tmp.loc.pos.x = 50;
	tmp.loc.pos.y = 10;
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 3;
	tmp.fgcolor = (SDL_Color){150, 150, 150, 0};
	tmp.bgcolor = (SDL_Color){255, 255, 255, 0};
	updatetext((t_updatetext){doom->sdl.rend, doom->ui.fonts.s64, &tmp.txture,
	&tmp.loc.area, " START ", tmp.fgcolor, tmp.bgcolor});
	return (tmp);
}

/*
** Option button (main menu)
*/

t_btn	add_opt_button(t_doom *doom)
{
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = &option_button;
	tmp.loc.pos.x = 50;
	tmp.loc.pos.y = 20;
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 3;
	tmp.fgcolor = (SDL_Color){150, 150, 150, 0};
	tmp.bgcolor = (SDL_Color){255, 255, 255, 0};
	updatetext((t_updatetext){doom->sdl.rend, doom->ui.fonts.s64, &tmp.txture,
	&tmp.loc.area, " Options ", tmp.fgcolor, tmp.bgcolor});
	return (tmp);
}

/*
** Bottom Right button
*/

t_btn	add_quit_button(t_doom *doom, const char *str, void *fc)
{
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = fc;
	tmp.loc.pos.x = 95;
	tmp.loc.pos.y = 95;
	tmp.loc.snapx = 2;
	tmp.loc.snapy = 2;
	tmp.fgcolor = (SDL_Color){191, 35, 44, 0};
	tmp.bgcolor = (SDL_Color){255, 255, 255, 0};
	updatetext((t_updatetext){doom->sdl.rend, doom->ui.fonts.s64, &tmp.txture,
	&tmp.loc.area, str, tmp.fgcolor, tmp.bgcolor});
	return (tmp);
}
