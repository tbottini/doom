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
	else if (key == SDLK_4)
		printf("currpillar : %p\n", doom->edit.currpilier);
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
		//doom->edit.currpilier = find_pilier(doom->edit.map, x - doom->edit.mappos.x, y - doom->edit.mappos.y);
	}
	return (0);
}

/*
** Add here function that need to be done when mouse wheel is used
*/

int		editor_mouse_wheel(SDL_MouseWheelEvent e, t_doom *doom)
{
	doom->edit.mapzoom += e.y;
	printf("Wheel %d\t%d\n", doom->edit.mapzoom, e.y);
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
	doom->edit.currpilier = find_pilier(doom->edit.map, e.x - doom->edit.mappos.x, e.y - doom->edit.mappos.y);
	if (e.state == SDL_BUTTON_LMASK)
	{/*
		if (doom->edit.currpilier)
		{
			doom->edit.currpilier->pos.x += e.xrel;
			doom->edit.currpilier->pos.y += e.yrel;
		}
		else
		{*/
			doom->edit.mappos.x += e.xrel;
			doom->edit.mappos.y += e.yrel;
		//}
	}
	//fill_pixel(doom->edit.screen, doom->edit.size, (t_vct2){x, y}, 0xFFFFFF);
	return (0);
}
