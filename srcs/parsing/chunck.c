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
			double_atof(line, &player.pos);
		else if (i == 1)
			double_atof(line, &player.rot);
		else if (i == 2)
			player.fov = ft_atof(line);
		i++;
	}
	return (player);
}

t_sector	*chunck_sector(int fd)
{
	t_sector	*sector;
	t_list		*files;
	t_list		*node;
	char		*line;
	int			nline;

	nline = 0;
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
		else
		{
			node = ft_lstn(line);
			ft_lstadd(&files, node);
		}
		nline++;
	}
	sector->wall = chunck_walls(files, nline - 2);
	sector->len = nline - 2;
	return (sector);
}
