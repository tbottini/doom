/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_mouse_press.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 00:54:56 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 00:54:57 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Add here function that need to be done when mouse is pressed
** Example :
** else if (btn == SDL_BUTTON_yourbutton)
**		action();
*/

static void	editor_mouse_left(SDL_MouseButtonEvent e, t_editor *edit)
{
	t_pilier	*pil[3];

	edit->currmur = NULL;
	edit->currstat = NULL;
	if (!(edit->currpilier = find_pilier(edit, edit->pillist, e.x, e.y)))
	{
		if (!(edit->currstat = find_player(edit, e.x, e.y)))
			edit->currmur = find_mur(edit, edit->map, e.x, e.y);
		else
			edit->currmur = edit->hovermur;
	}
	if (e.clicks == 2)
	{
		pil[0] = ft_pillarpushend(&edit->pillist, g_r_mp(edit, e.x, e.y));
		if (edit->currmur)
		{
			pil[1] = edit->currmur->pil1;
			pil[2] = edit->currmur->pil2;
			ft_removewall(edit, &edit->map->murs, &edit->currmur);
			ft_wallpushend(&edit->map->murs, pil[0], pil[1], edit->txtrgame[0]);
			ft_wallpushend(&edit->map->murs, pil[0], pil[2], edit->txtrgame[0]);
			edit->hovermur = NULL;
		}
	}
}

static void	lil_editor_mouse_right(SDL_MouseButtonEvent e, t_editor *edit)
{
	t_pilier	*pil;

	if (edit->map && edit->currpilier)
	{
		if (!(pil = ft_pillarpushend(&edit->pillist, g_r_mp(edit, e.x, e.y))))
			ft_putendl_fd("Error adding pillar\n", 2);
		ft_wallpushend(&edit->map->murs, edit->currpilier, pil,
			edit->txtrgame[0]);
		edit->currpilier = pil;
	}
	else if (edit->currstat)
	{
		if (!(ISENEMY(edit->currstat->type))
			&& &edit->player.stat != edit->currstat)
		{
			if (!(edit->currstat->mur = edit->hovermur))
				edit->currstat->mursec = NULL;
			else
				edit->currstat->mursec = edit->map;
		}
	}
}

static void	editor_mouse_right(SDL_MouseButtonEvent e, t_editor *edit)
{
	if (edit->map && edit->currpilier && edit->hoverpilier)
		ft_wallpushend(&edit->map->murs, edit->currpilier,
			(edit->currpilier = edit->hoverpilier), edit->txtrgame[0]);
	else if (e.clicks == 2)
	{
		ft_remove_pillar_from_sector(edit, edit->sectors, &edit->pillist,
			&edit->hoverpilier);
		if (edit->currmur == edit->hovermur)
			edit->currmur = NULL;
		ft_removewall(edit, &edit->map->murs, &edit->hovermur);
	}
	else
		lil_editor_mouse_right(e, edit);
}

static void	lil_editor_mouse_press(SDL_MouseButtonEvent e, t_editor *edit)
{
	edit->selecttxtr = NOSELECT;
	if (e.button == SDL_BUTTON_LEFT)
	{
		editor_mouse_left(e, edit);
	}
	else if (e.button == SDL_BUTTON_RIGHT)
	{
		editor_mouse_right(e, edit);
	}
}

int			editor_mouse_press(SDL_MouseButtonEvent e, t_editor *edit)
{
	if (edit->status != ED_LOADED)
		return (0);
	if (pos_in_rect(edit->sectbox, e.x, e.y))
	{
		if (edit->currstat)
			edit->currstat->sector = sector_menu_click(edit, e.y, 2);
		else if (edit->currmur)
		{
			if ((edit->currmur->portal_ptr = sector_menu_click(edit, e.y, 2)))
				edit->currmur->portal_id = 4;
			else
				edit->currmur->portal_id = 0;
		}
		else
			sector_menu_click(edit, e.y,
				e.x > edit->sectbox.x + edit->sectbox.w - 50);
		return (0);
	}
	else if (pos_in_rect(edit->optbox, e.x, e.y))
		return (opt_menu_click(edit, e.y));
	else if (edit->selecttxtr && pos_in_rect(edit->txtrbox, e.x, e.y))
		return (texturebox_click(edit, e));
	lil_editor_mouse_press(e, edit);
	return (0);
}
