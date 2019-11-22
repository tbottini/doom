/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_btns4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 08:20:54 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Change Difficulty
*/

t_btn	add_middle_diff_button(t_doom *doom, SDL_Rect *parent)
{
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = &set_medium;
	tmp.loc.parent = parent;
	tmp.loc.pos.x = 50;
	tmp.loc.pos.y = 200;
	tmp.loc.snapx = 1;
	tmp.loc.snapy = 3;
	tmp.fgcolor = (SDL_Color){255, 255, 255, 0};
	tmp.bgcolor = (SDL_Color){191, 35, 44, 0};
	updatetext((t_updatetext){doom->sdl.rend, doom->ui.fonts.s64, &tmp.txture,
	&tmp.loc.area, " MEDIUM ", tmp.fgcolor, tmp.bgcolor});
	return (tmp);
}

t_btn	add_left_diff_button(t_doom *doom, SDL_Rect *parent)
{
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = &set_easy;
	tmp.loc.parent = parent;
	tmp.loc.pos.x = 10;
	tmp.loc.pos.y = 0;
	tmp.loc.snapx = 5;
	tmp.loc.snapy = 4;
	tmp.fgcolor = (SDL_Color){255, 255, 255, 0};
	tmp.bgcolor = (SDL_Color){191, 35, 44, 0};
	updatetext((t_updatetext){doom->sdl.rend, doom->ui.fonts.s64, &tmp.txture,
	&tmp.loc.area, " EASY ", tmp.fgcolor, tmp.bgcolor});
	return (tmp);
}

t_btn	add_right_diff_button(t_doom *doom, SDL_Rect *parent)
{
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = &set_hard;
	tmp.loc.parent = parent;
	tmp.loc.pos.x = 10;
	tmp.loc.pos.y = 0;
	tmp.loc.snapx = 3;
	tmp.loc.snapy = 4;
	tmp.fgcolor = (SDL_Color){255, 255, 255, 0};
	tmp.bgcolor = (SDL_Color){191, 35, 44, 0};
	updatetext((t_updatetext){doom->sdl.rend, doom->ui.fonts.s64, &tmp.txture,
	&tmp.loc.area, " HARD ", tmp.fgcolor, tmp.bgcolor});
	return (tmp);
}

t_btn	add_left_music_button(t_doom *doom, SDL_Rect *parent)
{
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = &prev_track;
	tmp.loc.parent = parent;
	tmp.loc.pos.x = 10;
	tmp.loc.pos.y = 0;
	tmp.loc.snapx = 5;
	tmp.loc.snapy = 4;
	tmp.fgcolor = (SDL_Color){150, 150, 150, 0};
	tmp.bgcolor = (SDL_Color){255, 255, 255, 0};
	updatetext((t_updatetext){doom->sdl.rend, doom->ui.fonts.s64, &tmp.txture,
	&tmp.loc.area, " < ", tmp.fgcolor, tmp.bgcolor});
	return (tmp);
}

t_btn	add_right_music_button(t_doom *doom, SDL_Rect *parent)
{
	t_btn			tmp;

	ft_bzero(&tmp, sizeof(t_btn));
	tmp.func = &next_track;
	tmp.loc.parent = parent;
	tmp.loc.pos.x = 10;
	tmp.loc.pos.y = 0;
	tmp.loc.snapx = 3;
	tmp.loc.snapy = 4;
	tmp.fgcolor = (SDL_Color){150, 150, 150, 0};
	tmp.bgcolor = (SDL_Color){255, 255, 255, 0};
	updatetext((t_updatetext){doom->sdl.rend, doom->ui.fonts.s64, &tmp.txture,
	&tmp.loc.area, " > ", tmp.fgcolor, tmp.bgcolor});
	return (tmp);
}
