/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_parseur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 20:53:30 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/25 22:32:06 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				row_verif(t_wolf *wolf, char *row)
{
	int			i;

	i = 0;
	while (row[i])
	{
		if (row[i] == 'A' && (int)wolf->pos.x == 0)
		{
			wolf->pos.x = i + 0.5;
			wolf->pos.y = (double)wolf->map_size.y + 0.5;
		}
		else if (row[i] == 'A' || (row[i] != '.' && row[i] != '#'))
			return (0);
		i++;
	}
	if ((wolf->map_size.x != 0 && wolf->map_size.x != i) || !i)
		return (0);
	else
		wolf->map_size.x = i;
	return (1);
}

t_list			*get_file_lst(t_wolf *wolf, int fd)
{
	int			ret;
	char		*line;
	t_list		*file;
	t_list		*new;

	wolf->map_size.y = 0;
	wolf->map_size.x = 0;
	wolf->pos.x = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		new = ft_lstnew(NULL, 0);
		new->content = line;
		if (!new)
			return (NULL);
		if (row_verif(wolf, line))
			ft_lstadd(&file, new);
		else
			return (NULL);
		wolf->map_size.y++;
		printf("line : %s\n", line);
	}
	return ((ret == 0) ? file : NULL);
}

int				wolf_parseur(t_wolf *wolf, char *filename)
{
	int			fd;
	t_list		*file;

	printf("new_file\n");
	fd = open(filename, O_RDONLY);
	if (!(file = get_file_lst(wolf, fd)))
	{
		printf("mauvais fichier\n\n");
		return (0);
	}
	printf("bon fichier w %d h %d\n", wolf->map_size.x, wolf->map_size.y);
	return (1);
}
