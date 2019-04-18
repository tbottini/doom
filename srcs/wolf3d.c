/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 00:18:50 by magrab            #+#    #+#             */
/*   Updated: 2019/04/18 17:29:15 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void void_wolf(t_wolf *wolf)
{
	wolf->sdl.font = NULL;
	wolf->sdl.rend = NULL;
	wolf->sdl.win = NULL;
}

t_wolf *wolf_init()
{
	t_wolf *wolf;

	if (!(wolf = (t_wolf *)malloc(sizeof(t_wolf))))
		return (NULL);
	void_wolf(wolf);
	if (sdl_start(wolf, "Wolf 3D"))
		return (NULL);

	add_start_button(wolf, 1);
	add_wolf_button(wolf, 0);
	add_opt_button(wolf, 2);
	add_quit_button(wolf, 3);
	wolf->sdl.btnarr[4].txture = NULL;
	wolf->pos.x = 0;
	wolf->pos.y = 0;
	return (wolf);
}

void load_buttons(t_wolf *wolf)
{
	t_btn *tmp;
	int x;
	int y;

	x = -1;
	y = 0;
	while (wolf->sdl.btnarr[++x].txture)
	{
		tmp = &(wolf->sdl.btnarr[x]);
		wolf->sdl.btnarr[x].area.x = wolf->sdl.size.x * (tmp->pos.x / 100); //controls the rect's x coordinate
		wolf->sdl.btnarr[x].area.y = wolf->sdl.size.y * (tmp->pos.y / 100);
		if (tmp->snapx == 1)
			wolf->sdl.btnarr[x].area.x -= tmp->area.w / 2;
		else if (tmp->snapx == 2)
			wolf->sdl.btnarr[x].area.x -= tmp->area.w;
		if (tmp->snapy == 1)
			wolf->sdl.btnarr[x].area.y -= tmp->area.h / 2;
		else if (tmp->snapy == 2)
			wolf->sdl.btnarr[x].area.y -= tmp->area.h;
		else if (tmp->snapy == 3)
			wolf->sdl.btnarr[x].area.y = y + tmp->pos.y;
		y = tmp->area.y + tmp->area.h;
	}
}

void draw_buttons(t_wolf *wolf)
{
	int x;
	x = -1;
	SDL_RenderClear(wolf->sdl.rend);
	while (wolf->sdl.btnarr[++x].txture)
	{
		SDL_RenderCopy(wolf->sdl.rend, wolf->sdl.btnarr[x].txture, NULL, &(wolf->sdl.btnarr[x].area));
	}
	SDL_RenderPresent(wolf->sdl.rend);
}

void test_draw(t_wolf *wolf, char *str, int x, int y)
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

	btntext = TTF_RenderText_Shaded(wolf->sdl.font32, str, tmp.fgcolor, tmp.bgcolor);
	SDL_GetClipRect(btntext, &rect);
	tmp.area.x = x;
	tmp.area.y = y;
	tmp.area.w = rect.w;
	tmp.area.h = rect.h;
	tmp.txture = SDL_CreateTextureFromSurface(wolf->sdl.rend, btntext);
	SDL_RenderCopy(wolf->sdl.rend, tmp.txture, NULL, &(tmp.area));
}

int load_maps(t_wolf *wolf)
{
	DIR *maps;
	struct dirent *mapdata;
	char tmp[1024];
	int y;

	y = 50;
	maps = opendir("map");
	while ((mapdata = readdir(maps)))
	{
		if (mapdata->d_reclen == 32)
		{
			ft_strcpy(tmp, "map/");
			ft_strcpy(&(tmp[4]), mapdata->d_name);
			ft_printf("read : %s\t%d\t%d\n", tmp, mapdata->d_ino, mapdata->d_reclen);
			test_draw(wolf, tmp, wolf->sdl.size.x / 3, y);
			y += 50;
		}
	}
	closedir(maps);
	return (0);
}

void start_btn(t_wolf *wolf)
{
	SDL_RenderClear(wolf->sdl.rend);
	load_maps(wolf);
	SDL_RenderPresent(wolf->sdl.rend);
}

void btn_click(t_wolf *wolf, int x, int y)
{
	int i;
	t_btn tmp;

	i = -1;
	while (wolf->sdl.btnarr[++i].txture)
	{
		tmp = wolf->sdl.btnarr[i];
		if (tmp.area.x <= x && x <= tmp.area.x + tmp.area.w && tmp.area.y <= y && y <= tmp.area.y + tmp.area.h)
		{
			ft_printf("Click on btn %d\n", i);
			if (i == 1)
				start_btn(wolf);
			else if (i == 3)
				prog_quit(wolf);
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
