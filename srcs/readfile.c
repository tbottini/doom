/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:39:35 by magrab            #+#    #+#             */
/*   Updated: 2019/07/07 13:15:25 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int	read_balise(int fd, char *balise)
{
	int x;
	int y;

	x = (int)balise;
	read(fd, &y, sizeof(x));
	if (x == y)
		return (1);
	return (0);
}

int	read_file(t_doom *doom, const char *file)
{
	int		fd;
	long	x;
	long	y;
	int		i;
	int		j;

	if ((fd = open(file, O_RDONLY | O_NOFOLLOW | O_NONBLOCK)) == -1)
	{
		write(2, "Error opening file\n", 19);
		return (-1);
	}
	read(fd, &x, sizeof(x));
	y = (long)"💎🇩🇿🍉💩";
	if (x != y)
	{
		ft_printf("Invalid file start balise : %s\n", file);
		close(fd);
		return (-1);
	}
	/*if (!read_balise(fd, "🌅"))
	{
		ft_printf("Invalid file 2 : %s\n", file);
		close(fd);
		return (-1);
	}*/
	read(fd, &x, sizeof(x));
	y = (long)"👨🏻🤠🍑";
	if (x != y)
	{
		ft_printf("Invalid file end balise : %s\n", file);
		close(fd);
		return (-1);
	}
	close(fd);
	write(1, "Successfully read ressources/map/editor.map\n", 48);
	return (0);
}
