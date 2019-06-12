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

char 		*double_atof(char *line, t_fvct2 *vct)
{
	char	*p;
	vct->x = ft_catof(line, ' ');
	p = ft_strchr(line, ' ');
	vct->y = ft_atof(p + 1);
	return (ft_strchr(p + 1, ' '));
}

char		*triple_atof(char *line, t_fvct3 *fvct)
{
	char	*p;

	p = double_atof(line, (t_fvct2*)fvct);
	fvct->z = ft_atof(p + 1);
	return (ft_strchr(p + 1, ' '));
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
		if (!ft_strncmp(line, "TXTR", 4))
		{
			printf("chunk texture\n");
			chunk_texture(&doom->sdl, &doom->tool, fd);
		}
		if (!ft_strncmp(line, "SCTR", 4))
		{
			printf("chunck_sector\n");
			doom->sector = chunck_sector(fd, &doom->tool);
		}
		else if (!ft_strncmp(line, "PERS", 4))
		{
			doom->player = chunck_player(fd);
			doom->player.sector = search_sector(doom->sector, line + 5);
			doom->player.pos.z = doom->player.sector->h_floor;
			doom->camera.d_screen = (doom->sdl.size.x / 2.0) / tan(doom->player.fov / 2.0 * PI180);
		}
		free(line);
	}
	free(line);
	return (1);
}
