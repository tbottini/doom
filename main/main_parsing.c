#include "doom_nukem.h"

float		ft_atof(char *str)
{
	float	nb;
	int		i;
	int		sign;
	float	j;

	j = 10.0;
	sign = (str[0] == '-') ? -1 : 1;
	nb = 0.0;
	i = 0;
	while (str[i] && str[i] != '.')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	i++;
	while (str[i])
	{
		nb = nb + (str[i] - '0') / j;
		j *= 10.0;
		i++;
	}
	return (nb);
}

float		ft_catof(char *str, char c)
{
	float	nb;
	int		i;
	int		sign;
	float	j;

	j = 10.0;
	sign = (str[0] == '-') ? -1 : 1;
	nb = 0.0;
	i = 0;
	while (str[i] && str[i] != '.' && str[i] != c)
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	if (str[i] != ' ')
		i++;
	while (str[i] && str[i] != c)
	{
		nb = nb + (str[i] - '0') / j;
		j *= 10.0;
		i++;
	}
	return (nb);
}

t_wl		*wall_by_line(char *line, t_wl *past)
{
	t_wl	*wall;

	if (!(wall = (t_wl*)malloc(sizeof(t_wl))))
		return (NULL);

	wall->pos.x = ft_catof(line, ' ');
	wall->pos.y = ft_atof(ft_strchr(line, ' ') + 1);
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
	if (!ft_strcmp(line, "END"))
		tmp_wl->next = sector->root_wall;
	ft_strdel(&line);
	return (sector);
}

t_sector	*parsing(char *av)
{
	int			fd;
	char		*line;
	t_sector	*sector;

	fd = open(av, O_RDONLY | O_NOFOLLOW);
	if (fd == -1)
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_strcmp(line, "SCTR"))
			sector = chunck_sector(fd);
	}
	return (sector);
}

void		sector_describe(t_sector sector)
{
	t_wl	*wall;

	ft_putstr("height floor : ");
	ft_putfloat(sector.h_floor);
	ft_putstr("\nheight ceil : ");
	ft_putfloat(sector.h_ceil);
	wall = NULL;
	while (!wall || wall->next != sector.root_wall)
	{
		if (wall == NULL)
			wall = sector.root_wall;
		else
			wall = wall->next;
		ft_putchar('\n');
		fvct2_print(wall->pos);
		ft_putstr(" to ");
		fvct2_print(wall->next->pos);
	}
	ft_putchar('\n');
}

int			main(int ac, char **av)
{
	t_sector	*sector;

	if (ac < 2)
	{
		ft_putendl("pas de fichier");
		return (0);
	}
	if (!(sector = parsing(av[1])))
		ft_putendl("fichier non conforme");
	else
	{
		sector_describe(*sector);
	}
	return (0);
}
