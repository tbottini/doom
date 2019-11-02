/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asynchronous_txtr_load.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:03:12 by magrab            #+#    #+#             */
/*   Updated: 2019/08/18 16:03:13 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "screen.h"

static int	if_load_fail(SDL_Texture **txtrs, int tot, DIR *txtrfolder)
{
	SDL_DestroyTexture(txtrs[tot]);
	txtrs[tot] = NULL;
	ft_putstr_fd("Error Adding texture\n", 2);
	closedir(txtrfolder);
	return (0);
}

static int	load_textures_folder(SDL_Renderer *rend, SDL_Texture **txtrs,
	char **txtrsname)
{
	DIR				*txtrfolder;
	struct dirent	*txtrdata;
	int				tot;
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
					return (if_load_fail(txtrs, tot, txtrfolder));
		}
	}
	closedir(txtrfolder);
	return (1);
}

int			asynchronous_txtr_load(void *param)
{
	t_editor *edit;

	edit = param;
	load_textures_folder(edit->rend, edit->txtrgame, edit->txtrname);
	edit->player.stat.sector = push_secteur(&edit->sectors, edit->txtrgame[0],
		edit->txtrgame[0]);
	edit->player.stat.pos = (t_vct2){0, 0};
	edit->player.stat.type = 100;
	edit->map = edit->sectors;
	if (!(edit->player.stat.sector))
		edit->player.stat.sector = edit->map;
	edit->status = ED_LOADED;
	return (0);
}
