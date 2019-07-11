/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savefile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:39:35 by magrab            #+#    #+#             */
/*   Updated: 2019/07/09 18:40:34 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#define EDITORSTEP 100.0

void	write_balise(int fd, char *balise)
{
	int *x;

	x = (int *)balise;
	if (*x == -2054381584 || *x == -1936941072 || *x == 11115490 || *x == -1970102288 || *x == -1483038736 || *x == -1601200144 || *x == -1433100304 || *x == -1181900816)
		printf("Writing %s:\n", balise);
	else if (*x == -1500340240 || *x == 11639778 || *x == -1113939984 || *x == -1450008592)
		printf("\tWriting %s:\n", balise);
	else if (*x == -1130979344 || *x == -2053922832)
		printf("\t\tWriting %s:\n", balise);
	else
		printf("Writing %d %s:\n", *x, balise);
	if (*x == -1936941072 || *x == -1970102288 || *x == 11639778 || *x == -2053922832 || *x == -1601200144 || *x == -1181900816)
		printf("\n");
	write(fd, x, sizeof(int));
}

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
	printf("Found %d Pillars\n", nb_pillars);
	write(fd, &nb_pillars, sizeof(int));
	nbp = edit->pillist;
	while (nbp)
	{
		tmp = (double)nbp->pos.x / EDITORSTEP;
		write(fd, &tmp, sizeof(double));
		printf("\tNew Pillars at %f", tmp);
		tmp = (double)nbp->pos.y / EDITORSTEP;
		printf("\t%f\n", tmp);
		write(fd, &tmp, sizeof(double));
		nbp = nbp->next;
	}
	write_balise(fd, "💊");
}

void	write_one_prop(int fd, t_entity *prop)
{
	double	pos;

	printf("\t\t\tProp type: %d\n", prop->stat.type);
	write(fd, &prop->stat.type, sizeof(int));
	if (prop->stat.sector)
	{
		printf("\t\t\tSector ID: %d\n", prop->stat.sector->id);
		write(fd, &prop->stat.sector->id, sizeof(int));
	}
	else
	{
		printf("\t\t\tSector ID: null\n");
		write(fd, "\xff\xff\xff\xff", sizeof(int));
	}
	if (prop->stat.mur && prop->stat.mursec)
	{
		printf("\t\t\tWall Sector ID: %d\n", prop->stat.mursec->id);
		printf("\t\t\tWall ID: %d\n", prop->stat.mur->id);
		write(fd, &prop->stat.mursec->id, sizeof(int));
		write(fd, &prop->stat.mur->id, sizeof(int));
	}
	else
	{
		printf("\t\t\tWall Sector ID: null\n");
		printf("\t\t\tWall ID: null\n");
		write(fd, "\xff\xff\xff\xff", sizeof(int));
		write(fd, "\xff\xff\xff\xff", sizeof(int));
	}
	pos = (double)prop->stat.pos.x / EDITORSTEP;
	printf("\t\t\tPosition: %f", pos);
	write(fd, &pos, sizeof(double));
	pos = (double)prop->stat.pos.y / EDITORSTEP;
	printf("\t%f\n", pos);
	write(fd, &pos, sizeof(double));
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
	printf("\t\tFound %d wall props\n", x);
	write(fd, &x, sizeof(int));
	tmp = props;
	while (tmp)
	{
		write_one_prop(fd, tmp);
		tmp = tmp->next;
	}
	write_balise(fd, "📅");
}

void	write_one_wall(int fd, t_lstmur wall)
{
	printf("\t\tID Pillar 1: %d\n", wall->pil1->id);
	write(fd, &wall->pil1->id, sizeof(int));
	printf("\t\tID Pillar 2: %d\n", wall->pil2->id);
	write(fd, &wall->pil2->id, sizeof(int));
	printf("\t\tID Texture: %d\n", wall->idtxtr);
	write(fd, &wall->idtxtr, sizeof(int));
	printf("\t\tID Portal Type: %d\n", wall->portal_id);
	write(fd, &wall->portal_id, sizeof(t_portal_id));
	if (wall->portal_ptr)
	{
		printf("\t\tID Sector: %d\n", wall->portal_ptr->id);
		write(fd, &wall->portal_ptr->id, sizeof(int));
	}
	else
	{
		printf("\t\tID Sector: null\n");
		write(fd, "\xff\xff\xff\xff", sizeof(int));
	}
	write_wall_props(fd, wall->wproplist);
}

void	write_sec_walls(int fd, t_lstmur wall)
{
	t_lstmur tmp;
	int nbwalls;
	
	write_balise(fd, "💦");
	tmp = wall;
	nbwalls = 0;
	while (tmp)
	{
		tmp->id = nbwalls;
		nbwalls++;
		tmp = tmp->next;
	}
	printf("\tFound %d walls\n", nbwalls);
	write(fd, &nbwalls, sizeof(int));
	tmp = wall;
	while (tmp)
	{
		write_one_wall(fd, tmp);
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
	printf("\t\tFound %d props\n", c);
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
	double tmp;

	printf("\tGravity: %d\n", (int)sec->gravity);
	write(fd, &sec->gravity, sizeof(char));
	tmp = sec->hsol / EDITORSTEP;
	printf("\tHauteur Sol: %f\n", tmp);
	write(fd, &tmp, sizeof(double));
	tmp = sec->htop / EDITORSTEP;
	printf("\tHauteur Plafond: %f\n", tmp);
	write(fd, &tmp, sizeof(double));
	printf("\tID Image sol: %d\n", sec->idsol);
	write(fd, &sec->idsol, sizeof(int));
	printf("\tID Image plafond: %d\n", sec->idtop);
	write(fd, &sec->idtop, sizeof(int));
	write_sec_walls(fd, sec->murs);
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
	printf("Found %d Sectors\n", nbsectors);
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
		{
			return (x);
		}
		x++;
	}
	if (x < MAXTXTRNUMBER && !(edit->txtrreal[x]))
	{
		edit->txtrreal[x] = txtr;
		return (x);
	}
	printf("\tError Adding Texture: %d\n", x);
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
	int	pathlen;

	path = get_path(edit, txtr);
	pathlen = ft_strlen(path);
	printf("\tWrote path(%d): %s\n", pathlen, path);
	write(fd, &pathlen, sizeof(int));
	write(fd, path, sizeof(char) * (pathlen + 1));
	write(fd, "\v", sizeof(char));
}

void	write_textures(int fd, t_editor *edit)
{
	int i;
	int nb_textures;

	write_balise(fd, "🌅");
	load_used_textures(edit);
	nb_textures = 0;
	while (nb_textures < MAXTXTRNUMBER && edit->txtrreal[nb_textures])
		nb_textures++;
	printf("\t Found %d Textures\n", nb_textures);
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

	printf("\t\tEnemy type: %d\n", enn->stat.type);
	write(fd, &enn->stat.type, sizeof(int));
	if (enn->stat.sector)
	{
		printf("\t\tEnemy Sector ID: %d\n", enn->stat.sector->id);
		write(fd, &enn->stat.sector->id, sizeof(int));
	}
	else
	{
		printf("\t\tEnemy Sector ID: null\n");
		write(fd, "\xff\xff\xff\xff", sizeof(int));
	}
	tmp = (double)(enn->stat.pos.x / EDITORSTEP);
	write(fd, &tmp, sizeof(double));
	printf("\t\tEnemy pos: %f", tmp);
	tmp = (double)(enn->stat.pos.y / EDITORSTEP);
	write(fd, &tmp, sizeof(double));
	printf("\t%f", tmp);
	write(fd, &enn->stat.roty, sizeof(double));
	printf("\trot: %f\n", enn->stat.roty);
	printf("\n");
}

void	write_enemies(int fd, t_lstent enn)
{
	t_lstent	tmp;
	int			c;

	write_balise(fd, "🔪");
	c = 0;
	tmp = enn;
	while (tmp)
	{
		if (ISENEMY(tmp->stat.type))
			c++;
		tmp = tmp->next;
	}
	printf("\tFound %d Enemies\n", c);
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

void	write_player(int fd, t_eplayer *player)
{
	double tmp;

	write_balise(fd , "🍆");
	if (player->stat.sector)
	{
		printf("\t\tplayer Sector ID: %d\n", player->stat.sector->id);
		write(fd, &player->stat.sector->id, sizeof(int));
	}
	else
	{
		printf("\t\tplayer Sector ID: null\n");
		write(fd, "\xff\xff\xff\xff", sizeof(int));
	}
	printf("\t\tplayer HP: %d\n", player->stat.type);
	write(fd, &player->stat.type, sizeof(int));

	tmp = (double)(player->stat.pos.x / EDITORSTEP);
	write(fd, &tmp, sizeof(double));
	printf("\t\tplayer pos: %f\t", tmp);

	tmp = (double)(player->stat.pos.y / EDITORSTEP);
	write(fd, &tmp, sizeof(double));
	printf("%f\n", tmp);

	write(fd, &player->stat.roty, sizeof(double));
	printf("\trot: %f\n", player->stat.roty);
	write_balise(fd , "🍌");
}

int writing_map(int fd, t_editor *edit)
{
	long *x;
	
	x = (long *)"💎🇩🇿🍉💩";
	write(fd, x, sizeof(long));
	write_textures(fd, edit);
	write_pillars(fd, edit);
	write_sectors(fd, edit);
	write_player(fd, &edit->player);
	write_enemies(fd, edit->ennlist);
	x = (long *)"👨🏻🤠🍑";
	write(fd, x, sizeof(long));
	return (0);
}

int	save_editor_to_file(t_editor *edit)
{
	int fd;


	if ((fd = open("ressources/map/editor.map", O_CREAT | O_EXCL | O_WRONLY, S_IRUSR | S_IRGRP| S_IROTH)) == -1)
	{
		write(2, "Error writting to ressources/map/editor.map\n", 44);
		return (-1);
	}
	writing_map(fd, edit);
	close(fd);
	write(1, "Successfully wrote to ressources/map/editor.map\n", 48);
	return (0);
}
