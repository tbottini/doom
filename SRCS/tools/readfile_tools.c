/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 05:51:49 by magrab            #+#    #+#             */
/*   Updated: 2019/08/26 23:02:37 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int			read_balise(int fd, char *balise, int ret)
{
	int *x;
	int y;

	x = (int *)balise;
	read(fd, &y, sizeof(y));
	if (*x != y)
		return (ret);
	return (0);
}

void		set_txtr(t_txtr *txtr, SDL_Surface *surf, int id)
{
	txtr->pixels = surf->pixels;
	txtr->w = surf->w;
	txtr->h = surf->h;
	txtr->id = id;
}

static void	free_gamesurf(SDL_Surface ***gamesurf, char ***gamepath)
{
	SDL_Surface	**tmp;
	char		**tmpath;
	int			x;

	tmp = *gamesurf;
	tmpath = (gamepath ? *gamepath : NULL);
	x = 0;
	while (tmp[x])
	{
		SDL_FreeSurface(tmp[x]);
		if (tmpath)
			free(tmpath[x]);
		x++;
	}
	free(tmp);
	if (tmpath)
	{
		free(tmpath);
		*gamepath = NULL;
	}
	*gamesurf = NULL;
}

static void	free_sectors(t_sector **sectors, int sec_len)
{
	int			x;
	int			y;
	t_sector	*tmp;

	x = 0;
	tmp = *sectors;
	while (x < sec_len)
	{
		y = 0;
		while (y < tmp[x].len)
		{
			free(tmp[x].wall[y].props);
			y++;
		}
		free(tmp[x].wall);
		free(tmp[x].props);
		free_enemys(tmp[x].enemys);
		x++;
	}
	free(tmp);
	*sectors = NULL;
}

void		free_game(t_game *game)
{
	if (game->gamesurf)
	{
		free_gamesurf(&game->gamesurf, (game->surfpath
			? &game->surfpath : NULL));
	}
	if (game->pillars)
	{
		free(game->pillars);
		game->pillars = NULL;
	}
	if (game->sectors)
		free_sectors(&game->sectors, game->len.nb_sects);
	game->len.nb_sects = 0;
	game->len.nb_pills = 0;
	game->len.nb_txtrs = 0;
}
