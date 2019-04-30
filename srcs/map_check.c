/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 12:48:11 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/27 12:48:14 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				row_verif(t_doom *doom, char *row)
{
	int			i;

	i = 0;
	while (row[i])
	{
		if (row[i] == 'A' && doom->pos.x < 0.1)
		{
			doom->pos.x = i + 0.5;
			doom->pos.y = (double)doom->map_size.y + 0.5;
		}
		else if (row[i] == 'A' || (row[i] != '.' && row[i] != '#'))
			return (0);
		i++;
	}
	if ((doom->map_size.x != 0 && doom->map_size.x != i) || !i)
		return (0);
	else
		doom->map_size.x = i;
	return (1);
}

int				map_check(t_doom *doom, char *filename)
{
	int			fd;
	int			ret;
	char		*line;

	fd = open(filename, O_RDONLY);
	line = NULL;
	doom->map_size.x = 0;
	doom->map_size.y = 0;
	doom->pos.x = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!row_verif(doom, line))
		{
			free(line);
			return (0);
		}
		free(line);
		doom->map_size.y++;
	}
	if (line)
		free(line);
	if ((int)doom->pos.x == 0)
		return (0);
	return ((ret == 0) ? 1 : 0);
}
