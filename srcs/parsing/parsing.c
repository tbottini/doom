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
