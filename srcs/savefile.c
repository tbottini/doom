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

int	save_editor_to_file(t_editor *edit)
{
	int fd;
	long x;

	if ((fd = open("ressources/map/editor.map", O_CREAT | /*O_EXCL |*/ O_WRONLY, 0777 /*S_IRUSR | S_IRGRP| S_IROTH*/)) == -1)
	{
		write(2, "Error writting to ressources/map/editor.map\n", 44);
		return (-1);
	}
	x = (long)"💎🇩🇿🍉💩";
	write(fd, &x, sizeof(x));
	//writing_map(fd, edit);
	close(fd);
	write(1, "Successfully wrote to ressources/map/editor.map\n", 48);
	return (0);
}
