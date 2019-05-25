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

#define MINZOOM 10
#define MAXZOOM 20000

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
		ft_clear_pillar_list(&doom->edit.map);
	else if (key == SDLK_r)
	{
		doom->edit.mappos = (t_vct2){doom->edit.size.x / 2, doom->edit.size.y / 2};
		doom->edit.mapzoom = 100;
	}
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

t_vct2	get_rel_mappos(t_editor *editor, int x, int y)
{
	t_vct2 pos;

	pos.x = (x - editor->mappos.x) * EDITORPRECISION / editor->mapzoom;
	pos.y = (y - editor->mappos.y) * EDITORPRECISION / editor->mapzoom;
	return (pos);
}

int		editor_mouse_press(int btn, int x, int y, t_doom *doom)
{
	t_vct2 relpos;
	t_lstpil tmp;

	relpos = get_rel_mappos(&doom->edit, x, y);
	//ft_printf("pos %d\t%d\n", (x - doom->edit.mappos.x) / doom->edit.mapzoom, (y - doom->edit.mappos.y) / doom->edit.mapzoom);
	//ft_printf("Center %d\t%d\n", doom->edit.size.x / 2 - x, doom->edit.size.y / 2 - y);
	ft_printf("stru %d\t%d\n",  relpos.x, relpos.y);
	ft_printf("area %d\n", MAXZOOM / doom->edit.mapzoom);
	if (btn == SDL_BUTTON_LEFT)
	{
		doom->edit.currpilier = find_pilier(&doom->edit, doom->edit.map, x, y);
	}
	else if (btn == SDL_BUTTON_RIGHT)
	{
		if (doom->edit.currpilier)
		{
			tmp = find_pilier(&doom->edit, doom->edit.map, x, y);
			if (tmp && doom->edit.currpilier != tmp
				&& doom->edit.currpilier->next != tmp
				&& doom->edit.currpilier->prvs != tmp)
			{
				doom->edit.currpilier->next = tmp;
				doom->edit.currpilier->next->prvs = doom->edit.currpilier;
			}
			else if (!(ft_pillarpushnext(&doom->edit.currpilier, relpos)))
				ft_printf("Error adding pillar\n");
		}
	}
	return (0);
}

/*
** Add here function that need to be done when mouse wheel is used
*/

int		editor_mouse_wheel(SDL_MouseWheelEvent e, t_doom *doom)
{
	if (doom->edit.mapzoom + e.y < MINZOOM)
		doom->edit.mapzoom = MINZOOM;
	else if (doom->edit.mapzoom + e.y > MAXZOOM)
		doom->edit.mapzoom = MAXZOOM;
	else
		doom->edit.mapzoom += e.y * (doom->edit.mapzoom / 400 + 1);
	ft_printf("\rWheel %d\t%d        ", doom->edit.mapzoom, e.y);
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
	doom->edit.🐁.x = e.x;
	doom->edit.🐁.y = e.y;
	doom->edit.map🐁 = get_rel_mappos(&doom->edit, e.x, e.y);
	doom->edit.hoverpilier = find_pilier(&doom->edit, doom->edit.map, e.x, e.y);
	if (e.state == SDL_BUTTON_LMASK)
	{
		if (doom->edit.currpilier)
		{
			doom->edit.currpilier->pos.x += e.xrel * (EDITORPRECISION) / doom->edit.mapzoom;
			doom->edit.currpilier->pos.y += e.yrel * (EDITORPRECISION) / doom->edit.mapzoom;
		}
	}
	else if (e.state == SDL_BUTTON_MMASK)
	{
		doom->edit.mappos.x += e.xrel;
		doom->edit.mappos.y += e.yrel;
	}
	return (0);
}
