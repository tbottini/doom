/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savefile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:39:35 by magrab            #+#    #+#             */
/*   Updated: 2019/07/07 21:05:01 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#define EDITORSTEP 100.0

void	write_balise(int fd, char *balise)
{
	int x;

	x = (int)balise;
	write(fd, &x, sizeof(int));
}

void	write_pillars(int fd, t_editor *edit)
{
	t_lstpil	nbp;
	double		tmp;
	int			nb_pillars;

	write_balise(fd, "⛩");
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
		tmp = (double)nbp->pos.x / EDITORSTEP;
		write(fd, &tmp, sizeof(double));
		tmp = (double)nbp->pos.y / EDITORSTEP;
		write(fd, &tmp, sizeof(double));
		nbp = nbp->next;
	}
	write_balise(fd, "💊");
}

void	write_one_prop(int fd, t_entity *prop)
{
	write(fd, &prop->stat.type, sizeof(int));
	write(fd, &prop->stat.sector->id, sizeof(int));
	write(fd, &prop->stat.mur->id, sizeof(int));
	write(fd, &prop->stat.pos.x, sizeof(double));
	write(fd, &prop->stat.pos.y, sizeof(double));
}

void	write_wall_props(int fd, t_lstent props)
{
	t_lstent tmp;
	int x;

	write_balise(fd, "🖼");
	tmp = props;
	x = 0;
	while (tmp)
	{
		x++;
		tmp = tmp->next;
	}
	tmp = props;
	while (tmp)
	{
		write_one_prop(fd, tmp);
		tmp = tmp->next;
	}
	write_balise(fd, "📅");
}

void	write_one_wall(int fd, int idsec, t_lstmur wall)
{
	write(fd, &wall->pil1->id, sizeof(int));
	write(fd, &wall->pil2->id, sizeof(int));
	write(fd, &wall->idtxtr, sizeof(int));
	write(fd, &wall->portal_id, sizeof(t_portal_id));
	write(fd, &idsec, sizeof(int));
	write_wall_props(fd, wall->wproplist);
}

void	write_sec_walls(int fd, int idsec, t_lstmur wall)
{
	t_lstmur tmp;
	int x;
	
	write_balise(fd, "💦");
	tmp = wall;
	x = 0;
	while (tmp)
	{
		tmp->id = x;
		x++;
		tmp = tmp->next;
	}
	write(fd, &x, sizeof(int));
	tmp = wall;
	while (tmp)
	{
		write_one_wall(fd, idsec, tmp);
		tmp = tmp->next;
	}
	write_balise(fd, "⛱");
}

void	write_sec_props(int fd, t_secteur *sect, t_lstent props)
{
	int			c;
	t_lstent	tmp;

	write_balise(fd, "🚽");
	c = 0;
	tmp = props;
	while (tmp)
	{
		if (tmp->stat.sector == sect && !(ISENEMY(tmp->stat.type)))
			c++;
		tmp = tmp->next;
	}
	write(fd, &c, sizeof(int));
	tmp = props;
	while (tmp)
	{
		if (tmp->stat.sector == sect && !(ISENEMY(tmp->stat.type)))
			write_one_prop(fd, tmp);
		tmp = tmp->next;
	}
	write_balise(fd, "💩");
}

void	write_one_sector(int fd, t_secteur *sec, t_lstent props)
{
	write(fd, &sec->gravity, sizeof(char));
	write(fd, &sec->hsol, sizeof(int));
	write(fd, &sec->htop, sizeof(int));
	write(fd, &sec->idsol, sizeof(int));
	write(fd, &sec->idtop, sizeof(int));
	write_sec_walls(fd, sec->id, &sec->murs);
	write_sec_props(fd, sec, props);
}

void	write_sectors(int fd, t_editor *edit)
{
	t_secteur *sec;
	int nbsectors;

	write_balise(fd, "🚧");
	nbsectors = 0;
	sec = edit->sectors;
	while (sec)
	{
		sec->id = nbsectors;
		nbsectors++;
		sec = sec->next;
	}
	write(fd, &nbsectors, sizeof(int));
	sec = edit->sectors;
	while (sec)
	{
		write_one_sector(fd, sec, edit->ennlist);
		sec = sec->next;
	}
	write_balise(fd, "🏠");
}

int		push_texture(t_editor *edit, SDL_Texture *txtr)
{
	int x;

	x = 0;
	while (x < MAXTXTRNUMBER && edit->txtrreal[x])
	{
		if (edit->txtrreal[x] == txtr)
			return (x);
		x++;
	}
	if (x < MAXTXTRNUMBER && !(edit->txtrreal[x]))
	{
		edit->txtrreal[x] = txtr;
		return (x);
	}
	return (-1);
}

void	load_used_textures(t_editor *edit)
{
	t_lstsec currsec;
	t_lstmur currwall;

	currsec = edit->sectors;
	while (currsec)
	{
		currsec->idtop = push_texture(edit, currsec->top);
		currsec->idsol = push_texture(edit, currsec->sol);
		currwall = currsec->murs;
		while (currwall)
		{
			currwall->idtxtr = push_texture(edit, currwall->txtr);
			currwall = currwall->next;
		}
		currsec = currsec->next;
	}
}

char	*get_path(t_editor *edit, SDL_Texture *txtr)
{
	int x;

	x = 0;
	while (x < MAXTXTRNUMBER && edit->txtrgame[x])
	{
		if (edit->txtrgame[x] == txtr)
			return (edit->txtrname[x]);
		x++;
	}
	return (NULL);
}

void	write_one_texture(int fd, t_editor *edit, SDL_Texture *txtr)
{
	char *path;

	path = get_path(edit, txtr);
	write(fd, path, sizeof(char) * ft_strlen(path));
	write(fd, "\v", sizeof(char));
}

void	write_textures(int fd, t_editor *edit)
{
	int i;
	int nb_textures;

	load_used_textures(edit);
	write_balise(fd, "🌅");
	while (nb_textures < MAXTXTRNUMBER && edit->txtrreal[nb_textures])
		nb_textures++;
	write(fd, &nb_textures, sizeof(int));
	i = 0;
	while (i < nb_textures)
	{
		write_one_texture(fd, edit, edit->txtrreal[i]);
		i++;
	}
	write_balise(fd, "🌌");
}

void	write_one_enemy(int fd, t_entity *enn)
{
	double tmp;

	write(fd, &enn->stat.type, sizeof(int));
	write(fd, &enn->stat.sector->id, sizeof(int));
	tmp = (double)(enn->stat.pos.x / EDITORSTEP);
	write(fd, &tmp, sizeof(double));
	tmp = (double)(enn->stat.pos.y / EDITORSTEP);
	write(fd, &tmp, sizeof(double));
	tmp = enn->stat.roty / EDITORSTEP;
	write(fd, &tmp, sizeof(double));
}

void	write_enemies(int fd, t_lstent enn)
{
	t_lstent	tmp;
	int			c;

	tmp = enn;
	while (tmp)
	{
		if (ISENEMY(tmp->stat.type))
			c++;
		tmp = tmp->next;
	}
	write_balise(fd, "🔪");
	write(fd, &c, sizeof(int));
	tmp = enn;
	while (tmp)
	{
		if (ISENEMY(tmp->stat.type))
			write_one_enemy(fd, tmp);
		tmp = tmp->next;
	}
	write_balise(fd, "🍹");
}

int writing_map(int fd, t_editor *edit)
{
	write_textures(fd, edit);
	write_pillars(fd, edit);
	write_sectors(fd, edit);
	write_enemies(fd, edit->ennlist);
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
	writing_map(fd, edit);
	x = (long)"👨🏻🤠🍑";
	write(fd, &x, sizeof(long));
	close(fd);
	write(1, "Successfully wrote to ressources/map/editor.map\n", 48);
	return (0);
}
