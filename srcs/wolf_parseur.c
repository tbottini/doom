/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_parseur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 20:53:30 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/28 15:36:27 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_list			*ft_lstn(void *mcontent)
{
	t_list		*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = mcontent;
	new->content_size = sizeof(mcontent);
	new->next = NULL;
	return (new);
}

t_list			*get_file_lst(t_wolf *doom, int fd)
{
	int			ret;
	char		*line;
	t_list		*file;
	t_list		*new;

	vct2_value(&doom->map_size, 0, 0);
	doom->pos.x = 0;
	file = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!(new = ft_lstn(line)))
		{
			free(line);
			return (listdel(&file));
		}
		(file == NULL) ? file = new : ft_lstadd(&file, new);
		if (!row_verif(doom, line))
			return (listdel(&file));
		doom->map_size.y++;
	}
	ft_strdel(&line);
	return ((ret == 0 || doom->pos.x == 0) ? file : listdel(&file));
}

int				list_to_map(t_wolf *doom, t_list **f)
{
	int			row;
	t_list		*tmp;
	t_list		*file;

	file = *f;
	if (!(doom->map = tab_new(doom->map_size.y)))
		return (0);
	row = doom->map_size.y;
	while (--row > -1)
	{
		doom->map[row] = file->content;
		if (!doom->map[row])
			return (0);
		tmp = file;
		file = file->next;
		free(tmp);
	}
	return (1);
}

void			wolf_clear_map(t_wolf *doom)
{
	int			i;

	i = 0;
	if (!doom->map)
		return ;
	while (i < doom->map_size.y)
	{
		free(doom->map[i]);
		i++;
	}
	free(doom->map);
	doom->map = NULL;
}

int				wolf_parseur(t_wolf *doom, char *filename)
{
	int			fd;
	t_list		*file;

	fd = open(filename, O_RDONLY);
	if (!(file = get_file_lst(doom, fd)))
		return (0);
	if (!list_to_map(doom, &file))
		return (0);
	return (1);
}
