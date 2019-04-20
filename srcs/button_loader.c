/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:19:51 by magrab            #+#    #+#             */
/*   Updated: 2019/04/19 18:19:52 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				load_map_btns(t_wolf *wolf)
{
	DIR				*maps;
	struct dirent	*mapdata;
	char			tmp[512];
	int				y;

//	if (!wolf->sdl.btnmap[0].txture)
//		wolf->sdl.btnmap[0] = add_quit_button(wolf, " Return ");
//	if (!wolf->sdl.btnmap[1].txture)
//		wolf->sdl.btnmap[1] = add_mapmenu_button(wolf);
	y = 2;
	if (!(maps = opendir("map")))
	{
		if (wolf->sdl.btnmap[y].txture)
		{
			SDL_DestroyTexture(wolf->sdl.btnmap[y].txture);
			wolf->sdl.btnmap[y].txture = NULL;
			free(wolf->sdl.btnmap[y].data);
		}
		ft_printf("Error loading folder 'map'\n");
		return (0);
	}
	while ((mapdata = readdir(maps)) && y < 9)
		if (mapdata->d_reclen == 32)
		{
			ft_strcpy(tmp, "map/");
			ft_strcpy(&(tmp[4]), mapdata->d_name);
			if (wolf->sdl.btnmap[y].txture)
			{
				SDL_DestroyTexture(wolf->sdl.btnmap[y].txture);
				free(wolf->sdl.btnmap[y].data);
			}
			wolf->sdl.btnmap[y] = add_map_button(wolf, &(tmp[4]));
			wolf->sdl.btnmap[y].data = ft_strdup(tmp);
			y++;
		}
	closedir(maps);
	if (wolf->sdl.btnmap[y].txture)
	{
		SDL_DestroyTexture(wolf->sdl.btnmap[y].txture);
		wolf->sdl.btnmap[y].txture = NULL;
		free(wolf->sdl.btnmap[y].data);
	}
	return (0);
}
