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

t_sector		*search_sector(t_sector *sector, char *search)
{
	int	i_sector;

	if (!(*search))
		return (sector);
	i_sector = ft_catoi_u(search, '.');
	if (i_sector > sector->len_sub)
		return (NULL);
	search = ft_strchr(search, '.');
	if (!search)
	{
		return (&sector->ssector[i_sector]);
	}
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
	return (1);
}
