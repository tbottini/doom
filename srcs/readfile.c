/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:39:35 by magrab            #+#    #+#             */
/*   Updated: 2019/07/10 17:09:52 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	set_txtr(t_txtr *txtr, SDL_Surface *surf)
{
	txtr->pixels = surf->pixels;
	txtr->w = surf->w;
	txtr->h = surf->h;
}

int	read_balise(int fd, char *balise, int ret)
{
	int *x;
	int y;

	x = (int *)balise;
	read(fd, &y, sizeof(y));
	if (*x != y)
		return (ret);
	return (0);
}

int	read_one_texture(int fd, SDL_Surface **surf)
{
	int pathlen;
	char path[512];
	SDL_Surface *tmp;

	if (read(fd, &pathlen, sizeof(int)) != sizeof(int) || pathlen >= 512 || pathlen <= 0)
		return (-23);
	printf("\tString Len: %d\n", pathlen);
	if (read(fd, path, sizeof(char) * (pathlen + 1)) != sizeof(char) * (pathlen + 1))
		return (-24);
	path[pathlen] = '\0';
	printf("\tString : %s\n", path);
	if (!(tmp = IMG_Load(path)))
		return (-25);
	*surf = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA8888, 0);
	SDL_FreeSurface(tmp);
	if (read(fd, path, sizeof(char)) != sizeof(char) || *path != '\v')
		return (-26);
	printf("\tGOOD\n\n");
	return (0);
}

int read_textures(int fd, SDL_Surface ***surf, t_slen *len)
{
	int x;
	int rtn;
	SDL_Surface **localsurf;

	if (read_balise(fd, "🌅", -2))
		return (-2);
	if (read(fd, &len->nb_txtrs, sizeof(int)) != sizeof(int))
		return (-21);
	printf("Found %d Textures\n", len->nb_txtrs);
	if (!(*surf = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * (len->nb_txtrs + 1))))
		return (-420);
	localsurf = *surf;
	ft_bzero(localsurf, sizeof(SDL_Surface *) * (len->nb_txtrs + 1));
	x = 0;
	while (x < len->nb_txtrs)
	{
		if ((rtn = read_one_texture(fd, &(localsurf[x]))))
			return (rtn);
		x++;
	}
	if (read_balise(fd, "🌌", 2))
		return (2);
	return (0);
}

int	read_one_pillar(int fd, t_pillar *pill)
{
	if ((read(fd, &pill->p.x, sizeof(double))) != sizeof(double))
		return (-32);
	if (read(fd, &pill->p.y, sizeof(double)) != sizeof(double))
		return (-33);
	printf("\tNew Pillar at %f\t%f\n", pill->p.x, pill->p.y);
	return (0);
}

int	read_pillars(int fd, t_pillar **pillars, t_slen *len)
{
	int x;
	int rtn;

	if (read_balise(fd, "⛩", -3))
		return (-3);
	if ((read(fd, &len->nb_pills, sizeof(int)) != sizeof(int)) || len->nb_pills < 0)
		return (-31);
	printf("Found %d Pillars\n", len->nb_pills);
	if (!(*pillars = (t_pillar *)malloc(sizeof(t_pillar) * (len->nb_pills + 1))))
		return (-421);
	ft_bzero(*pillars, sizeof(t_pillar) * (len->nb_pills + 1));
	x = 0;
	while (x < len->nb_pills)
	{
		if ((rtn = read_one_pillar(fd, &(((*pillars)[x])))))
			return (rtn);
		x++;
	}
	if (read_balise(fd, "💊", 3))
		return (3);
	return (0);
}

int	read_one_prop(int fd, t_game *game, t_prop *prop, t_slen *len)
{
	int		var_a;
	int		var_b;

	if (read(fd, &prop->type, sizeof(int)) != sizeof(int))
		return (-72);
	printf("\t\tFound Prop type: %d\n", prop->type);
	if ((read(fd, &var_a, sizeof(int)) != sizeof(int)) || var_a >= len->nb_sects)
		return (-73);
	printf("\t\tFound Prop Sector ID: %d\n", var_a);
	prop->sector = &game->sectors[var_a];
	if ((read(fd, &var_b, sizeof(int)) != sizeof(int)) || var_b >= len->nb_sects)
		return (-74);
	if (var_b == -1)
	{
		if ((read(fd, &var_a, sizeof(int)) != sizeof(int)) || var_a != -1)
			return (-79);
	}
	else if ((read(fd, &var_a, sizeof(int)) != sizeof(int)) || var_a >= game->sectors[var_b].len)
		return (-75);
	printf("\t\tFound wall %d in sector %d\n", var_a, var_b);
	prop->wall = &game->sectors[var_b].wall[var_a];
	if ((read(fd, &prop->pos.x, sizeof(double)) != sizeof(double)))
		return (-76);
	if ((read(fd, &prop->pos.y, sizeof(double)) != sizeof(double)))
		return (-77);
	init_prop(prop);
	printf("\t\tSet Wall Prop position %f %f\n", prop->pos.x, prop->pos.y);
	return (0);
}

int	read_wall_props(int fd, t_game *game, t_wall *wall, t_slen *len)
{
	int x;
	int	nbp;
	int rtn;

	if (read_balise(fd, "🖼", -7))
		return (-7);
	if ((read(fd, &nbp, sizeof(int)) != sizeof(int)) || nbp < 0)
		return (-71);
	printf("\t\tFound %d Wall Props\n", nbp);
	if (!(wall->props = (t_prop *)malloc(sizeof(t_prop) * (nbp + 1))))
		return (-427);
	ft_bzero(wall->props, sizeof(t_prop) * (nbp + 1));
	x = 0;
	while (x < nbp)
	{
		if ((rtn = read_one_prop(fd, game, &(wall->props[x]), len)))
			return (rtn);
		x++;
	}
	if (read_balise(fd, "📅", 7))
		return (7);
	return (0);
}

int	read_one_wall(int fd, t_game *game, t_wall *wall, t_slen *len)
{
	int	tmp;

	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_pills))
		return (-61);
	printf("\t\tFound Pillar1 ID: %d\n", tmp);
	wall->pillar = &game->pillars[tmp];
	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_pills))
		return (-62);
	printf("\t\tFound Pillar2 ID: %d\n", tmp);
	wall->next = &game->pillars[tmp];
	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_txtrs))
		return (-63);
	printf("\t\tFound Texture ID: %d\n", tmp);
	set_txtr(&wall->txtr, game->gamesurf[tmp]);
	if (((read(fd, &wall->status, sizeof(t_portal_id)) != sizeof(t_portal_id))))
		return (-64);
	printf("\t\tFound Wall Type: %d\n", tmp);
	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_sects))
		return (-65);
	printf("\t\tFound Wall Sector Link: %d\n", tmp);
	wall->link = &game->sectors[tmp];
	return (read_wall_props(fd, game, wall, len));
}

int	read_sec_walls(int fd, t_game *game, t_sector *sector, t_slen *len)
{
	int x;
	int	nbw;
	int rtn;

	if (read_balise(fd, "💦", -6))
		return (-6);
	if ((read(fd, &nbw, sizeof(int)) != sizeof(int)))
		return (-61);
	printf("\t\tFound %d Walls\n", nbw);
	if (!(sector->wall = (t_wall *)malloc(sizeof(t_wall) * (nbw + 1))))
		return (-423);
	ft_bzero(sector->wall, sizeof(t_wall) * (nbw + 1));
	x = 0;
	while (x < nbw)
	{
		if ((rtn = read_one_wall(fd, game, &(sector->wall[x]), len)))
			return (rtn);
		x++;
	}
	sector->len = nbw;
	if (read_balise(fd, "⛱", -6))
		return (-5);
	return (0);
}

int	read_sec_props(int fd, t_game *game, t_sector *sector, t_slen *len)
{
	int x;
	int	nbp;
	int rtn;

	if (read_balise(fd, "🚽", -8))
		return (-8);
	if ((read(fd, &nbp, sizeof(int)) != sizeof(int)))
		return (-81);
	printf("\tFound %d Props\n", nbp);
	if (!(sector->props = (t_prop *)malloc(sizeof(t_prop) * (nbp + 1))))
		return (-428);
	ft_bzero(sector->props, sizeof(t_prop) * (nbp + 1));
	x = 0;
	while (x < nbp)
	{
		if ((rtn = read_one_prop(fd, game, &(sector->props[x]), len)))
			return (rtn);
		x++;
	}
	if (read_balise(fd, "💩", 8))
		return (8);
	return (0);
}

int	read_one_sector(int fd, t_game *game, t_sector *sector, t_slen *len)
{
	char	ctmp;
	int		itmp;

	if (read(fd, &ctmp, sizeof(char)) != sizeof(char))
		return (-51);
	sector->gravity.z = (ctmp ? G_EARTH : G_MOON);
	printf("\tSector gravit at %d\n", ctmp);
	if (read(fd, &sector->h_floor, sizeof(double)) != sizeof(double))
		return (-52);
	printf("\tSector height from 0 at %f\n", sector->h_floor);
	if (read(fd, &sector->h_ceil, sizeof(double)) != sizeof(double))
		return (-53);
	printf("\tSector ceil at %f\n", sector->h_ceil);
	if (((read(fd, &itmp, sizeof(int)) != sizeof(int)) || itmp >= len->nb_txtrs))
		return (-54);
	set_txtr(&sector->txtrsol, game->gamesurf[itmp]);
	printf("\tSector floor txtr: %d\n", itmp);
	if (((read(fd, &itmp, sizeof(int)) != sizeof(int)) || itmp >= len->nb_txtrs))
		return (-55);
	set_txtr(&sector->txtrtop, game->gamesurf[itmp]);
	printf("\tSector ceil txtr: %d\n", itmp);
	if ((itmp = read_sec_walls(fd, game, sector, len)))
		return (itmp);
	return (read_sec_props(fd, game, sector, len));
}

int	read_sectors(int fd, t_game *game, t_slen *len)
{
	int x;
	int rtn;

	if (read_balise(fd, "🚧", -5))
		return (-5);
	if ((read(fd, &len->nb_sects, sizeof(int)) != sizeof(int)) || len->nb_sects < 0)
		return (-51);
	printf("Found %d sectors\n", len->nb_sects);
	if (!(game->sectors = (t_sector *)malloc(sizeof(t_sector) * (len->nb_sects + 1))))
		return (-422);
	ft_bzero(game->sectors, sizeof(t_sector) * (len->nb_sects + 1));
	x = 0;
	while (x < len->nb_sects)
	{
		if ((rtn = read_one_sector(fd, game, &(game->sectors[x]), len)))
			return (rtn);
		x++;
	}
	if (read_balise(fd, "🏠", 5))
		return (5);
	return (0);
}

int	read_player(int fd, t_game *game, t_player *player, t_slen *len)
{
	int tmp;

	if (read_balise(fd, "🍆", -9))
		return (-9);
	if ((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_sects)
		return (-91);
	printf("Found Player at %d\n", tmp);
	player->stat.sector = &game->sectors[tmp];
	if ((read(fd, &player->stat.health, sizeof(int)) != sizeof(int)))
		return (-92);
	printf("Player Health: %d\n", player->stat.health);
	if ((read(fd, &player->stat.pos.x, sizeof(double)) != sizeof(double)))
		return (-93);
	if ((read(fd, &player->stat.pos.y, sizeof(double)) != sizeof(double)))
		return (-94);
	printf("Player Pos: %f %f\n", player->stat.pos.x, player->stat.pos.y);
	if ((read(fd, &player->stat.rot.y, sizeof(double)) != sizeof(double)))
		return (-95);
	printf("Player Rot: %f\n", player->stat.rot.y);
	if (read_balise(fd, "🍌", 9))
		return (9);
	return (0);
}

int	read_one_enemy(int fd, t_game *game, t_slen *len)
{
	t_enemy *enemy;
	int tmp;

	if ((read(fd, &tmp, sizeof(int)) != sizeof(int)) || !(ISENEMY(tmp)))
		return (-101);
	enemy = enemy_init(tmp);
	printf("\tEnemy type: %d\n", tmp);
	if ((read(fd, &tmp, sizeof(int)) != sizeof(int)))
		return (-102);
	printf("\tEnemy Sector: %d\n", tmp);
	if ((read(fd, &enemy->stat.pos.x, sizeof(double)) != sizeof(double)))
		return (-103);
	if ((read(fd, &enemy->stat.pos.y, sizeof(double)) != sizeof(double)))
		return (-104);
	printf("Enemy Pos: %f %f\n", enemy->stat.pos.x, enemy->stat.pos.y);
	if ((read(fd, &enemy->stat.rot.y, sizeof(double)) != sizeof(double)))
		return (-105);
	printf("Enemy Rot: %f\n", enemy->stat.rot.y);
	if (0 <= tmp && tmp < len->nb_sects)
		pushfront_enemy(&game->sectors[tmp], enemy);
	else
		free(enemy);
	return (0);
}

int	read_enemies(int fd, t_game *game, t_slen *len)
{
	int	x;
	int	rtn;
	int	nbe;

	if (read_balise(fd, "🔪", -10))
		return (-10);
	if ((read(fd, &nbe, sizeof(int)) != sizeof(int)))
		return (-11);
	printf("Found %d enemies\n", nbe);
	x = 0;
	while (x < nbe)
	{
		if ((rtn = read_one_enemy(fd, game, len)))
			return (rtn);
		x++;
	}
	if (read_balise(fd, "🍹", 10))
		return (10);
	return (0);
}

int reading_map(int fd, t_doom *doom, t_slen *len)
{
	long	x;
	long	*tmp;
	int		rtn;

	read(fd, &x, sizeof(x));
	tmp = (long *)"💎🇩🇿🍉💩";
	if (x != *tmp)
		return (1);
	if ((rtn = read_textures(fd, &(doom->game.gamesurf), len)))
		return (rtn);
	if ((rtn = read_pillars(fd, &doom->game.pillars, len)))
		return (rtn);
	if ((rtn = read_sectors(fd, &doom->game, len)))
		return (rtn);
	if ((rtn = read_player(fd, &doom->game, &doom->game.player, len)))
		return (rtn);
	if ((rtn = read_enemies(fd, &doom->game, len)))
		return (rtn);
	read(fd, &x, sizeof(x));
	tmp = (long *)"👨🏻🤠🍑";
	if (x != *tmp)
		return (-1);
	return (0);
}

int	read_file(t_doom *doom, const char *file)
{
	int		fd;
	int		returncode;
	t_slen	len;

	if ((fd = open(file, O_RDONLY | O_NOFOLLOW | O_NONBLOCK)) == -1)
	{
		write(2, "Error opening file\n", 19);
		return (-1);
	}
	if ((returncode = reading_map(fd, doom, &len)))
	{
		ft_printf("Error : %d\n", returncode);
		close(fd);
		return (-1);
	}
	close(fd);
	write(1, "Successfully read ressources/map/editor.map\n", 48);
	return (0);
}
