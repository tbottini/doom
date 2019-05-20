#include "doom_nukem.h"

/*
**	on recupere le chunck en liste de string, chaque string est un pillier
**	du mur
*/
t_wall		*chunck_walls(t_list *chunck_line, size_t len)
{
	t_wall	*wall;
	t_list	*node;
	int		i;

	if (!(wall = (t_wall*)malloc(sizeof(t_wall) * (len))))
		return (NULL);
	i = 0;
	while (chunck_line)
	{
		node = chunck_line;
		if (i != 0)
			wall[i].next = &wall[i - 1].pillar;
		double_atof(node->content, &wall[i].pillar.p);
		chunck_line = chunck_line->next;
		free(node);
		i++;
	}
	wall[0].next = &wall[i - 1].pillar;
	return (wall);
}

t_player	chunck_player(int fd)
{
	t_player	player;
	int			i;
	char		*line;

	i = 0;
	while (get_next_line(fd, &line) > 0 && ft_strcmp(line, "END"))
	{
		if (i == 0)
			triple_atof(line, &player.pos);
		else if (i == 1)
			double_atof(line, &player.rot);
		else if (i == 2)
			player.fov = ft_atoi(line);
		i++;
	}
	player.health = 100;
	return (player);
}

/*
chunk sector

on recupere les lignes
on defini les premiere caracteristique lorsque qu'il y a un secteur
on l'ajoute a une liste chaine


*/
t_list		*add_subsector(t_list **list, int fd)
{
	t_list		*sub_sector;
	t_sector	*sector;

	sub_sector = (t_list*)malloc(sizeof(t_list));
	if (!sub_sector)
		return (NULL);
	sector = chunck_sector(fd);
	sub_sector->content = sector;
	sub_sector->next = *list;
	(*list) = sub_sector;
	return (*list);
}

size_t		list_len(t_list *list)
{
	size_t	len;

	len = 0;
	while (list != NULL)
	{
		len++;
		list = list->next;
	}
	return (len);
}

int			list_to_ssector(t_sector *parent, t_list *sub_sector)
{
	int			i;
	t_list		*tmp;

	i = 0;
	parent->len_sub = list_len(sub_sector);
	parent->ssector = (t_sector*)malloc(sizeof(t_sector) * (parent->len_sub));
	if (!parent->ssector)
		return (0);
	while (i < parent->len_sub)
	{
		//parent->ssector[i].wall
		ft_memcpy(&parent->ssector[i], sub_sector->content, sizeof(t_sector));
		tmp = sub_sector;
		sub_sector = sub_sector->next;
		free(tmp);
		++i;
	}
	return (0);
}

t_sector	*chunck_sector(int fd)
{
	t_sector	*sector;
	t_list		*files;
	t_list		*node;
	char		*line;
	int			nline;
	t_list		*sub_sector;


	t_sector	*tmp;

	nline = 0;
	sub_sector = NULL;
	if (!(sector = sector_new()))
		return (0);
	while (get_next_line(fd, &line) > 0 && ft_strcmp(line, "END"))
	{
		if (nline == 0)
			sector->h_floor = ft_atof(line);
		else if (nline == 1)
			sector->h_ceil = ft_atof(line);
		else if (nline == 2)
			files = ft_lstn(line);
		else if (!ft_strcmp(line, "SCTR"))
		{
			//on ajoute le sous secteur a la liste du secteur
			add_subsector(&sub_sector, fd);
			tmp = (t_sector*)sub_sector->content;
			nline--;
		}
		else
		{
			node = ft_lstn(line);
			ft_lstadd(&files, node);
		}
		nline++;
	}
	if (sub_sector)
		list_to_ssector(sector, sub_sector);
	sector->wall = chunck_walls(files, nline - 2);
	sector->len = nline - 2;
	return (sector);
}
