/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:19:51 by magrab            #+#    #+#             */
/*   Updated: 2019/04/25 19:19:03 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				load_map_btns(t_wolf *wolf)
{
	DIR				*maps;
	struct dirent	*mapdata;
	char			tmp[512];
	int				y;

	y = 2;
	if (!(maps = opendir("map")))
	{
		if (wolf->ui.btnmap[y].txture)
		{
			SDL_DestroyTexture(wolf->ui.btnmap[y].txture);
			wolf->ui.btnmap[y].txture = NULL;
			free(wolf->ui.btnmap[y].data);
		}
		ft_printf("Error loading folder 'map'\n");
		return (0);
	}
	while ((mapdata = readdir(maps)) && y < 9)
	{
		ft_strcpy(tmp, "map/");
		ft_strcpy(&(tmp[4]), mapdata->d_name);
		if (mapdata->d_reclen == 32 && wolf_parseur(wolf, tmp))
		{
			if (wolf->ui.btnmap[y].txture)
			{
				SDL_DestroyTexture(wolf->ui.btnmap[y].txture);
				free(wolf->ui.btnmap[y].data);
			}
			wolf->ui.btnmap[y] = add_map_button(wolf, &(tmp[4]));
			wolf->ui.btnmap[y].data = ft_strdup(tmp);
			y++;
		}
	}
	closedir(maps);
	if (wolf->ui.btnmap[y].txture)
	{
		SDL_DestroyTexture(wolf->ui.btnmap[y].txture);
		wolf->ui.btnmap[y].txture = NULL;
		free(wolf->ui.btnmap[y].data);
	}
	return (0);
}
