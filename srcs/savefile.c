/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savefile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:39:35 by magrab            #+#    #+#             */
/*   Updated: 2019/07/07 15:34:33 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	write_balise(int fd, char *balise)
{
	int x;

	x = (int)balise;
	write(fd, &x, sizeof(int));
}

void	write_pillars(int fd, t_editor *edit, t_slen *len)
{
	t_lstpil nbp;

	write_balise(fd, "⛩");
	nbp = edit->pillist;
	while (nbp)
	{
		len->nb_pillars++;
		nbp = nbp->next;
	}
	write(fd, &len->nb_pillars, sizeof(int));
	nbp = edit->pillist;
	while (nbp)
	{
		write(fd, &nbp->pos.x, sizeof(double));
		write(fd, &nbp->pos.y, sizeof(double));
		nbp = nbp->next;
	}
	write_balise(fd, "💊");
}

void	write_one_prop(int fd, t_lstent prop, t_slen *len)
{
	write(fd, &prop->stat.type, sizeof(int));
	// ID SECTOR
	// ID WALL
	write(fd, &prop->stat.pos.x, sizeof(double));
	write(fd, &prop->stat.pos.y, sizeof(double));
}

void	write_wall_props(int fd, t_lstent props, t_slen *len)
{
	t_lstent tmp;

	write_balise(fd, "🖼");
	tmp = props;
	len->nb_props = 0;
	while (tmp)
	{
		len->nb_props++;
		tmp = tmp->next;
	}
	tmp = props;
	while (tmp)
	{
		write_one_prop(fd, tmp, len);
		tmp = tmp->next;
	}
	write_balise(fd, "📅");
}

void	write_one_wall(int fd, t_lstmur wall, t_slen *len)
{
	//ID PiLLAR START
	//ID PILLAR END
	//ID TEXTURE
	write(fd, &wall->portal_id, sizeof(int)); //Pas sur que ca marche comme ca
	//ID SECTOR
	write_wall_props(fd, wall->wproplist, len);

}

void	write_sec_walls(int fd, t_lstmur wall, t_slen *len)
{
	t_lstmur tmp;
	write_balise(fd, "💦");
	tmp = wall;
	len->nb_walls = 0;
	while (tmp)
	{
		len->nb_walls++;
		tmp = tmp->next;
	}
	write(fd, &len->nb_walls, sizeof(int));
	tmp = wall;
	while (tmp)
	{
		write_one_wall(fd, tmp, len);
		tmp = tmp->next;
	}
	write_balise(fd, "⛱");
}

void	write_one_sector(int fd, t_lstsec sec, t_slen *len)
{
	write(fd, &sec->gravity, sizeof(int));
	write(fd, &sec->hsol, sizeof(int));
	write(fd, &sec->htop, sizeof(int));
	//ID TEXTURE SOL
	//ID TEXTURE PLAFOND
	write_sec_walls(fd, &sec->murs, len);
	//write_sec_props(fd, ?????, len);
	//write_sec_enemys(fd, ?????, len);
}

void	write_sectors(int fd, t_editor *edit, t_slen *len)
{
	t_lstsec sec;

	write_balise(fd, "🚧");
	sec = edit->sectors;
	while (sec)
	{
		len->nb_sectors++;
		sec = sec->next;
	}
	write(fd, &len->nb_sectors, sizeof(int));
	sec = edit->sectors;
	while (sec)
	{
		write_one_sector(fd, sec, len);
		sec = sec->next;
	}
	write_balise(fd, "🏠");
}

int writing_map(int fd, t_editor *edit)
{
	t_slen	len;

	len.nb_textures = 0;
	//write_textures(fd, edit, &len);
	len.nb_pillars = 0;
	write_pillars(fd, edit, &len);
	len.nb_sectors = 0;
	write_sectors(fd, edit, &len);
	return (0);
}

int	save_editor_to_file(t_editor *edit)
{
	int fd;
	long x;

	if ((fd = open("ressources/map/editor.map", O_CREAT | /*O_EXCL |*/ O_WRONLY, 0777 /*S_IRUSR | S_IRGRP| S_IROTH*/)) == -1)
	{
		write(2, "Error writting to ressources/map/editor.map\n", 44);
		return (-1);
	}
	x = (long)"💎🇩🇿🍉💩";
	write(fd, &x, sizeof(long));
	//write_balise(fd, "🌅");
	//writing_map(fd, edit);
	x = (long)"👨🏻🤠🍑";
	write(fd, &x, sizeof(long));
	close(fd);
	write(1, "Successfully wrote to ressources/map/editor.map\n", 48);
	return (0);
}
