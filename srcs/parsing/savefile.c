/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savefile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:39:35 by magrab            #+#    #+#             */
/*   Updated: 2019/08/04 14:48:40 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	write_one_texture(int fd, t_editor *edit, SDL_Texture *txtr)
{
	char	*path;
	int		pathlen;

	path = get_path(edit, txtr);
	pathlen = ft_strlen(path);
	write(fd, &pathlen, sizeof(int));
	write(fd, path, sizeof(char) * (pathlen + 1));
	write(fd, "\v", sizeof(char));
}

void	write_textures(int fd, t_editor *edit)
{
	int	i;
	int	nb_textures;

	write_balise(fd, "🌅");
	load_used_textures(edit);
	nb_textures = 0;
	while (nb_textures < MAXTXTRNUMBER && edit->txtrreal[nb_textures])
		nb_textures++;
	write(fd, &nb_textures, sizeof(int));
	i = 0;
	while (i < nb_textures)
	{
		write_one_texture(fd, edit, edit->txtrreal[i]);
		i++;
	}
	write_balise(fd, "🌌");
}

void	write_enemies(int fd, t_lstent enn)
{
	t_lstent	tmp;
	int			c;

	write_balise(fd, "🔪");
	c = 0;
	tmp = enn;
	while (tmp)
	{
		if (ISENEMY(tmp->stat.type))
			c++;
		tmp = tmp->next;
	}
	write(fd, &c, sizeof(int));
	tmp = enn;
	while (tmp)
	{
		if (ISENEMY(tmp->stat.type))
			write_one_enemy(fd, tmp);
		tmp = tmp->next;
	}
	write_balise(fd, "🍹");
}

int		writing_map(int fd, t_editor *edit)
{
	long	*x;

	x = (long *)"💎🇩🇿🍉💩";
	write(fd, x, sizeof(long));
	write_textures(fd, edit);
	write_pillars(fd, edit);
	write_sectors(fd, edit);
	write_player(fd, &edit->player);
	write_enemies(fd, edit->ennlist);
	x = (long *)"👨🏻🤠🍑";
	write(fd, x, sizeof(long));
	return (0);
}

int		save_editor_to_file(t_editor *edit)
{
	int		fd;
	char	path[512];

	ft_strcpy(path, "ressources/map/");
	ft_strcpy(&(path[15]), edit->filename);
	remove(path);
	if ((fd = open(path, O_CREAT | O_TRUNC | O_WRONLY,
		S_IRWXU | S_IRGRP | S_IROTH)) == -1)
	{
		ft_putendl_fd("Error writting to ressources/map/editor.map\n", 2);
		return (-1);
	}
	writing_map(fd, edit);
	close(fd);
	ft_putstr("Successfully wrote to ");
	ft_putendl(path);
	return (0);
}
