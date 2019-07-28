/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:19:51 by magrab            #+#    #+#             */
/*   Updated: 2019/07/19 12:24:14 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void		free_btnmap(t_doom *doom, int y)
{
	SDL_DestroyTexture(doom->ui.btnmap[y].txture);
	doom->ui.btnmap[y].txture = NULL;
	free(doom->ui.btnmap[y].data);
}

static int		read_directory(t_doom *doom, DIR *maps, int y)
{
	struct dirent	*mapdata;
	char			tmp[512];

	ft_printf("Reading\n");
	while ((mapdata = readdir(maps)) && y < 100)
	{
		ft_strcpy(tmp, "ressources/map/");
		ft_strcpy(&(tmp[15]), mapdata->d_name);
		if (mapdata->d_type == 8 && check_file(tmp))
		{
			if (doom->ui.btnmap[y].txture)
				free_btnmap(doom, y);
			doom->ui.btnmap[y] = add_map_button(doom, &(tmp[15]));
			doom->ui.btnmap[y].data = ft_strdup(tmp);
			y++;
		}
	}
	return (y);
}

int				load_map_btns(t_doom *doom)
{
	DIR				*maps;
	int				y;

	y = 2;
	if (!(maps = opendir("ressources/map")))
	{
		if (doom->ui.btnmap[y].txture)
			free_btnmap(doom, y);
		ft_printf("Error loading folder 'map'\n");
		return (0);
	}
	y = read_directory(doom, maps, y);
	closedir(maps);
	if (doom->ui.btnmap[y].txture)
		free_btnmap(doom, y);
	return (0);
}
