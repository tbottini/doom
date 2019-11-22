/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_readfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 06:10:49 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 06:10:50 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int	lil_read_one_prop(int fd, t_game *game, t_prop *prop, t_slen *len)
{
	if ((read(fd, &prop->pos.x, sizeof(double)) != sizeof(double)))
		return (-76);
	if ((read(fd, &prop->pos.y, sizeof(double)) != sizeof(double)))
		return (-77);
	init_prop(prop, game->sectors[len->current_sector].h_floor);
	if (game->ui && MINPROPSPOS <= prop->type && prop->type < MAXPROPSPOS)
		set_txtr(&prop->tex, game->ui->propssurf[prop->type - MINPROPSPOS], 0);
	else if (game->ui && ISWALLPROP(prop->type))
		set_txtr(&prop->tex,
			game->ui->propssurf[prop->type - MINWPROPSPOS + 14], 0);
	return (0);
}

int			read_one_prop(int fd, t_game *game, t_prop *prop, t_slen *len)
{
	int		var_a;
	int		var_b;

	if (read(fd, &prop->type, sizeof(int)) != sizeof(int))
		return (-72);
	if ((read(fd, &var_a, sizeof(int)) != sizeof(int))
			|| var_a >= len->nb_sects)
		return (-73);
	if (var_a == -1)
		prop->sector = NULL;
	else
		prop->sector = &game->sectors[var_a];
	if ((read(fd, &var_b, sizeof(int)) != sizeof(int))
			|| var_b >= len->nb_sects)
		return (-74);
	if (var_b == -1)
	{
		if ((read(fd, &var_a, sizeof(int)) != sizeof(int)) || var_a != -1)
			return (-79);
	}
	else if ((read(fd, &var_a, sizeof(int)) != sizeof(int)))
		return (-75);
	if (var_b != -1 && var_a != -1)
		prop->wall = &game->sectors[var_b].wall[var_a];
	return (lil_read_one_prop(fd, game, prop, len));
}

int			read_wall_props(int fd, t_game *game, t_wall *wall, t_slen *len)
{
	int	x;
	int	nbp;
	int	rtn;

	if (read_balise(fd, "🖼", -7))
		return (-7);
	if ((read(fd, &nbp, sizeof(int)) != sizeof(int)) || nbp < 0)
		return (-71);
	if (!(wall->props = (t_prop *)malloc(sizeof(t_prop) * (nbp + 1))))
		return (-427);
	ft_bzero(wall->props, sizeof(t_prop) * (nbp + 1));
	x = -1;
	while (++x < nbp)
		if ((rtn = read_one_prop(fd, game, &(wall->props[x]), len)))
			return (rtn);
	wall->nb_props = nbp;
	wall->props[nbp].type = MINWPROPSPOS + 2;
	if (game->ui)
		set_txtr(&wall->props[nbp].tex, game->ui->propssurf[16], 0);
	wall->props[nbp].pos.z = -10;
	if (read_balise(fd, "📅", 7))
		return (7);
	return (0);
}

int			read_one_wall(int fd, t_game *game, t_wall *wall, t_slen *len)
{
	int	tmp;

	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_pills))
		return (-61);
	wall->pillar = &game->pillars[tmp];
	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_pills))
		return (-62);
	wall->next = &game->pillars[tmp];
	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_txtrs))
		return (-63);
	if (tmp >= 0)
		set_txtr(&wall->txtr, game->gamesurf[tmp], tmp);
	if (((read(fd, &wall->status, sizeof(t_portal_id)) != sizeof(t_portal_id))))
		return (-64);
	if (((read(fd, &wall->level, sizeof(int)) != sizeof(int))))
		return (-67);
	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_sects))
		return (-65);
	wall->link = &game->sectors[tmp];
	wall->percent = 100.0;
	wall->ots = 0;
	return (read_wall_props(fd, game, wall, len));
}

int			read_sec_walls(int fd, t_game *game, t_sector *sector, t_slen *len)
{
	int x;
	int	nbw;
	int rtn;

	if (read_balise(fd, "💦", -6))
		return (-6);
	if ((read(fd, &nbw, sizeof(int)) != sizeof(int)))
		return (-61);
	if (!(sector->wall = (t_wall *)malloc(sizeof(t_wall) * (nbw))))
		return (-423);
	ft_bzero(sector->wall, sizeof(t_wall) * (nbw));
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
