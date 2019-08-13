/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_inspect_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 02:58:48 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 02:58:49 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "render.h"

static void	if_character(t_editor *editor, SDL_Rect box)
{
	if (&editor->player.stat == editor->currstat) // If Player
		sdl_int_put(editor->rend, editor->ui->fonts.s32,
			(t_vct2){box.x + 5, box.y + 5}, "Health: ", editor->currstat->type,
			(SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
	else if (ISPROP(editor->currstat->type)) // If Prop
	{
		sdl_int_put(editor->rend, editor->ui->fonts.s32,
			(t_vct2){box.x + 5, box.y + 5}, "Type: ",
			editor->currstat->type - MINPROPSPOS,
			(SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
		sdl_string_put(editor->rend, editor->ui->fonts.s32,
			(t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT + 5}, "Delete",
			(SDL_Color){255, 100, 100, 0xFF});
	}
	else if (ISWALLPROP(editor->currstat->type)) // If Wall Prop
	{
		sdl_int_put(editor->rend, editor->ui->fonts.s32,
			(t_vct2){box.x + 5, box.y + 5}, "Type: ",
			editor->currstat->type - MINWPROPSPOS,
			(SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
		sdl_string_put(editor->rend, editor->ui->fonts.s32,
			(t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT + 5}, "Delete",
			(SDL_Color){255, 100, 100, 0xFF});
	}
	else
	{
		sdl_int_put(editor->rend, editor->ui->fonts.s32,
			(t_vct2){box.x + 5, box.y + 5}, "Type: ", editor->currstat->type,
			(SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
		sdl_string_put(editor->rend, editor->ui->fonts.s32,
			(t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT + 5}, "Delete",
			(SDL_Color){255, 100, 100, 0xFF});
	}
}

static void	if_mur(t_editor *editor, SDL_Rect box)
{
	SDL_Rect txtrpos;

	sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + 5}, "Texture:", (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
	txtrpos = (SDL_Rect){box.x + 120, box.y + 4, SECTORBOXHEIGHT - 2, SECTORBOXHEIGHT - 2};
	SDL_RenderCopy(editor->rend, editor->currmur->txtr, NULL, &txtrpos);
	if (editor->currmur->portal_ptr)
	{
		SDL_SetRenderDrawColor(editor->rend, 133, 133, 133, 255);
		SDL_RenderDrawLine(editor->rend, box.x, box.y + SECTORBOXHEIGHT + 5, box.x + box.w, box.y + SECTORBOXHEIGHT + 5);
		sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 1 + 5}, " Window", (editor->currmur->portal_id == WINDOW ? (SDL_Color){255, 255, 200, 0xFF} : (SDL_Color){200, 200, 200, 0xFF}));
		sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 2 + 5}, " Close Door", (editor->currmur->portal_id == CLOSE_DOOR ? (SDL_Color){255, 255, 200, 0xFF} : (SDL_Color){200, 200, 200, 0xFF}));
		sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 3 + 5}, " Open Door", (editor->currmur->portal_id == OPEN_DOOR ? (SDL_Color){255, 255, 200, 0xFF} : (SDL_Color){200, 200, 200, 0xFF}));
		sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 4 + 5}, " Portal", (editor->currmur->portal_id == PORTAL ? (SDL_Color){255, 255, 200, 0xFF} : (SDL_Color){200, 200, 200, 0xFF}));
		SDL_RenderDrawLine(editor->rend, box.x, box.y + SECTORBOXHEIGHT * 5, box.x + box.w, box.y + SECTORBOXHEIGHT * 5);
		sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 5 + 5}, " Level 0", (editor->currmur->level == 0 ? (SDL_Color){255, 255, 200, 0xFF} : (SDL_Color){200, 200, 200, 0xFF}));
		sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 6 + 5}, " Level 1", (editor->currmur->level == 1 ? (SDL_Color){255, 255, 200, 0xFF} : (SDL_Color){200, 200, 200, 0xFF}));
		sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 7 + 5}, " Level 2", (editor->currmur->level == 2 ? (SDL_Color){255, 255, 200, 0xFF} : (SDL_Color){200, 200, 200, 0xFF}));
		sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 8 + 5}, " Level 3", (editor->currmur->level == 3 ? (SDL_Color){255, 255, 200, 0xFF} : (SDL_Color){200, 200, 200, 0xFF}));
		SDL_RenderDrawLine(editor->rend, box.x, box.y + SECTORBOXHEIGHT * 9, box.x + box.w, box.y + SECTORBOXHEIGHT * 9);/* */
	}
	else
	{
		sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 1 + 5}, "Add Prop", (SDL_Color){75, 100, 200, 0xFF});
	}
}

static void	if_secteur(t_editor *editor, SDL_Rect box)
{
	SDL_Rect txtrpos;

	sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + 5}, "Ceil:", (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
	txtrpos = (SDL_Rect){box.x + 120, box.y + 4, SECTORBOXHEIGHT - 2, SECTORBOXHEIGHT - 2};
	SDL_RenderCopy(editor->rend, editor->map->top, NULL, &txtrpos);
	sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT + 5}, "Floor:", (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
	txtrpos = (SDL_Rect){box.x + 120, box.y + SECTORBOXHEIGHT + 4, SECTORBOXHEIGHT - 2, SECTORBOXHEIGHT - 2};
	SDL_RenderCopy(editor->rend, editor->map->sol, NULL, &txtrpos);
	sdl_int_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 2 + 5}, "Ceil: ", editor->map->htop, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
	sdl_int_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 3 + 5}, "Floor: ", editor->map->hsol, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
	if (editor->map->gravity)
		sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 4 + 5}, "Gravity: Moon", (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
	else
		sdl_string_put(editor->rend, editor->ui->fonts.s32, (t_vct2){box.x + 5, box.y + SECTORBOXHEIGHT * 4 + 5}, "Gravity: Earth", (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF});
}

void		draw_inspect_menu(t_editor *editor)
{
	SDL_SetRenderDrawColor(editor->rend, 66, 66, 66, 255);
	SDL_RenderFillRect(editor->rend, &editor->optbox);
	if (editor->currstat) // If Character
	{
		if_character(editor, editor->optbox);
	}
	else if (editor->currmur) // If mur
	{
		if_mur(editor, editor->optbox);
	}
	else if (editor->map) // If secteur
	{
		if_secteur(editor, editor->optbox);
	}
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 255);
}
