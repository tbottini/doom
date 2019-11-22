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

static void	if_character(t_editor *e, SDL_Renderer *r, TTF_Font *f, SDL_Rect b)
{
	if (&e->player.stat == e->currstat)
		sdl_int_put((t_ip){r, f, (t_vct2){b.x + 5, b.y + 5}, "Health: ",
		e->currstat->type, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF}});
	else if (ISPROP(e->currstat->type))
	{
		sdl_int_put((t_ip){r, f, (t_vct2){b.x + 5, b.y + 5}, "Type: ",
		e->currstat->type - MINPROPSPOS, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF}});
		sdl_string_put((t_sp){r, f, (t_vct2){b.x + 5, b.y + SBH + 5}, "Delete",
		(SDL_Color){255, 100, 100, 0xFF}});
	}
	else if (ISWALLPROP(e->currstat->type))
	{
		sdl_int_put((t_ip){r, f, (t_vct2){b.x + 5, b.y + 5}, "Type: ",
		e->currstat->type - MINWPROPSPOS, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF}});
		sdl_string_put((t_sp){r, f, (t_vct2){b.x + 5, b.y + SBH + 5}, "Delete",
		(SDL_Color){255, 100, 100, 0xFF}});
	}
	else
	{
		sdl_int_put((t_ip){r, f, (t_vct2){b.x + 5, b.y + 5}, "Type: ",
		e->currstat->type, (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF}});
		sdl_string_put((t_sp){r, f, (t_vct2){b.x + 5, b.y + SBH + 5}, "Delete",
		(SDL_Color){255, 100, 100, 0xFF}});
	}
}

static void	lil_if_mur(SDL_Renderer *r, TTF_Font *f, t_mur *cm, SDL_Rect b)
{
	SDL_RenderDrawLine(r, b.x, b.y + SBH * 5, b.x + b.w, b.y + SBH * 5);
	sdl_string_put((t_sp){r, f, (t_vct2){b.x + 5, b.y + SBH * 5 + 5},
		" Level 0", (cm->level == 0 ? (SDL_Color){255, 255, 200, 0xFF}
		: (SDL_Color){200, 200, 200, 0xFF})});
	sdl_string_put((t_sp){r, f, (t_vct2){b.x + 5, b.y + SBH * 6 + 5},
		" Level 1", (cm->level == 1 ? (SDL_Color){255, 255, 200, 0xFF}
		: (SDL_Color){200, 200, 200, 0xFF})});
	sdl_string_put((t_sp){r, f, (t_vct2){b.x + 5, b.y + SBH * 7 + 5},
		" Level 2", (cm->level == 2 ? (SDL_Color){255, 255, 200, 0xFF}
		: (SDL_Color){200, 200, 200, 0xFF})});
	sdl_string_put((t_sp){r, f, (t_vct2){b.x + 5, b.y + SBH * 8 + 5},
		" Level 3", (cm->level == 3 ? (SDL_Color){255, 255, 200, 0xFF}
		: (SDL_Color){200, 200, 200, 0xFF})});
	SDL_RenderDrawLine(r, b.x, b.y + SBH * 9, b.x + b.w, b.y + SBH * 9);
}

