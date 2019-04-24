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
			wolf->pos.y = (double)wolf->map_size.y + 0.5;
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
	while (flag == 0 && (ret = get_next_line(fd, &line)) > 0)
	{
		if (wolf->map_size.x == 0)
		{
			if (ft_strlen(line) < 100)
				wolf->map_size.x = (int)ft_strlen(line);
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
	return (1);
}

int				get_texture(int fd, t_wolf *wolf)
{
	int			i;
	char		*path;
	int			j;

	j = -1;
	i = -1;
	while (i++ != 4 && get_next_line(fd, &path) > 0)
	{
		wolf->wl_txture[i] = IMG_Load(path);
		if (!wolf->wl_txture[i])
			return (0);
		wolf->wall[i] = (uint32_t*)wolf->wl_txture[i]->pixels;
		free(path);
	}
	if (i == 4)
		return (1);
	return (0);
}

int				wolf_parseur(t_wolf *wolf, char *filename)
{
	int			fd;

	fd = open(filename, O_RDONLY);
	if (map_verif(fd, wolf) == 0)
		return (0);
	if (get_texture(fd, wolf) == 0)
		return (0);
	return (1);
}
