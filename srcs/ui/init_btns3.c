/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_btns3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/06/12 15:37:01 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Pause Logo (Not really a button)
*/

t_btn	add_pause_button(t_doom *doom)
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
	&tmp.loc.area, " PAUSE ", tmp.fgcolor, tmp.bgcolor});
	return (tmp);
}

/*
** Start button (main menu)
*/

t_btn	add_resume_button(t_doom *doom)
{
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = &resume_button;
	tmp.loc.pos.x = 50;
	tmp.loc.pos.y = 20;
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 3;
	tmp.fgcolor = (SDL_Color){150, 150, 150, 0};
	tmp.bgcolor = (SDL_Color){255, 255, 255, 0};
	updatetext((t_updatetext){doom->sdl.rend, doom->ui.fonts.s64, &tmp.txture,
	&tmp.loc.area, " Resume ", tmp.fgcolor, tmp.bgcolor});
	return (tmp);
}

/*
** Option button (in game)
*/

t_btn	add_ing_opt_button(t_doom *doom)
{
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = &ignoption_button;
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
** Return Main Menu button (in game)
*/

t_btn	add_main_menu_button(t_doom *doom)
{
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = &main_menu_button;
	tmp.loc.pos.x = 50;
	tmp.loc.pos.y = 95;
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 2;
	tmp.fgcolor = (SDL_Color){150, 150, 150, 0};
	tmp.bgcolor = (SDL_Color){255, 255, 255, 0};
	updatetext((t_updatetext){doom->sdl.rend, doom->ui.fonts.s64, &tmp.txture,
	&tmp.loc.area, " Main Menu ", tmp.fgcolor, tmp.bgcolor});
	return (tmp);
}

/*
** Change music
*/

t_btn	add_middle_music_button(t_doom *doom)
{
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = NULL;
	tmp.loc.pos.x = 50;
	tmp.loc.pos.y = 20;
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 3;
	tmp.fgcolor = (SDL_Color){150, 150, 150, 0};
	tmp.bgcolor = (SDL_Color){255, 255, 255, 0};
	updatetext((t_updatetext){doom->sdl.rend, doom->ui.fonts.s64, &tmp.txture,
	&tmp.loc.area, " Track 1 ", tmp.fgcolor, tmp.bgcolor});
	return (tmp);
}