static void	if_mur(SDL_Renderer *r, TTF_Font *f, t_mur *cm, SDL_Rect b)
{
	sdl_string_put((t_sp){r, f, (t_vct2){b.x + 5, b.y + 5}, "Texture:",
		(SDL_Color){0xDD, 0xDD, 0xDD, 0xFF}});
	SDL_RenderCopy(r, cm->txtr, NULL, &(SDL_Rect){b.x + 120, b.y + 4,
		SBH - 2, SBH - 2});
	if (cm->portal_ptr)
	{
		SDL_SetRenderDrawColor(r, 133, 133, 133, 255);
		SDL_RenderDrawLine(r, b.x, b.y + SBH + 5, b.x + b.w, b.y + SBH + 5);
		sdl_string_put((t_sp){r, f, (t_vct2){b.x + 5, b.y + SBH * 1 + 5},
		" Window", (cm->portal_id == WINDOW ? (SDL_Color){255, 255, 200, 0xFF}
			: (SDL_Color){200, 200, 200, 0xFF})});
		sdl_string_put((t_sp){r, f, (t_vct2){b.x + 5, b.y + SBH * 2 + 5},
		" Close Door", (cm->portal_id == CLOSE_DOOR ? (SDL_Color){255, 255, 200,
			0xFF} : (SDL_Color){200, 200, 200, 0xFF})});
		sdl_string_put((t_sp){r, f, (t_vct2){b.x + 5, b.y + SBH * 3 + 5},
		" Open Door", (cm->portal_id == OPEN_DOOR ? (SDL_Color){255, 255, 200,
			0xFF} : (SDL_Color){200, 200, 200, 0xFF})});
		sdl_string_put((t_sp){r, f, (t_vct2){b.x + 5, b.y + SBH * 4 + 5},
		" Portal", (cm->portal_id == PORTAL ? (SDL_Color){255, 255, 200, 0xFF} :
			(SDL_Color){200, 200, 200, 0xFF})});
		lil_if_mur(r, f, cm, b);
	}
	else
		sdl_string_put((t_sp){r, f, (t_vct2){b.x + 5, b.y + SBH * 1 + 5},
			"Add Prop", (SDL_Color){75, 100, 200, 0xFF}});
}

static void	if_secteur(t_editor *editor, SDL_Rect b)
{
	SDL_Rect txtrpos;

	sdl_string_put((t_sp){editor->rend, editor->ui->fonts.s32, (t_vct2){b.x + 5,
		b.y + 5}, "Ceil:", (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF}});
	txtrpos = (SDL_Rect){b.x + 120, b.y + 4, SBH - 2, SBH - 2};
	SDL_RenderCopy(editor->rend, editor->map->top, NULL, &txtrpos);
	sdl_string_put((t_sp){editor->rend, editor->ui->fonts.s32, (t_vct2){b.x + 5,
		b.y + SBH + 5}, "Floor:", (SDL_Color){0xDD, 0xDD, 0xDD, 0xFF}});
	txtrpos = (SDL_Rect){b.x + 120, b.y + SBH + 4, SBH - 2, SBH - 2};
	SDL_RenderCopy(editor->rend, editor->map->sol, NULL, &txtrpos);
	sdl_int_put((t_ip){editor->rend, editor->ui->fonts.s32, (t_vct2){b.x + 5,
	b.y + SBH * 2 + 5}, "Ceil: ", editor->map->htop, (SDL_Color){0xDD, 0xDD,
	0xDD, 0xFF}});
	sdl_int_put((t_ip){editor->rend, editor->ui->fonts.s32, (t_vct2){b.x + 5,
	b.y + SBH * 3 + 5}, "Floor: ", editor->map->hsol, (SDL_Color){0xDD, 0xDD,
	0xDD, 0xFF}});
	if (editor->map->gravity)
		sdl_string_put((t_sp){editor->rend, editor->ui->fonts.s32, (t_vct2){b.x
		+ 5, b.y + SBH * 4 + 5}, "Gravity: Moon", (SDL_Color){0xDD, 0xDD, 0xDD,
		0xFF}});
	else
		sdl_string_put((t_sp){editor->rend, editor->ui->fonts.s32, (t_vct2){b.x
		+ 5, b.y + SBH * 4 + 5}, "Gravity: Earth", (SDL_Color){0xDD, 0xDD, 0xDD,
		0xFF}});
}

void		draw_inspect_menu(t_editor *editor)
{
	SDL_SetRenderDrawColor(editor->rend, 66, 66, 66, 255);
	SDL_RenderFillRect(editor->rend, &editor->optbox);
	if (editor->currstat)
	{
		if_character(editor, editor->rend, editor->ui->fonts.s32,
			editor->optbox);
	}
	else if (editor->currmur)
	{
		if_mur(editor->rend, editor->ui->fonts.s32, editor->currmur,
			editor->optbox);
	}
	else if (editor->map)
	{
		if_secteur(editor, editor->optbox);
	}
	SDL_SetRenderDrawColor(editor->rend, 0, 0, 0, 255);
}
