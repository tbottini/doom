/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:50 by magrab            #+#    #+#             */
/*   Updated: 2019/04/18 21:38:44 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int load_map_btns(t_wolf *wolf)
{
	DIR *maps;
	struct dirent *mapdata;
	char tmp[512];
	int y;

	if (!wolf->sdl.btnmap[0].txture)
		wolf->sdl.btnmap[0] = add_quit_button(wolf, " Return ");
	if (!wolf->sdl.btnmap[1].txture)
		wolf->sdl.btnmap[1] = add_mapmenu_button(wolf);
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
	{
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

int main(int ac, char **av)
{
	t_wolf *wolf;
	(void)ac;
	(void)av;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		ft_printf("SDL_Init: %s\n", SDL_GetError());
		return (-1);
	}
	if (TTF_Init() == -1)
	{
		ft_printf("TTF_Init: %s\n", TTF_GetError());
		return (-1);
	}
	if (!(wolf = wolf_init()))
		return (-1);
	while (0 == 0)
	{
		if (!(event_handler(wolf)))
			return (0);
		loop_hook(wolf);
		printf("pos x : %d\t%d\t%c\t%f\n", (int)wolf->pos.x, (int)wolf->pos.y, wolf->map[(int)wolf->pos.y][(int)wolf->pos.x], wolf->rot);
	}

	return (0);
}
