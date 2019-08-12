/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/07/21 11:59:47 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** Add here function that need to be done when a key is pressed
** (wont trigger in loop_hook)
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

static void	lil_editor_key_press(int key, t_doom *doom)
{
	if (key == SDLK_o)
	{
		doom->edit.currmur = NULL;
		doom->edit.currstat = NULL;
		doom->edit.status = ED_OPEN;
	}
	else if (key == SDLK_SPACE)
	{
		if (doom->edit.currpilier)
			doom->edit.status = ED_FORME;
		else
			ft_putendl("Please select a pillar");
	}
	else
		ft_nodeadd_int(&(doom->edit.keys), key);
}

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

/*
** Add here function that need to be done when mouse is pressed
** Example :
** else if (btn == SDL_BUTTON_yourbutton)
**		action();
*/

void		editor_mouse_left(SDL_MouseButtonEvent e, t_editor *edit)
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
			ft_removewall(&edit->map->murs, &edit->currmur);
			ft_wallpushend(&edit->map->murs, pil[0], pil[1], edit->txtrgame[0]);
			ft_wallpushend(&edit->map->murs, pil[0], pil[2], edit->txtrgame[0]);
			edit->currmur = NULL;
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

void		editor_mouse_right(SDL_MouseButtonEvent e, t_editor *edit)
{
	if (edit->map && edit->currpilier && edit->hoverpilier)
		ft_wallpushend(&edit->map->murs, edit->currpilier,
			(edit->currpilier = edit->hoverpilier), edit->txtrgame[0]);
	else if (e.clicks == 2)
	{
		ft_remove_pillar_from_sector(edit->sectors, &edit->pillist,
			&edit->hoverpilier);
		if (edit->currmur == edit->hovermur)
			edit->currmur = NULL;
		ft_removewall(&edit->map->murs, &edit->hovermur);
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

/*
** Add here function that need to be done when mouse wheel is used
*/

static int	in_sectbox(SDL_MouseWheelEvent e, t_editor *edit)
{
	if (edit->sectscroll + e.y * 2 > 0)
		edit->sectscroll = 0;
	else
		edit->sectscroll += e.y * 2;
	return (0);
}

static int	in_txtrbox(SDL_MouseWheelEvent e, t_editor *edit)
{
	if (edit->txtrscroll + e.y * 2 > 0)
		edit->txtrscroll = 0;
	else
		edit->txtrscroll += e.y * 2;
	return (0);
}

static int	on_wall_prop(SDL_MouseWheelEvent e, t_editor *edit)
{
	if (edit->currstat->roty + e.y < 0)
		edit->currstat->roty = 0.0;
	else if (edit->currstat->roty + e.y > 100)
		edit->currstat->roty = 100.0;
	else
		edit->currstat->roty += e.y;
	edit->currstat->pos = line_percent(edit->currmur->pil1->pos,
		edit->currmur->pil2->pos, edit->currstat->roty / 100);
	return (0);
}

static int	on_prop(SDL_MouseWheelEvent e, t_editor *edit)
{
	if (edit->currstat->roty + e.y < 0)
		edit->currstat->roty += e.y + 360.0;
	else if (edit->currstat->roty + e.y > 360)
		edit->currstat->roty += e.y - 360.0;
	else
		edit->currstat->roty += e.y;
	return (0);
}

int			editor_mouse_wheel(SDL_MouseWheelEvent e, t_editor *edit)
{
	if (pos_in_rect(edit->sectbox, edit->mouse.x, edit->mouse.y))
		return (in_sectbox(e, edit));
	else if (pos_in_rect(edit->optbox, edit->mouse.x, edit->mouse.y))
		return (opt_menu_wheel(e, edit));
	else if (edit->selecttxtr && pos_in_rect(edit->txtrbox,
		edit->mouse.x, edit->mouse.y))
		return (in_txtrbox(e, edit));
	if (edit->currstat && edit->currmur && (ISWALLPROP(edit->currstat->type)))
		return (on_wall_prop(e, edit));
	else if (edit->currstat && !(ISPROP(edit->currstat->type)))
		return (on_prop(e, edit));
	scroll_limits(&edit->mappos.z,
		e.y * (edit->mappos.z / 400 * ZOOMSPEED + 1), MINZOOM, MAXZOOM);
	return (0);
}

static int	move_optbox(SDL_MouseMotionEvent e, t_editor *edit)
{
	e.x = (e.y - edit->sectscroll) / SECTORBOXHEIGHT;
	if ((e.x == 0 && edit->currstat && edit->currstat == &edit->player.stat)
	|| (2 <= e.x && e.x <= 3 && edit->map && !edit->currstat && !edit->currmur)
		|| (e.x == 0 && edit->currstat && ISPROP(edit->currstat->type)))
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE));
	else
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
	return (0);
}

static void	move_left_press(SDL_MouseMotionEvent e, t_editor *edit)
{
	if (edit->currpilier)
	{
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL));
		ft_movepillar(edit->sectors, edit->currpilier,
			(t_vct2){e.xrel, e.yrel}, edit->mappos.z);
	}
	else if (edit->currstat)
	{
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL));
		if (!(edit->currmur))
		{
			edit->currstat->pos.x += e.xrel * (EDITPREC) / edit->mappos.z;
			edit->currstat->pos.y += e.yrel * (EDITPREC) / edit->mappos.z;
		}
	}
	else if (edit->currmur)
	{
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL));
		ft_movewall(edit->currmur, e.xrel, e.yrel, edit->mappos.z);
	}
}

static void	lil_editor_mouse_move(SDL_MouseMotionEvent e, t_editor *edit)
{
	if (edit->hoverpilier || edit->hovermur)
	{
		if (e.state == SDL_BUTTON_RMASK
			&& edit->hoverpilier && !edit->currpilier)
		{
			ft_remove_pillar_from_sector(edit->sectors, &edit->pillist,
				&edit->hoverpilier);
			edit->hovermur = NULL;
		}
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
	}
	else
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
	if (e.state == SDL_BUTTON_LMASK)
		move_left_press(e, edit);
	else if (e.state == SDL_BUTTON_MMASK)
	{
		edit->mappos.x += e.xrel;
		edit->mappos.y += e.yrel;
	}
}

/*
** Add here function that need to be done when mouse if moved in window
*/

int			editor_mouse_move(SDL_MouseMotionEvent e, t_editor *edit)
{
	edit->mouse.x = e.x;
	edit->mouse.y = e.y;
	if (pos_in_rect(edit->sectbox, e.x, e.y))
	{
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
		return (0);
	}
	else if (pos_in_rect(edit->optbox, e.x, e.y))
		return (move_optbox(e, edit));
	else if (edit->selecttxtr && pos_in_rect(edit->txtrbox, e.x, e.y))
		return (0);
	edit->mapmouse = g_r_mp(edit, e.x, e.y);
	if (!(edit->hoverpilier = find_pilier(edit, edit->pillist, e.x, e.y)))
		edit->hovermur = find_mur(edit, edit->map, e.x, e.y);
	else
		edit->hovermur = NULL;
	lil_editor_mouse_move(e, edit);
	return (0);
}
