/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/05/06 17:46:28 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Add here function that need to be done when a key is pressed (wont trigger in loop_hook)
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

int		editor_key_press(int key, t_doom *doom)
{
	if (key == SDLK_BACKQUOTE)
	{
		close_editor(doom);
	}
	else if (key == SDLK_5)
		ft_nodeprint_pillar(doom->edit.map);
	else if (key == SDLK_6)
		draw_map(&doom->edit);
	else
		ft_nodeadd_int(&(doom->sdl.keys), key);
	return (0);
}

/*
** Add here function that need to be done when a key is released
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

int		editor_key_release(int key, t_doom *doom)
{
	ft_noderm_int(&(doom->sdl.keys), key);
	return (0);
}

/*
** Add here function that need to be done when mouse is pressed
** Example :
** else if (btn == SDL_BUTTON_yourbutton)
**		action();
*/

int		editor_mouse_press(int btn, int x, int y, t_doom *doom)
{
	t_vct2 pos;
	if (btn == SDL_BUTTON_LEFT)
	{
		if (!(doom->edit.map))
		{
			if (!(doom->edit.map = ft_newpillar((t_vct2){0, 0})))
				doom_exit(doom);
			doom->edit.mappos = (t_vct2){x, y};
			doom->edit.mapzoom = 1;
			doom->edit.currpilier = doom->edit.map;
		}
		else
			doom->edit.currpilier = find_pilier(doom->edit.map, x - doom->edit.mappos.x, y - doom->edit.mappos.y);
	}
	else if (btn == SDL_BUTTON_RIGHT)
	{
		if (doom->edit.currpilier)
		{
			pos.x = x - doom->edit.mappos.x;
			pos.y = y - doom->edit.mappos.y;
			
			if (!(ft_pillarpushend(&(doom->edit.currpilier), pos)))
				doom_exit(doom); 
		}
	}
	printf("currpillar : %p\n", doom->edit.currpilier);
	return (0);
}

/*
** Add here function that need to be done when mouse is released
** Example :
** else if (btn == SDL_BUTTON_yourbutton)
**		action();
*/

int		editor_mouse_release(int btn, int x, int y, t_doom *doom)
{
	(void)btn;
	(void)x;
	(void)y;
	(void)doom;
	return (0);
}

/*
** Add here function that need to be done when mouse if moved in window
** x and y are relative postions when in gamemode
*/

int		editor_mouse_move(SDL_MouseMotionEvent e, t_doom *doom)
{
	if (e.state == SDL_BUTTON_LMASK)
	{
		if (doom->edit.currpilier)
		{
			doom->edit.currpilier->pos.x += e.xrel;
			doom->edit.currpilier->pos.y += e.yrel;
		}
		else
		{
			doom->edit.mappos.x += e.xrel;
			doom->edit.mappos.y += e.yrel;
		}
	}
	//fill_pixel(doom->edit.screen, doom->edit.size, (t_vct2){x, y}, 0xFFFFFF);
	return (0);
}
