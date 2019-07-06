/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savefile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:39:35 by magrab            #+#    #+#             */
/*   Updated: 2019/07/04 21:39:36 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int	read_file(t_doom *doom, const char *file)
{
	int fd;
	long x;
	long y;

	if ((fd = open(file, O_RDONLY | O_NOFOLLOW | O_NONBLOCK)) == -1)
	{
		write(2, "Error opening file\n", 19);
		return (-1);
	}
	read(fd, &x, sizeof(x));
	y = (long)"💎🇩🇿🍉💩";
	if (x != y)
	{
		ft_printf("Invalid file : %s\n", file);
		return (-1);
	}
	close(fd);
	write(1, "Successfully read ressources/map/editor.map\n", 48);
	return (0);
}
