/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/06/20 16:30:43 by tbottini         ###   ########.fr       */
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

int editor_key_press(int key, t_doom *doom)
{
	if (key == SDLK_BACKQUOTE)
	{
		close_editor(doom);
	}
	else if (key == SDLK_3)
	{
		doom->edit.map = push_secteur(&(doom->edit.sectors));
	}
	else if (key == SDLK_4)
		printf("currpillar : %p\n", doom->edit.currpilier);
	else if (key == SDLK_5)
		ft_nodeprint_secteur(doom->edit.sectors);
	else if (key == SDLK_6)
	{
		ft_clear_secteur_list(&doom->edit.sectors);
	}
	else if (key == SDLK_r) // Reload position
	{
		doom->edit.mappos = (t_vct3){doom->edit.size.x / 2, doom->edit.size.y / 2, 1000};
	}
	else
		ft_nodeadd_int(&(doom->edit.keys), key);
	return (0);
}

/*
** Add here function that need to be done when a key is released
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

int editor_key_release(int key, t_doom *doom)
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

int editor_mouse_press(SDL_MouseButtonEvent e, t_editor *edit)
{
	t_vct2 relpos;

	if (pos_in_rect(edit->sectbox, e.x, e.y))
	{
		sector_menu(edit, e.y, e.x > edit->sectbox.x + edit->sectbox.w - 50);
		return (0);
	}
	relpos = get_rel_mappos(edit, e.x, e.y);
	if (e.button == SDL_BUTTON_LEFT)
	{
		edit->currpilier = find_pilier(edit, edit->pillist, e.x, e.y);
		if (e.clicks == 2)
			if (!ft_pillarpushend(&edit->pillist, relpos))
				ft_printf("Error adding pillar\n");
	}
	else if (e.button == SDL_BUTTON_RIGHT)
	{
		if (edit->currpilier && edit->hoverpilier)
		{
			ft_wallpushend(&edit->map->murs, edit->currpilier, edit->hoverpilier);
		}
		else if (e.clicks == 2)
		{
			ft_remove_pillar_from_sector(edit->sectors, &edit->pillist, &edit->hoverpilier);
		}
	}
	return (0);
}

/*
** Add here function that need to be done when mouse wheel is used
*/

int editor_mouse_wheel(SDL_MouseWheelEvent e, t_editor *edit)
{
	if (pos_in_rect(edit->sectbox, edit->mouse.x, edit->mouse.y))
	{
		if (edit->sectscroll + e.y * 2 > 0)
			edit->sectscroll = 0;
		else
			edit->sectscroll += e.y * 2;
		return (0);
	}
	if (edit->mappos.z + e.y < MINZOOM)
		edit->mappos.z = MINZOOM;
	else if (edit->mappos.z + e.y > MAXZOOM)
		edit->mappos.z = MAXZOOM;
	else
		edit->mappos.z += e.y * (edit->mappos.z / 400 + 1);
	ft_printf("\rWheel %d\t%d        ", edit->mappos.z, e.y);
	return (0);
}

/*
** Add here function that need to be done when mouse is released
** Example :
** else if (btn == SDL_BUTTON_yourbutton)
**		action();
*/

int editor_mouse_release(int btn, int x, int y, t_doom *doom)
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

int editor_mouse_move(SDL_MouseMotionEvent e, t_doom *doom)
{
	doom->edit.mouse.x = e.x;
	doom->edit.mouse.y = e.y;
	if (pos_in_rect(doom->edit.sectbox, e.x, e.y))
	{
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
		return (0);
	}
	doom->edit.mapmouse = get_rel_mappos(&doom->edit, e.x, e.y);
	doom->edit.hoverpilier = find_pilier(&doom->edit, doom->edit.pillist, e.x, e.y);
	if (doom->edit.hoverpilier)
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
	else
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
	if (e.state == SDL_BUTTON_LMASK)
	{
		if (doom->edit.currpilier)
		{
			SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL));
			doom->edit.currpilier->pos.x += e.xrel * (EDITORPRECISION) / doom->edit.mappos.z;
			doom->edit.currpilier->pos.y += e.yrel * (EDITORPRECISION) / doom->edit.mappos.z;
		}
	}
	else if (e.state == SDL_BUTTON_MMASK)
	{
		doom->edit.mappos.x += e.xrel;
		doom->edit.mappos.y += e.yrel;
	}
	return (0);
}
