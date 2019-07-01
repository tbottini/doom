#include "doom_nukem.h"

/*
**	on recupere le chunck en liste de string, chaque string est un pillier
**	du mur
*/
t_wall		*chunck_walls(t_list *chunck_line, t_designer *ressource, size_t len)
{
	t_wall	*wall;
	t_list	*node;
	char	*p;
	int		i;
	int		index_info;

	if (!(wall = (t_wall*)malloc(sizeof(t_wall) * (len))))
		return (NULL);
	i = 0;
	while (chunck_line)
	{
		node = chunck_line;
		p = chunck_line->content;
		if (i != 0)
			wall[i].next = &wall[i - 1].pillar;
		if (p[0] == 'W')
			wall[i].status = WALL;
		else if (p[0] == 'P')
			wall[i].status = PORTAL_DIRECT;
		else if (p[0] == 'O')
			wall[i].status = WINDOW;
		p = double_atof(p+1, &wall[i].pillar.p);
		//printf("%s\n", p);
		index_info = atoi(p);
		//verifier que index info n'est pas superieur a la taille ni inferieur a 0

		wall[i].txtr.pixels = ressource->texture[index_info]->pixels;
		wall[i].txtr.w = ressource->texture[index_info]->w;
		wall[i].txtr.h = ressource->texture[index_info]->h;
		chunck_line = chunck_line->next;
		free(node->content);
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
			double_atof(line, (t_fvct2*)&player.stat.pos);
		else if (i == 1)
		{
			player.stat.height = ft_atof(line);
		}
		else if (i == 2)
			double_atof(line, &player.stat.rot);
		else if (i == 3)
			player.fov = ft_atoi(line);
		free(line);
		i++;
	}
	free(line);
	player_init(&player);
	return (player);
}

/*
chunk sector

on recupere les lignes
on defini les premiere caracteristique lorsque qu'il y a un secteur
on l'ajoute a une liste chaine


*/
t_list		*add_subsector(t_list **list, t_designer *ressources, int fd)
{
	t_list		*sub_sector;
	t_sector	*sector;
	t_list		*cursor;

	sub_sector = (t_list*)malloc(sizeof(t_list));
	if (!sub_sector)
		return (NULL);
	sector = chunck_sector(fd, ressources);
	sub_sector->content = sector;
	sub_sector->next = NULL;
	if (!(*list))
	{
		*list = sub_sector;
		return (*list);
	}
	cursor = *list;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = sub_sector;
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
		ft_memcpy(&parent->ssector[i], sub_sector->content, sizeof(t_sector));
		tmp = sub_sector;
		sub_sector = sub_sector->next;
		free(tmp->content);
		free(tmp);
		++i;
	}
	return (0);
}

///////////////////////////////////////////////////////////////
/*
int			check_enemy(char *line)
{
	int i;

	if (line[4] != ' ')
		return (0);
	i = 5;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) || (line[i] != ' ' && line[i] != '.'))
			return (0);
		i++;
	}
	return (1);
}

double		ft_atof_enemy(char *str, int *i, int *s)
{
	double	nb;
	double	j;

	j = 10.0;
	nb = 0.0;
	while (str[*i] && str[*i] != '.' && str[*i] != ' ' && str[*i] != '\n')
	{
		nb = nb * 10 + str[*i] - '0';
		*i++;
	}
	if (str[*i])
		*i++;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\n')
	{
		nb = nb + (str[*i] - '0') / j;
		j *= 10.0;
		*i++;
	}
	*++s;
	return (nb);
}

int			parse_enemy(t_sector *sector, char *line)
{
	t_enemy	*enemy;
	double	tmp;

	if (!(enemy = enemy_init(ft_atoi(line + 5))))
		return (NULL);
	enemy->stat.pos.x = atof(line + 7);
	enemy->stat.pos.y = atof(line + 12);
	enemy->stat.rot.y = atof(line + 17);
	enemy->stat.pos.z = sector->h_floor;
	enemy->stat.rot.x = 90.0;
	if (sector->enemys == NULL);
		sector->enemys = enemy;
	//else
	//	;//
	return (1);
}
*/
////////////////////////////////////////////////////////////////

t_sector	*chunck_sector(int fd, t_designer *ressources)
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
		{
			sector->h_floor = ft_atof(line);
			free(line);
		}
		else if (nline == 1)
		{
			sector->h_ceil = ft_atof(line);
			free(line);
		}
		else if (nline == 2)
			files = ft_lstn(line);
		else if (!ft_strcmp(line, "SCTR"))
		{
			add_subsector(&sub_sector, ressources, fd);
			tmp = (t_sector*)sub_sector->content;
			nline--;
			free(line);
		}
		else if (!ft_strncmp(line, "ENEM", 4))
		{
			;//parse_enemy(sector, line);
		}
		else
		{
			node = ft_lstn(line);
			ft_lstadd(&files, node);
		}
		nline++;
	}
	if (line)
		free(line);
	if (sub_sector)
		list_to_ssector(sector, sub_sector);
	sector->wall = chunck_walls(files, ressources, nline - 2);
	sector->len = nline - 2;
	return (sector);
}
