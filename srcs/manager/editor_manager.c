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

int		editor_reset(t_editor *edit)
{
	if (edit->ennlist)
		ft_clear_entity_list(&(edit->ennlist));
	if (edit->sectors)
		ft_clear_secteur_list(&(edit->sectors));
	if (edit->pillist)
		ft_clear_pillar_list(&(edit->pillist));
	edit->txtrscroll = 0;
	ft_bzero(edit->txtrreal, sizeof(SDL_Texture *) * MAXTXTRNUMBER);
	edit->map = NULL;
	edit->currmur = NULL;
	edit->currstat = NULL;
	edit->currpilier = NULL;
	return (1);
}

int		close_editor(t_doom *doom)
{
	editor_reset(&doom->edit);
	free_textures_folder(doom->edit.txtrgame, doom->edit.txtrname);
	SDL_HideWindow(doom->edit.win);
	SDL_RaiseWindow(doom->sdl.win);
	doom->edit.status = ED_CLOSED;
	return (0);
}

void	open_editor(t_doom *doom)
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

void	editor_free(t_doom *doom)
{
	close_editor(doom);
	if (doom->edit.rend)
		SDL_DestroyRenderer(doom->edit.rend);
	if (doom->edit.win)
		SDL_DestroyWindow(doom->edit.win);
}

void	free_textures_folder(SDL_Texture **txtrs, char **txtrsname)
{
	int tot;

	tot = 0;
	while (txtrs[tot] && tot < MAXTXTRNUMBER)
	{
		SDL_DestroyTexture(txtrs[tot]);
		txtrs[tot] = NULL;
		tot++;
	}
	tot = 0;
	while (txtrsname[tot] && tot < MAXTXTRNUMBER)
	{
		free(txtrsname[tot]);
		txtrsname[tot] = NULL;
		tot++;
	}
}

int		editor_init(t_editor *editor)
{
	if (!(editor->win = SDL_CreateWindow("Editor", SDL_WINDOWPOS_CENTERED,
										 SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
										 SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE)))
		return (0);
	if (!(editor->rend = SDL_CreateRenderer(editor->win, -1, SDL_RENDERER_SOFTWARE)))
		return (0);
	SDL_SetWindowMinimumSize(editor->win, EDITMINWIDTH, EDITMINHEIGHT);
	SDL_GetWindowSize(editor->win, &(editor->size.x), &(editor->size.y));
	editor->mappos = (t_vct3){editor->size.x / 2, editor->size.y / 2, 1000};
	editor->sectbox.x = -1;
	editor->sectbox.y = -1;
	editor->sectbox.w = 160;
	editor->optbox.w = 200;
	editor->txtrbox.w = 620;
	editor->txtrbox.h = MINHEIGHT - 20;
	if (!(editor->sprites[0] = IMG_LoadTexture(editor->rend, PROPHEALTH)))
		return (0);
	if (!(editor->sprites[1] = IMG_LoadTexture(editor->rend, PROPCASS)))
		return (0);
	if (!(editor->sprites[2] = IMG_LoadTexture(editor->rend, PROPMUN)))
		return (0);
	if (!(editor->sprites[3] = IMG_LoadTexture(editor->rend, PROPRPILL)))
		return (0);
	if (!(editor->sprites[4] = IMG_LoadTexture(editor->rend, PROPGPILL)))
		return (0);
	if (!(editor->sprites[5] = IMG_LoadTexture(editor->rend, PROPBPILL)))
		return (0);
	if (!(editor->sprites[6] = IMG_LoadTexture(editor->rend, PROPJETPACK)))
		return (0);
	if (!(editor->sprites[7] = IMG_LoadTexture(editor->rend, PROPGUN)))
		return (0);
	if (!(editor->sprites[8] = IMG_LoadTexture(editor->rend, PROPSHOTGUN)))
		return (0);
	if (!(editor->sprites[9] = IMG_LoadTexture(editor->rend, PROPRIFLE)))
		return (0);
	if (!(editor->sprites[10] = IMG_LoadTexture(editor->rend, PROPKEY1)))
		return (0);
	if (!(editor->sprites[11] = IMG_LoadTexture(editor->rend, PROPKEY2)))
		return (0);
	if (!(editor->sprites[12] = IMG_LoadTexture(editor->rend, PROPKEY3)))
		return (0);
	if (!(editor->sprites[13] = IMG_LoadTexture(editor->rend, PROPCORE)))
		return (0);
	if (!(editor->wsprites[0] = IMG_LoadTexture(editor->rend, PROPBTN)))
		return (0);
	if (!(editor->wsprites[1] = IMG_LoadTexture(editor->rend, PROPWINBTN)))
		return (0);
	if (!(editor->wsprites[2] = IMG_LoadTexture(editor->rend, PROPIMPACT)))
		return (0);
	if (!(editor->wsprites[3] = IMG_LoadTexture(editor->rend, PROPARROW)))
		return (0);
	if (!(editor->wsprites[4] = IMG_LoadTexture(editor->rend, PROPCROSS)))
		return (0);
	if (!(editor->wsprites[5] = IMG_LoadTexture(editor->rend, PROPEXIT)))
		return (0);
	return (1);
}
