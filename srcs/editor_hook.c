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
		printf("%d\n",close_editor(doom));
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

int		editor_mouse_press(int btn, int x, int y, t_doom *doom)
{
	(void)btn;
	(void)x;
	(void)y;
	(void)doom;
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

int		editor_mouse_move(int x, int y, t_doom *doom)
{
	(void)x;
	(void)y;
	(void)doom;
	return (0);
}
