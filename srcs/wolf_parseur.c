#include "wolf3d.h"

int				row_verif(t_wolf *wolf, char *row)
{
	int			i;

	i = 0;
	while(row[i])
	{
		if(row[i] == 'A')
		{
			wolf->pos.x = i + 0.5;
			wolf->pos.y = (float)wolf->map_size.y + 0.5;
		}
		else if (row[i] != '.' && row[i] != '#')
			return (0);
		i++;
	}
	return (1);
}

int				map_verif(int fd, t_wolf *wolf)
{
	char		*line;
	int			ret;
	int			flag;

	line = NULL;
	flag = 0;
	wolf->map_size.x = 0;
	wolf->map_size.y = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && flag == 0)
	{
		if (wolf->map_size.x == 0)
		{
			if (ft_strlen(line) < 100)
				wolf->map_size.x = ft_strlen(line);
			else
				return (0);
		}
		if (ft_strcmp(line, "[Textures]") == 0)
			flag = 1;
		else if ((int)ft_strlen(line) == wolf->map_size.x)
		{
			if (row_verif(wolf, line))
				ft_strcpy(wolf->map[wolf->map_size.y], line);
			else
				return (0);
		}
		else
			return (0);
		wolf->map_size.y++;
		free(line);
	}
	if (line)
		free(line);
	return (1);
}

int				wolf_parseur(t_wolf *wolf, char *filename)
{
	int			fd;

	fd = open(filename, O_RDONLY);
	if (map_verif(fd, wolf) == 0)
		return (0);
	return (1);
}
