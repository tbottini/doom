/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_parseur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 20:53:30 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/27 12:58:51 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_list			*get_file_lst(t_wolf *wolf, int fd)
{
	int			ret;
	char		*line;
	t_list		*file;
	t_list		*new;

	vct2_value(&wolf->map_size, 0, 0);
	wolf->pos.x = 0;
	file = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!(new = ft_lstnew(line, sizeof(line))))
		{
			free(line);
			return (listdel(&file));
		}
		(file == NULL) ? file = new : ft_lstadd(&file, new);
		if (!row_verif(wolf, line))
			return (listdel(&file));
		wolf->map_size.y++;
	}
	ft_strdel(&line);
	return ((ret == 0 || wolf->pos.x == 0) ? file : listdel(&file));
}

int				list_to_map(t_wolf *wolf, t_list **f)
{
	int			row;
	t_list		*tmp;
	t_list		*file;

	file = *f;
	if (!(wolf->map = tab_new(wolf->map_size.y)))
		return (0);
	row = wolf->map_size.y;
	while (--row > -1)
	{
		wolf->map[row] = ft_strdup((char *)file->content);
		if (!wolf->map[row])
			return (0);
		tmp = file;
		file = file->next;
		lst_del_node(&tmp);
	}
	return (1);
}

void			wolf_clear_map(t_wolf *wolf)
{
	int			i;

	i = 0;
	if (!wolf->map)
		return ;
	while (i < wolf->map_size.y)
	{
		free(wolf->map[i]);
		i++;
	}
	free(wolf->map);
	wolf->map = NULL;
}

int				wolf_parseur(t_wolf *wolf, char *filename)
{
	int			fd;
	t_list		*file;

	fd = open(filename, O_RDONLY);
	if (!(file = get_file_lst(wolf, fd)))
		return (0);
	if (!list_to_map(wolf, &file))
		return (0);
	return (1);
}
