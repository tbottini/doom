/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/08/12 15:46:26 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "screen.h"

int			close_editor(t_doom *doom)
{
	editor_reset(&doom->edit);
	free_textures_folder(doom->edit.txtrgame, doom->edit.txtrname);
	SDL_HideWindow(doom->edit.win);
	SDL_RaiseWindow(doom->sdl.win);
	doom->edit.status = ED_CLOSED;
	return (0);
}

void		open_editor(t_doom *doom)
{
	if ((SDL_GetWindowFlags(doom->edit.win) & SDL_WINDOW_HIDDEN) != 8)
	{
		SDL_RaiseWindow(doom->edit.win);
		return ;
	}
	doom->edit.status = ED_LOADING;
	asynchronous_txtr_load(&doom->edit);
	doom->edit.mappos = (t_vct3){doom->edit.size.x / 2, doom->edit.size.y / 2,
		1000};
	SDL_ShowWindow(doom->edit.win);
	SDL_RaiseWindow(doom->edit.win);
}

void		editor_free(t_doom *doom)
{
	close_editor(doom);
	if (doom->edit.rend)
		SDL_DestroyRenderer(doom->edit.rend);
	if (doom->edit.win)
		SDL_DestroyWindow(doom->edit.win);
}

static int	load_sprites(t_editor *editor)
{
	if (!(editor->sprites[0] = IMG_LoadTexture(editor->rend, PROPHEALTH))
		|| !(editor->sprites[1] = IMG_LoadTexture(editor->rend, PROPCASS))
		|| !(editor->sprites[2] = IMG_LoadTexture(editor->rend, PROPMUN))
		|| !(editor->sprites[3] = IMG_LoadTexture(editor->rend, PROPRPILL))
		|| !(editor->sprites[4] = IMG_LoadTexture(editor->rend, PROPGPILL))
		|| !(editor->sprites[5] = IMG_LoadTexture(editor->rend, PROPBPILL))
		|| !(editor->sprites[6] = IMG_LoadTexture(editor->rend, PROPJETPACK))
		|| !(editor->sprites[7] = IMG_LoadTexture(editor->rend, PROPGUN))
		|| !(editor->sprites[8] = IMG_LoadTexture(editor->rend, PROPSHOTGUN))
		|| !(editor->sprites[9] = IMG_LoadTexture(editor->rend, PROPRIFLE))
		|| !(editor->sprites[10] = IMG_LoadTexture(editor->rend, PROPKEY1))
		|| !(editor->sprites[11] = IMG_LoadTexture(editor->rend, PROPKEY2))
		|| !(editor->sprites[12] = IMG_LoadTexture(editor->rend, PROPKEY3))
		|| !(editor->sprites[13] = IMG_LoadTexture(editor->rend, PROPCORE))
		|| !(editor->wsprites[0] = IMG_LoadTexture(editor->rend, PROPBTN))
		|| !(editor->wsprites[1] = IMG_LoadTexture(editor->rend, PROPWINBTN))
		|| !(editor->wsprites[2] = IMG_LoadTexture(editor->rend, PROPIMPACT))
		|| !(editor->wsprites[3] = IMG_LoadTexture(editor->rend, PROPARROW))
		|| !(editor->wsprites[4] = IMG_LoadTexture(editor->rend, PROPCROSS))
		|| !(editor->wsprites[5] = IMG_LoadTexture(editor->rend, PROPEXIT)))
		return (0);
	return (1);
}

int			editor_init(t_editor *editor)
{
	if (!(editor->win = SDL_CreateWindow("Editor", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
			SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE)))
		return (0);
	if (!(editor->rend = SDL_CreateRenderer(editor->win, -1, 1)))
		return (0);
	SDL_SetWindowMinimumSize(editor->win, EDITMINWIDTH, EDITMINHEIGHT);
	SDL_GetWindowSize(editor->win, &(editor->size.x), &(editor->size.y));
	editor->mappos = (t_vct3){editor->size.x / 2, editor->size.y / 2, 1000};
	editor->sectbox = (SDL_Rect){-1, -1, 160, 100};
	editor->optbox.w = 200;
	editor->txtrbox.w = TXTRSIZE * NBTXTRBYLINE + (NBTXTRBYLINE - 1) * 5 + 10;
	editor->txtrbox.h = MINHEIGHT - 20;
	if (!(load_sprites(editor)))
		return (0);
	return (1);
}
