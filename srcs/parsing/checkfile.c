/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:39:35 by magrab            #+#    #+#             */
/*   Updated: 2019/08/12 13:49:30 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int	check_one_texture(int fd)
{
	int		plen;
	char	path[512];
	int		imgfd;

	if (read(fd, &plen, sizeof(int)) != sizeof(int) || plen >= 512 || plen <= 0)
		return (-23);
	if (read(fd, path, sizeof(char) * (plen + 1)) != sizeof(char) * (plen + 1))
		return (-24);
	path[plen] = '\0';
	if ((imgfd = open(path, O_RDONLY | O_NOFOLLOW | O_NONBLOCK)) == -1)
		return (-25);
	close(imgfd);
	if (read(fd, path, sizeof(char)) != sizeof(char) || *path != '\v')
		return (-26);
	return (0);
}

int	check_textures(int fd, t_slen *len)
{
	int x;
	int rtn;

	if (check_balise(fd, "🌅", -2))
		return (-2);
	if (read(fd, &len->nb_txtrs, sizeof(int)) != sizeof(int))
		return (-21);
	x = 0;
	while (x < len->nb_txtrs)
	{
		if ((rtn = check_one_texture(fd)))
			return (rtn);
		x++;
	}
	if (check_balise(fd, "🌌", 2))
		return (2);
	return (0);
}

int	check_player(int fd, t_slen *len)
{
	unsigned int	tmp;
	double			dtmp;

	if (check_balise(fd, "🍆", -9))
		return (-9);
	if ((read(fd, &tmp, sizeof(int)) != sizeof(int))
			|| tmp >= (unsigned int)len->nb_sects)
		return (-91);
	if ((read(fd, &tmp, sizeof(int)) != sizeof(int)))
		return (-92);
	if ((read(fd, &dtmp, sizeof(double)) != sizeof(double)))
		return (-93);
	if ((read(fd, &dtmp, sizeof(double)) != sizeof(double)))
		return (-94);
	if ((read(fd, &dtmp, sizeof(double)) != sizeof(double)))
		return (-95);
	if (check_balise(fd, "🍌", 9))
		return (9);
	return (0);
}

int	check_map(int fd, t_slen *len)
{
	long	x;
	long	*tmp;
	int		rtn;

	read(fd, &x, sizeof(x));
	tmp = (long *)"💎🇩🇿🍉💩";
	if (x != *tmp)
		return (1);
	if ((rtn = check_textures(fd, len)))
		return (rtn);
	if ((rtn = check_pillars(fd, len)))
		return (rtn);
	if ((rtn = check_sectors(fd, len)))
		return (rtn);
	if ((rtn = check_player(fd, len)))
		return (rtn);
	if ((rtn = check_enemies(fd)))
		return (rtn);
	read(fd, &x, sizeof(x));
	tmp = (long *)"👨🏻🤠🍑";
	if (x != *tmp)
		return (-1);
	return (0);
}

int	check_file(const char *file)
{
	int		fd;
	int		returncode;
	t_slen	len;

	if ((fd = open(file, O_RDONLY | O_NOFOLLOW | O_NONBLOCK)) == -1)
	{
		ft_putendl_fd("Error opening file :", 2);
		ft_putendl_fd(file, 2);
		return (0);
	}
	if ((returncode = check_map(fd, &len)))
	{
		ft_printf("%s ❌  : %d\n", file, returncode);
		close(fd);
		return (0);
	}
	close(fd);
	ft_putstr(file);
	ft_putendl(" ✅");
	return (1);
}
