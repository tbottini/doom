/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_readsavefile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 06:18:41 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 06:18:42 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		read_one_sector(int fd, t_game *game, t_sector *sector, t_slen *len)
{
	char	ctmp;
	int		itmp;

	if (read(fd, &ctmp, sizeof(char)) != sizeof(char))
		return (-51);
	sector->gravity.z = (ctmp ? G_MOON : G_EARTH);
	if (read(fd, &sector->h_floor, sizeof(double)) != sizeof(double))
		return (-52);
	if (read(fd, &sector->h_ceil, sizeof(double)) != sizeof(double))
		return (-53);
	if (((read(fd, &itmp, sizeof(int)) != sizeof(int))
			|| itmp >= len->nb_txtrs))
		return (-54);
	if (itmp >= 0)
		set_txtr(&sector->txtrsol, game->gamesurf[itmp], itmp);
	if (((read(fd, &itmp, sizeof(int)) != sizeof(int))
			|| itmp >= len->nb_txtrs))
		return (-55);
	if (itmp >= 0)
		set_txtr(&sector->txtrtop, game->gamesurf[itmp], itmp);
	if ((itmp = read_sec_walls(fd, game, sector, len)))
		return (itmp);
	return (read_sec_props(fd, game, sector, len));
}

int		read_sectors(int fd, t_game *game, t_slen *len)
{
	int x;
	int rtn;

	if (read_balise(fd, "🚧", -5))
		return (-5);
	if ((read(fd, &len->nb_sects, sizeof(int)) != sizeof(int))
			|| len->nb_sects < 0)
		return (-51);
	if (!(game->sectors = (t_sector *)malloc(sizeof(t_sector)
			* (len->nb_sects + 1))))
		return (-422);
	ft_bzero(game->sectors, sizeof(t_sector) * (len->nb_sects + 1));
	x = 0;
	while (x < len->nb_sects)
	{
		len->current_sector = x;
		if ((rtn = read_one_sector(fd, game, &(game->sectors[x]), len)))
			return (rtn);
		x++;
	}
	if (read_balise(fd, "🏠", 5))
		return (5);
	return (0);
}

void	write_wall_props(int fd, t_lstent props)
{
	t_lstent	tmp;
	int			x;

	write_balise(fd, "🖼");
	tmp = props;
	x = 0;
	while (tmp)
	{
		x++;
		tmp = tmp->next;
	}
	write(fd, &x, sizeof(int));
	tmp = props;
	while (tmp)
	{
		write_one_prop(fd, tmp);
		tmp = tmp->next;
	}
	write_balise(fd, "📅");
}
