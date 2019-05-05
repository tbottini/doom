#include "doom_nukem.h"

t_wl		*wall_by_line(char *line, t_wl *past)
{
	t_wl	*wall;

	if (!(wall = (t_wl*)malloc(sizeof(t_wl))))
		return (NULL);

	wall->pos.x = ft_catof(line, ' ');
	wall->pos.y = ft_atof(ft_strchr(line, ' ') + 1);
	wall->frust = -1;
	if (past)
		past->next = wall;
	return (wall);
}

t_sector	*chunck_sector(int fd)
{
	t_sector	*sector;
	t_wl		*tmp_wl;
	char		*line;
	int			i;

	i = 0;
	sector = (t_sector *)malloc(sizeof(t_sector));
	if (!sector)
		return (0);
	while (get_next_line(fd, &line) > 0 && ft_strcmp(line, "END"))
	{
		if (i == 0)
			sector->h_floor = ft_atof(line);
		else if (i == 1)
			sector->h_ceil = ft_atof(line);
		else if (i == 2)
		{
			sector->root_wall = wall_by_line(line, NULL);
			tmp_wl = sector->root_wall;
		}
		else
			tmp_wl = wall_by_line(line, tmp_wl);
		i++;
		free(line);
	}
	sector->len = i - 2;
	if (!ft_strcmp(line, "END"))
		tmp_wl->next = sector->root_wall;
	ft_strdel(&line);
	return (sector);
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
	}
	return (1);
}
