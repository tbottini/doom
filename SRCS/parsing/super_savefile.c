/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_savefile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 05:19:40 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 05:19:41 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#define EDITORSTEPX 100.0
#define EDITORSTEPY -100.0
#define CACATRIGO -90.0

void	write_pillars(int fd, t_editor *edit)
{
	t_lstpil	nbp;
	double		tmp;
	int			nb_pillars;

	write_balise(fd, "⛩");
	nb_pillars = 0;
	nbp = edit->pillist;
	while (nbp)
	{
		nbp->id = nb_pillars;
		nb_pillars++;
		nbp = nbp->next;
	}
	write(fd, &nb_pillars, sizeof(int));
	nbp = edit->pillist;
	while (nbp)
	{
		tmp = (double)nbp->pos.x / EDITORSTEPX;
		write(fd, &tmp, sizeof(double));
		tmp = (double)nbp->pos.y / EDITORSTEPY;
		write(fd, &tmp, sizeof(double));
		nbp = nbp->next;
	}
	write_balise(fd, "💊");
}

void	write_one_prop(int fd, t_entity *prop)
{
	double	pos;

	write(fd, &prop->stat.type, sizeof(int));
	if (prop->stat.sector)
		write(fd, &prop->stat.sector->id, sizeof(int));
	else
		write(fd, "\xff\xff\xff\xff", sizeof(int));
	if (prop->stat.mur && prop->stat.mursec)
	{
		write(fd, &prop->stat.mursec->id, sizeof(int));
		write(fd, &prop->stat.mur->id, sizeof(int));
	}
	else
	{
		write(fd, "\xff\xff\xff\xff", sizeof(int));
		write(fd, "\xff\xff\xff\xff", sizeof(int));
	}
	pos = (double)prop->stat.pos.x / EDITORSTEPX;
	write(fd, &pos, sizeof(double));
	pos = (double)prop->stat.pos.y / EDITORSTEPY;
	write(fd, &pos, sizeof(double));
}

void	write_one_sector(int fd, t_secteur *sec, t_lstent props)
{
	double tmp;

	write(fd, &sec->gravity, sizeof(char));
	tmp = sec->hsol / EDITORSTEPX;
	write(fd, &tmp, sizeof(double));
	tmp = sec->htop / EDITORSTEPX;
	write(fd, &tmp, sizeof(double));
	write(fd, &sec->idsol, sizeof(int));
	write(fd, &sec->idtop, sizeof(int));
	write_sec_walls(fd, sec->murs);
	write_sec_props(fd, sec, props);
}

void	write_one_enemy(int fd, t_entity *enn)
{
	double	tmp;

	write(fd, &enn->stat.type, sizeof(int));
	if (enn->stat.sector)
		write(fd, &enn->stat.sector->id, sizeof(int));
	else
		write(fd, "\xff\xff\xff\xff", sizeof(int));
	tmp = (double)(enn->stat.pos.x / EDITORSTEPX);
	write(fd, &tmp, sizeof(double));
	tmp = (double)(enn->stat.pos.y / EDITORSTEPY);
	write(fd, &tmp, sizeof(double));
	tmp = (double)(enn->stat.roty + CACATRIGO);
	write(fd, &tmp, sizeof(double));
}

void	write_player(int fd, t_eplayer *player)
{
	double	tmp;

	write_balise(fd, "🍆");
	if (player->stat.sector)
		write(fd, &player->stat.sector->id, sizeof(int));
	else
		write(fd, "\xff\xff\xff\xff", sizeof(int));
	write(fd, &player->stat.type, sizeof(int));
	tmp = (double)(player->stat.pos.x / EDITORSTEPX);
	write(fd, &tmp, sizeof(double));
	tmp = (double)(player->stat.pos.y / EDITORSTEPY);
	write(fd, &tmp, sizeof(double));
	tmp = (double)(player->stat.roty + CACATRIGO);
	write(fd, &tmp, sizeof(double));
	write_balise(fd, "🍌");
}
