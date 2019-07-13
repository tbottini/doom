/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:28 by magrab            #+#    #+#             */
/*   Updated: 2019/06/27 16:07:41 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		close_editor(t_doom *doom)
{
	if (doom->edit.ennlist)
		ft_clear_entity_list(&(doom->edit.ennlist));
	if (doom->edit.sectors)
		ft_clear_secteur_list(&(doom->edit.sectors));
	if (doom->edit.pillist)
		ft_clear_pillar_list(&(doom->edit.pillist));
	free_textures_folder(doom->edit.txtrgame, doom->edit.txtrname);
	doom->edit.txtrscroll = 0;
	doom->edit.map = NULL;
	doom->edit.currmur = NULL;
	doom->edit.currstat = NULL;
	doom->edit.currpilier = NULL;
	SDL_HideWindow(doom->edit.win);
	SDL_RaiseWindow(doom->sdl.win);
	doom->edit.status = false;
	return (0);
}

void	open_editor(t_doom *doom)
{
	doom->edit.mappos = (t_vct3){doom->edit.size.x / 2, doom->edit.size.y / 2, 1000};
	load_textures_folder(doom->edit.rend, doom->edit.txtrgame, doom->edit.txtrname);
	doom->edit.sectors = ft_newsector(doom->edit.txtrgame[0], doom->edit.txtrgame[0]);
	doom->edit.map = doom->edit.sectors;
	doom->edit.player.stat.sector = doom->edit.map;
	doom->edit.player.stat.type = 100;
	SDL_ShowWindow(doom->edit.win);
	SDL_RaiseWindow(doom->edit.win);
	doom->edit.status = true;
}

void	editor_free(t_doom *doom)
{
	close_editor(doom);
	if (doom->edit.rend)
		SDL_DestroyRenderer(doom->edit.rend);
	if (doom->edit.win)
		SDL_DestroyWindow(doom->edit.win);
}

void free_textures_folder(SDL_Texture **txtrs, char **txtrsname)
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

int load_textures_folder(SDL_Renderer *rend, SDL_Texture **txtrs, char **txtrsname)
{
	DIR				*txtrfolder;
	struct dirent	*txtrdata;
	int tot;
	char			tmp[512];

	if (!(txtrfolder = opendir("ressources/textures")))
	{
		ft_putstr_fd("Error loading folder 'textures'\n", 2);
		return (0);
	}
	tot = 0;
	ft_strcpy(tmp, "ressources/textures/");
	while ((txtrdata = readdir(txtrfolder)) && tot < MAXTXTRNUMBER)
	{
		if (txtrdata->d_type == 8)
		{
			ft_strcpy(&(tmp[20]), txtrdata->d_name);
			if ((txtrs[tot] = IMG_LoadTexture(rend, tmp)))
				if (!(txtrsname[tot++] = ft_strdup(tmp)))
				{
					SDL_DestroyTexture(txtrs[tot]);
					txtrs[tot] = NULL;
					ft_putstr_fd("Error Adding texture\n", 2);
					closedir(txtrfolder);
					return (0);
				}
		}
	}
	closedir(txtrfolder);
	return (1);
}

int		editor_init(t_editor *editor)
{
	if (!(editor->win = SDL_CreateWindow("Editor", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE)))
		return (0);
	if (!(editor->rend = SDL_CreateRenderer(editor->win, -1, SDL_RENDERER_SOFTWARE)))
		return (0);
	SDL_SetWindowMinimumSize(editor->win, EDITMINWIDTH, EDITMINHEIGHT);
	SDL_GetWindowSize(editor->win, &(editor->size.x), &(editor->size.y));
	//editor->mappos = (t_vct3){editor->size.x / 2, editor->size.y / 2, 1000};
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
	if (!(editor->wsprites[0] = IMG_LoadTexture(editor->rend, PROPBTN)))
		return (0);
	return (1);
}
