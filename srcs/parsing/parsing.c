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
	char			*next_s;

	//0.0.1 //on recherche is le premier index existe c
	//a.2
	//.
	//a.32.52 //de passement de l'index
	//si ya plus de nombre on remonte
	next_s = ft_strchr(search, '.');
	//si il ne reste plus de point on recupere le prochain nombre on renvoie l'index du sector
	//si il reste un point alors on recupere le prochain nombre jusqu'au point, on fait un recursive
	//en envoiyant le secteur et l'index
	i_sector = ft_catoi_u(search, '.');
	if (i_sector < sector->len_sub)
		return (NULL);
	if (!next_s)
	{
		return (&sector->ssector[i_sector]);
	}
	else
	{
		return (search_sector(&sector->ssector[i_sector], next_s + 1));
	}
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
		if (!ft_strcmp(line, "SCTR"))
			doom->sector = chunck_sector(fd);
		else if (!ft_strcmp(line, "PERS"))
			doom->player = chunck_player(fd);
	}
	return (1);
}
