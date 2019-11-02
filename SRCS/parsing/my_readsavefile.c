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

int			read_one_sector(int fd, t_game *game, t_sector *sector, t_slen *len)
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

int			read_sectors(int fd, t_game *game, t_slen *len)
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

void		write_wall_props(int fd, t_lstent props)
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

static void	lil_relink_sector(t_game *g, t_editor *e, t_mur *mur, t_vct3 id)
{
	t_entity			*ent;

	if (mur->portal_id != WALL)
		mur->portal_ptr = find_secteur(e->sectors, g,
			g->sectors[id.x].wall[id.y].link);
	id.z = 0;
	ent = mur->wproplist;
	while (ent)
	{
		fill_ent(e->sectors, g, ent,
			&g->sectors[id.x].wall[id.y].props[id.z]);
		ent = ent->next;
		id.z++;
	}
}

int			relink_sector(t_game *g, t_editor *e)
{
	t_secteur			*secteur;
	t_mur				*mur;
	t_vct3				id;

	id.x = 0;
	secteur = e->sectors;
	while (secteur)
	{
		id.y = 0;
		mur = secteur->murs;
		while (mur)
		{
			lil_relink_sector(g, e, mur, id);
			mur = mur->next;
			id.y++;
		}
		secteur = secteur->next;
		id.x++;
	}
	return (1);
}
