/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 00:51:54 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 00:51:56 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	lil_editor_key_press(int key, t_doom *doom)
{
	if (key == SDLK_o)
	{
		doom->edit.currmur = NULL;
		doom->edit.currstat = NULL;
		doom->edit.status = ED_OPEN;
	}
	else
		ft_nodeadd_int(&(doom->edit.keys), key);
}

/*
**	else if (key == SDLK_SPACE)
**	{
**		if (doom->edit.currpilier)
**			doom->edit.status = ED_FORME;
**		else
**			ft_putendl("Please select a pillar");
**	}
*/

/*
** Add here function that need to be done when a key is pressed
** (wont trigger in loop_hook)
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

int			editor_key_press(int key, t_doom *doom)
{
	if (key == SDLK_BACKQUOTE)
		close_editor(doom);
	else if (key == SDLK_RETURN)
	{
		doom->edit.currmur = NULL;
		doom->edit.currstat = NULL;
		if (doom->edit.pillist)
			doom->edit.status = ED_SAVING;
	}
	else if (key == SDLK_1 || key == SDLK_2 || key == SDLK_3 || key == SDLK_4)
		ft_enemypushend(&doom->edit.ennlist, g_r_mp(&doom->edit,
			doom->edit.mouse.x, doom->edit.mouse.y), key - 48, doom->edit.map);
	else if (key == SDLK_6)
		ft_enemypushend(&doom->edit.ennlist, g_r_mp(&doom->edit,
		doom->edit.mouse.x, doom->edit.mouse.y), MINPROPSPOS, doom->edit.map);
	else if (key == SDLK_r)
		doom->edit.mappos = (t_vct3){doom->edit.size.x / 2,
			doom->edit.size.y / 2, 1000};
	else
		lil_editor_key_press(key, doom);
	return (0);
}

/*
** Add here function that need to be done when a key is released
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

int			editor_key_release(int key, t_doom *doom)
{
	ft_noderm_int(&(doom->edit.keys), key);
	return (0);
}
