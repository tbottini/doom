/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:39:35 by magrab            #+#    #+#             */
/*   Updated: 2019/08/12 13:49:41 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		read_player(int fd, t_game *game, t_player *player, t_slen *len)
{
	unsigned int tmp;

	if (read_balise(fd, "🍆", -9))
		return (-9);
	if ((read(fd, &tmp, sizeof(int)) != sizeof(int))
			|| tmp >= (unsigned int)len->nb_sects)
		return (-91);
	player->stat.sector = &game->sectors[tmp];
	if ((read(fd, &player->stat.health, sizeof(int)) != sizeof(int)))
		return (-92);
	if ((read(fd, &player->stat.pos.x, sizeof(double)) != sizeof(double)))
		return (-93);
	if ((read(fd, &player->stat.pos.y, sizeof(double)) != sizeof(double)))
		return (-94);
	if ((read(fd, &player->stat.rot.y, sizeof(double)) != sizeof(double)))
		return (-95);
	if (read_balise(fd, "🍌", 9))
		return (9);
	return (0);
}

int		read_one_enemy(int fd, t_game *game, t_slen *len)
{
	t_enemy		*enemy;
	int			tmp;
	int			tmp2;

	if ((read(fd, &tmp2, sizeof(int)) != sizeof(int)) || !(ISENEMY(tmp2)))
		return (-101);
	if ((read(fd, &tmp, sizeof(int)) != sizeof(int)))
		return (-102);
	enemy = enemy_init(tmp2, (int)game->difficulty, &game->sectors[tmp]);
	if ((read(fd, &enemy->stat.pos.x, sizeof(double)) != sizeof(double)))
		return (-103);
	if ((read(fd, &enemy->stat.pos.y, sizeof(double)) != sizeof(double)))
		return (-104);
	if ((read(fd, &enemy->stat.rot.y, sizeof(double)) != sizeof(double)))
		return (-105);
	if (0 <= tmp && tmp < len->nb_sects)
		pushfront_enemy(&game->sectors[tmp], enemy);
	else
		free(enemy);
	return (0);
}

int		read_enemies(int fd, t_game *game, t_slen *len)
{
	int	x;
	int	rtn;
	int	nbe;

	if (read_balise(fd, "🔪", -10))
		return (-10);
	if ((read(fd, &nbe, sizeof(int)) != sizeof(int)))
		return (-11);
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

int		reading_map(int fd, t_game *game, t_slen *len, bool foredit)
{
	long	x;
	long	*tmp;
	int		rtn;

	read(fd, &x, sizeof(x));
	tmp = (long *)"💎🇩🇿🍉💩";
	if (x != *tmp)
		return (1);
	if ((rtn = read_textures(fd, &(game->gamesurf), len,
			(foredit ? &game->surfpath : NULL))))
		return (rtn);
	if ((rtn = read_pillars(fd, &game->pillars, len)))
		return (rtn);
	if ((rtn = read_sectors(fd, game, len)))
		return (rtn);
	if ((rtn = read_player(fd, game, &game->player, len)))
		return (rtn);
	if ((rtn = read_enemies(fd, game, len)))
		return (rtn);
	read(fd, &x, sizeof(x));
	tmp = (long *)"👨🏻🤠🍑";
	if (x != *tmp)
		return (-1);
	return (0);
}

int		read_file(t_game *game, const char *file, bool foredit)
{
	int		fd;
	int		returncode;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(2, "Error opening file\n", 19);
		return (-1);
	}
	if ((returncode = reading_map(fd, game, &game->len, foredit)))
	{
		ft_printf("Error : %d\n", returncode);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
