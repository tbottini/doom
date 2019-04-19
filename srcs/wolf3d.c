/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:50 by magrab            #+#    #+#             */
/*   Updated: 2019/04/18 21:38:44 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void void_wolf(t_wolf *wolf)
{
	wolf->sdl.font = NULL;
	wolf->sdl.font32 = NULL;
	wolf->sdl.font128 = NULL;
	wolf->sdl.txture = NULL;
	wolf->sdl.rend = NULL;
	wolf->sdl.win = NULL;
	wolf->sdl.btnmap[0].txture = NULL;
	wolf->sdl.btnmap[1].txture = NULL;
	wolf->sdl.btnmap[2].txture = NULL;
}

t_wolf *wolf_init()
{
	t_wolf *wolf;

	if (!(wolf = (t_wolf *)malloc(sizeof(t_wolf))))
		return (NULL);
	void_wolf(wolf);
	if (sdl_start(wolf, "Wolf 3D"))
		return (NULL);

	wolf->sdl.btnarr[0] = add_wolf_button(wolf);
	wolf->sdl.btnarr[1] = add_start_button(wolf);
	wolf->sdl.btnarr[2] = add_opt_button(wolf);
	wolf->sdl.btnarr[3] = add_quit_button(wolf);
	wolf->sdl.btnarr[4].txture = NULL;
	wolf->pos.x = 0;
	wolf->pos.y = 0;
	wolf->fov = 90;
	wolf->rot = 90;
	return (wolf);
}





t_btn add_map_button(t_wolf *wolf, char *str)
{
	SDL_Surface *btntext;
	t_btn tmp;
	SDL_Rect rect;

	tmp.fgcolor.r = 150;
	tmp.fgcolor.g = 150;
	tmp.fgcolor.b = 150;
	tmp.bgcolor.r = 255;
	tmp.bgcolor.g = 255;
	tmp.bgcolor.b = 255;
	tmp.pos.x = 50;
	tmp.snapx = 1;
	tmp.snapy = 3;
	btntext = TTF_RenderText_Shaded(wolf->sdl.font32, str, tmp.fgcolor, tmp.bgcolor);
	SDL_GetClipRect(btntext, &rect);
	tmp.area.w = rect.w;
	tmp.area.h = rect.h;
	tmp.txture = SDL_CreateTextureFromSurface(wolf->sdl.rend, btntext);
	SDL_FreeSurface(btntext);
	return (tmp);
}

int load_maps(t_wolf *wolf)
{
	DIR *maps;
	struct dirent *mapdata;
	char tmp[1024];
	int y;

	if (!wolf->sdl.btnmap[0].txture)
		wolf->sdl.btnmap[0] = add_quit_button(wolf);
	if (!wolf->sdl.btnmap[1].txture)
		wolf->sdl.btnmap[1] = add_mapmenu_button(wolf);
	y = 2;
	if (!(maps = opendir("map")))
		return (-1);
	while ((mapdata = readdir(maps)))
	{
		if (mapdata->d_reclen == 32)
		{
			ft_strcpy(tmp, "map/");
			ft_strcpy(&(tmp[4]), mapdata->d_name);
			//ft_printf("read : %s\t%d\t%d\n", tmp, mapdata->d_ino, mapdata->d_reclen);
			if (wolf->sdl.btnmap[y].txture)
				SDL_DestroyTexture(wolf->sdl.btnmap[y].txture);
			wolf->sdl.btnmap[y] = add_map_button(wolf, tmp);
			y += 1;
		}
	}
	closedir(maps);
	wolf->sdl.btnmap[y].txture = NULL;
	return (0);
}

void start_btn(t_wolf *wolf)
{
	wolf->sdl.m_status = 2;
	if (load_maps(wolf) == -1)
	{
		ft_printf("Error loading folder 'map'\n");
	}
	draw_menu(wolf);
}



void btn_click(t_wolf *wolf, int x, int y)
{
	int i;
	t_btn tmp;

	i = -1;
	if (wolf->sdl.m_status == 1)
	{
		while (wolf->sdl.btnarr[++i].txture)
		{
			tmp = wolf->sdl.btnarr[i];
			if (tmp.area.x <= x && x <= tmp.area.x + tmp.area.w && tmp.area.y <= y && y <= tmp.area.y + tmp.area.h)
			{
				ft_printf("Click on btn %d\n", i);
				if (i == 1)
				{
					start_btn(wolf);
				}
				else if (i == 3)
					prog_quit(wolf);
			}
		}
	}
	else if (wolf->sdl.m_status == 2)
	{
		while (wolf->sdl.btnmap[++i].txture)
		{
			//ft_printf("LoadBTN\n");
			tmp = wolf->sdl.btnmap[i];
			if (tmp.area.x <= x && x <= tmp.area.x + tmp.area.w && tmp.area.y <= y && y <= tmp.area.y + tmp.area.h)
			{
				ft_printf("MapClick on btn %d\n", i);
				if (i == 0)
				{
					wolf->sdl.m_status = 1;
					draw_menu(wolf);
				}
				/*	if (i == 1)
					start_btn(wolf);
				else if (i == 3)
					prog_quit(wolf);
			*/
			}
		}
	}
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
	//if (!wolf_parseur(ac, av, wolf))
	//{
	//	ft_putendl("error");
	//	return (0);
	//}
	while (0 == 0)
	{
		if (!(event_handler(wolf)))
			return (0);
	}

	return (0);
}
