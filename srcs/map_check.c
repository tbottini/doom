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

#include "wolf3d.h"

int				row_verif(t_wolf *wolf, char *row)
{
	int			i;

	i = 0;
	while (row[i])
	{
		if (row[i] == 'A' && wolf->pos.x < 0.1)
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

int				map_check(t_wolf *wolf, char *filename)
{
	int			fd;
	int			ret;
	char		*line;

	fd = open(filename, O_RDONLY);
	line = NULL;
	wolf->map_size.x = 0;
	wolf->map_size.y = 0;
	wolf->pos.x = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!row_verif(wolf, line))
		{
			free(line);
			return (0);
		}
		free(line);
		wolf->map_size.y++;
	}
	if (line)
		free(line);
	return ((ret == 0) ? 1 : 0);
}
