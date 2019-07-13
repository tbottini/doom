/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/07/09 14:26:57 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MINZOOM 10
#define MAXZOOM 20000
#define ZOOMSPEED 3

/*
** Add here function that need to be done when a key is pressed (wont trigger in loop_hook)
** Example :
** else if (key == SDLK_yourkey)
**		action();
*/

int editor_key_press(int key, t_doom *doom)
{
	t_vct2 relpos;

	if (key == SDLK_BACKQUOTE)
	{
		close_editor(doom);
	}
	else if (key == SDLK_RETURN)
	{
		save_editor_to_file(&doom->edit);
	}
	else if (key == SDLK_1 || key == SDLK_2 || key == SDLK_3 || key == SDLK_4)
	{
		relpos = get_rel_mappos(&doom->edit, doom->edit.mouse.x, doom->edit.mouse.y);
		if (!ft_enemypushend(&doom->edit.ennlist, relpos, key - 48, doom->edit.map))
				ft_printf("Error adding Enemy\n");
	}
	else if (key == SDLK_6)
	{
		relpos = get_rel_mappos(&doom->edit, doom->edit.mouse.x, doom->edit.mouse.y);
		if (!ft_enemypushend(&doom->edit.ennlist, relpos, MINPROPSPOS, doom->edit.map))
				ft_printf("Error adding Prop\n");
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
	SDL_Texture *txtrclick;

	if (edit->status != ED_LOADED)
		return (0);
	if (pos_in_rect(edit->sectbox, e.x, e.y)) // If menu left
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
			sector_menu_click(edit, e.y, e.x > edit->sectbox.x + edit->sectbox.w - 50);
		return (0);
	}
	else if (pos_in_rect(edit->optbox, e.x, e.y)) // If menu right
	{
		opt_menu_click(edit, e.y);
		return (0);
	}
	else if (edit->selecttxtr && pos_in_rect(edit->txtrbox, e.x, e.y)) // If menu texture
	{
		if (edit->selecttxtr == FILL_PROP && edit->currstat && ISPROP(edit->currstat->type) && (e.x = txtr_menu_click_int(edit, e.x, e.y, MINPROPSPOS, MAXPROPSNUMBER)))
		{
			edit->currstat->type = e.x;
			edit->selecttxtr = NOSELECT;
		}
		else if (edit->selecttxtr == FILL_WPROP && edit->currstat && ISWALLPROP(edit->currstat->type) && (e.x = txtr_menu_click_int(edit, e.x, e.y, MINWPROPSPOS, MAXWPROPSNUMBER)))
		{
			edit->currstat->type = e.x;
			edit->selecttxtr = NOSELECT;
		}
		else if ((txtrclick = txtr_menu_click(edit, e.x, e.y, MAXTXTRNUMBER)))
		{
			if (edit->currmur)
				edit->currmur->txtr = txtrclick;
			else if (edit->map)
			{
				if (edit->selecttxtr == FILL_TXTR)
					edit->map->top = txtrclick;
				else if (edit->selecttxtr == FILL_SOL)
					edit->map->sol = txtrclick;
			}
			edit->selecttxtr = NOSELECT;
		}
		return (0);
	}
	edit->selecttxtr = NOSELECT;
	relpos = get_rel_mappos(edit, e.x, e.y);
	if (e.button == SDL_BUTTON_LEFT)
	{
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
			if (!ft_pillarpushend(&edit->pillist, relpos))
				ft_printf("Error adding pillar\n");
	}
	else if (e.button == SDL_BUTTON_RIGHT)
	{
		if (edit->currpilier && edit->hoverpilier)
		{
			ft_wallpushend(&edit->map->murs, edit->currpilier, edit->hoverpilier, edit->txtrgame[0]);
		}
		else if (edit->currstat)
		{
			if (!(ISENEMY(edit->currstat->type)) && &edit->player.stat != edit->currstat)
			{
				if (!(edit->currstat->mur = edit->hovermur))
					edit->currstat->mursec = NULL;
				else
					edit->currstat->mursec = edit->map;
			}
		}
		else if (e.clicks == 2)
		{
			ft_remove_pillar_from_sector(edit->sectors, &edit->pillist, &edit->hoverpilier);
			if (edit->currmur == edit->hovermur)
				edit->currmur = NULL;
			ft_removewall(&edit->map->murs, &edit->hovermur);
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
	else if (pos_in_rect(edit->optbox, edit->mouse.x, edit->mouse.y))
	{
		e.x = (edit->mouse.y - edit->sectscroll) / SECTORBOXHEIGHT;
		if (e.x == 0 && edit->currstat)
		{
			if (edit->currstat == &edit->player.stat)
			{
				if (edit->currstat->type + e.y < 10)
					edit->currstat->type = 10;
				else if (edit->currstat->type + e.y > 250)
					edit->currstat->type = 250;
				else
					edit->currstat->type += e.y;
			}
			if (ISPROP(edit->currstat->type))
			{
				if (edit->currstat->type + e.y < MINPROPSPOS)
					edit->currstat->type = MINPROPSPOS;
				else if (edit->currstat->type + e.y >= MAXPROPSPOS)
					edit->currstat->type = MAXPROPSPOS - 1;
				else
					edit->currstat->type += e.y;
			}
			else if (ISWALLPROP(edit->currstat->type))
			{
				if (edit->currstat->type + e.y < MINWPROPSPOS)
					edit->currstat->type = MINWPROPSPOS;
				else if (edit->currstat->type + e.y >= MAXWPROPSPOS)
					edit->currstat->type = MAXWPROPSPOS - 1;
				else
					edit->currstat->type += e.y;
			}
		}
		else if (e.x == 2 && edit->map)
		{
			if (edit->map->htop + e.y * 5 < 0)
				edit->map->htop = 0;
			else
				edit->map->htop += e.y * 5;
		}
		else if (e.x == 3 && edit->map)
		{
			if (edit->map->hsol + e.y * 5 < 0)
				edit->map->hsol = 0;
			else
				edit->map->hsol += e.y * 5;
		}
		return (0);
	}
	else if (edit->selecttxtr && pos_in_rect(edit->txtrbox, edit->mouse.x, edit->mouse.y))
	{
		if (edit->txtrscroll + e.y * 2 > 0)
			edit->txtrscroll = 0;
		else
			edit->txtrscroll += e.y * 2;
		return (0);
	}
	if (edit->currstat && edit->currmur && (ISWALLPROP(edit->currstat->type)))
	{
		if (edit->currstat->roty + e.y < 0)
			edit->currstat->roty = 0.0;
		else if (edit->currstat->roty + e.y > 100)
			edit->currstat->roty = 100.0;
		else
			edit->currstat->roty += e.y;
		edit->currstat->pos = line_percent(edit->currmur->pil1->pos, edit->currmur->pil2->pos, edit->currstat->roty / 100);
		return (0);
	}
	else if (edit->currstat && !(ISPROP(edit->currstat->type)))
	{
		if (edit->currstat->roty + e.y < 0)
			edit->currstat->roty += e.y + 360.0;
		else if (edit->currstat->roty + e.y > 360)
			edit->currstat->roty += e.y - 360.0;
		else
			edit->currstat->roty += e.y;
		return (0);
	}
	if (edit->mappos.z + e.y < MINZOOM)
		edit->mappos.z = MINZOOM;
	else if (edit->mappos.z + e.y > MAXZOOM)
		edit->mappos.z = MAXZOOM;
	else
		edit->mappos.z += e.y * (edit->mappos.z / 400 * ZOOMSPEED + 1);
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
*/
int editor_mouse_move(SDL_MouseMotionEvent e, t_editor *edit)
{
	edit->mouse.x = e.x;
	edit->mouse.y = e.y;
	if (pos_in_rect(edit->sectbox, e.x, e.y))
	{
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
		return (0);
	}
	else if (pos_in_rect(edit->optbox, e.x, e.y))
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
	else if (edit->selecttxtr && pos_in_rect(edit->txtrbox, e.x, e.y))
	{
		return (0);
	}
	edit->mapmouse = get_rel_mappos(edit, e.x, e.y);
	if (!(edit->hoverpilier = find_pilier(edit, edit->pillist, e.x, e.y)))
		edit->hovermur = find_mur(edit, edit->map, e.x, e.y);
	else
		edit->hovermur = NULL;
	if (edit->hoverpilier || edit->hovermur)
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
	else
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
	if (e.state == SDL_BUTTON_LMASK)
	{
		if (edit->currpilier)
		{
			SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL));
			ft_movepillar(edit->sectors, edit->currpilier, e.xrel, e.yrel, edit->mappos.z);
		}
		else if (edit->currstat)
		{
			SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL));
			if (!(edit->currmur))
			{
				edit->currstat->pos.x += e.xrel * (EDITORPRECISION) / edit->mappos.z;
				edit->currstat->pos.y += e.yrel * (EDITORPRECISION) / edit->mappos.z;
			}
		}
		else if (edit->currmur)
		{
			SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL));
			ft_movewall(edit->currmur, e.xrel, e.yrel, edit->mappos.z);
		}
	}
	else if (e.state == SDL_BUTTON_MMASK)
	{
		edit->mappos.x += e.xrel;
		edit->mappos.y += e.yrel;
	}
	return (0);
}
