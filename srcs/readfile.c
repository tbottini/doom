/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:39:35 by magrab            #+#    #+#             */
/*   Updated: 2019/07/09 14:27:23 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int	read_balise(int fd, char *balise, int ret)
{
	int x;
	int y;

	x = (int)balise;
	read(fd, &y, sizeof(x));
	if (x != y)
		return (ret);
	return (0);
}

int reading_map(int fd, t_doom *doom)
{
	long	x;
	long	tmp;

	read(fd, &x, sizeof(x));
	tmp = (long)"💎🇩🇿🍉💩";
	if (x != tmp)
		return (1);
	//read_textures(fd, edit);
	//read_pillars(fd, edit);
	//read_sectors(fd, edit);
	//read_player(fd, &edit->player);
	//read_enemies(fd, edit->ennlist);
	read(fd, &x, sizeof(x));
	tmp = (long)"👨🏻🤠🍑";
	if (x != tmp)
		return (-1);
	return (0);
}

int	read_file(t_doom *doom, const char *file)
{
	int		fd;
	int		returncode;

	if ((fd = open(file, O_RDONLY | O_NOFOLLOW | O_NONBLOCK)) == -1)
	{
		write(2, "Error opening file\n", 19);
		return (-1);
	}
	if ((returncode = reading_map(fd, doom)))
	{
		ft_printf("Error : %d\n", returncode);
		close(fd);
		return (-1);
	}
	close(fd);
	write(1, "Successfully read ressources/map/editor.map\n", 48);
	return (0);
}
