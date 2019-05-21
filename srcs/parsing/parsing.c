#include "doom_nukem.h"

t_list		*ft_lstn(void *content)
{
	t_list *n;

	n = (t_list *)malloc(sizeof(t_list));
	if (!n)
		return (NULL);
	n->content = content;
	n->next = NULL;
	return (n);
}

t_fvct2		*double_atof(char *line, t_fvct2 *vct)
{
	vct->x = ft_catof(line, ' ');
	vct->y = ft_atof(ft_strchr(line, ' ') + 1);
	return (vct);
}

t_fvct3		*triple_atof(char *line, t_fvct3 *fvct)
{
	char	*inter;

	fvct->x = ft_catof(line, ' ');
	inter =  ft_strchr(line, ' ') + 1;
	fvct->y = ft_catof(inter, ' ');
	fvct->z = ft_atof(ft_strchr(inter, ' ') + 1);
	return (fvct);
}

// t_wl		*wall_by_line(char *line, t_wl *past)
// {
	// t_wall	*wall;
//
	// if (!(wall = (t_wl*)malloc(sizeof(t_wl))))
		// return (NULL);
	// double_atof(line, wall[i].pillar);
	// wall->pillar.x = ft_catof(line, ' ');
	// wall->pillar.y = ft_atof(ft_strchr(line, ' ') + 1);
	// wall->frust = -1;
	// if (past)
		// past->next = wall;
	// return (wall);
// }

t_sector		*search_sector(t_sector *sector, char *search)
{
	int	i_sector;

	//0.0.1 //on recherche is le premier index existe c
	//on recupere le nombre jusqu'au prochain point
	printf("appel\n");
	if (!(*search))
		return (sector);
	printf("search : %s\n", search);
	i_sector = ft_catoi_u(search, '.');
	printf("i_sector %d sector->len_sub %d\n", i_sector, sector->len_sub);
	if (i_sector > sector->len_sub)
		return (NULL);
	printf("no problem\n");
	search = ft_strchr(search, '.');
	if (!search)
	{
		printf("return \n");
		return (&sector->ssector[i_sector]);
	}
	printf("search ?\n");
	return (search_sector(&sector->ssector[i_sector], search + 1));
}

int			parsing(t_doom *doom, char *filename)
{
	int			fd;
	char		*line;

	fd = open(filename, O_RDONLY | O_NOFOLLOW);
	if (fd == -1)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_strncmp(line, "SCTR", 4))
		{
			printf("chunck_sector\n");
			doom->sector = chunck_sector(fd);
		}
		else if (!ft_strncmp(line, "PERS", 4))
		{
			doom->player = chunck_player(fd);
			doom->player.sector = search_sector(doom->sector, line + 5);
		}
		free(line);
	}
	free(line);
	printf("sector player %p\n", (doom->player.sector));
	printf("sector root 0.0 %p\n", &doom->sector->ssector[0].ssector[1]);
	return (1);
}
