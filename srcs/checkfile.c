/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 21:39:35 by magrab            #+#    #+#             */
/*   Updated: 2019/07/20 14:02:58 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int	check_balise(int fd, char *balise, int ret)
{
	int *x;
	int y;

	x = (int *)balise;
	read(fd, &y, sizeof(y));
	if (*x != y)
		return (ret);
	return (0);
}

int	check_one_texture(int fd)
{
	int pathlen;
	char path[512];
	int imgfd;

	if (read(fd, &pathlen, sizeof(int)) != sizeof(int) || pathlen >= 512 || pathlen <= 0)
		return (-23);
	if (read(fd, path, sizeof(char) * (pathlen + 1)) != sizeof(char) * (pathlen + 1))
		return (-24);
	path[pathlen] = '\0';
	if ((imgfd = open(path, O_RDONLY | O_NOFOLLOW | O_NONBLOCK)) == -1)
		return (-25);
	close(imgfd);
	if (read(fd, path, sizeof(char)) != sizeof(char) || *path != '\v')
		return (-26);
	return (0);
}

int check_textures(int fd, t_slen *len)
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

int	check_one_pillar(int fd)
{
	t_fvct2 p;

	if ((read(fd, &p.x, sizeof(double))) != sizeof(double))
		return (-32);
	if (read(fd, &p.y, sizeof(double)) != sizeof(double))
		return (-33);
	return (0);
}

int	check_pillars(int fd, t_slen *len)
{
	int x;
	int rtn;

	if (check_balise(fd, "⛩", -3))
		return (-3);
	if ((read(fd, &len->nb_pills, sizeof(int)) != sizeof(int)) || len->nb_pills < 0)
		return (-31);
	x = 0;
	while (x < len->nb_pills)
	{
		if ((rtn = check_one_pillar(fd)))
			return (rtn);
		x++;
	}
	if (check_balise(fd, "💊", 3))
		return (3);
	return (0);
}

int	check_one_prop(int fd)
{
	int		var_a;
	int		var_b;
	double	dtmp;

	if (read(fd, &var_a, sizeof(int)) != sizeof(int))
		return (-72);
	if ((read(fd, &var_a, sizeof(int)) != sizeof(int)))
		return (-73);
	if ((read(fd, &var_b, sizeof(int)) != sizeof(int)))
		return (-74);
	if (var_b == -1)
	{
		if ((read(fd, &var_a, sizeof(int)) != sizeof(int)) || var_a != -1)
			return (-79);
	}
	else if ((read(fd, &var_a, sizeof(int)) != sizeof(int)))
		return (-75);
	if ((read(fd, &dtmp, sizeof(double)) != sizeof(double)))
		return (-76);
	if ((read(fd, &dtmp, sizeof(double)) != sizeof(double)))
		return (-77);
	return (0);
}

int	check_wall_props(int fd)
{
	int x;
	int	nbp;
	int rtn;

	if (check_balise(fd, "🖼", -7))
		return (-7);
	if ((read(fd, &nbp, sizeof(int)) != sizeof(int)) || nbp < 0)
		return (-71);
	x = 0;
	while (x < nbp)
	{
		if ((rtn = check_one_prop(fd)))
			return (rtn);
		x++;
	}
	if (check_balise(fd, "📅", 7))
		return (7);
	return (0);
}

int	check_one_wall(int fd, t_slen *len)
{
	int	tmp;
	t_portal_id ptmp;

	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_pills))
		return (-61);
	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_pills))
		return (-62);
	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_txtrs))
		return (-63);
	if (((read(fd, &ptmp, sizeof(t_portal_id)) != sizeof(t_portal_id))))
		return (-64);
	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_sects))
		return (-65);
	return (check_wall_props(fd));
}

int	check_sec_walls(int fd, t_slen *len)
{
	int x;
	int	nbw;
	int rtn;

	if (check_balise(fd, "💦", -6))
		return (-6);
	if ((read(fd, &nbw, sizeof(int)) != sizeof(int)))
		return (-61);
	x = 0;
	while (x < nbw)
	{
		if ((rtn = check_one_wall(fd, len)))
			return (rtn);
		x++;
	}
	if (check_balise(fd, "⛱", -6))
		return (-5);
	return (0);
}

int	check_sec_props(int fd)
{
	int x;
	int	nbp;
	int rtn;

	if (check_balise(fd, "🚽", -8))
		return (-8);
	if ((read(fd, &nbp, sizeof(int)) != sizeof(int)))
		return (-81);
	x = 0;
	while (x < nbp)
	{
		if ((rtn = check_one_prop(fd)))
			return (rtn);
		x++;
	}
	if (check_balise(fd, "💩", 8))
		return (8);
	return (0);
}

int	check_one_sector(int fd, t_slen *len)
{
	char	ctmp;
	int		itmp;
	double	dtmp;

	if (read(fd, &ctmp, sizeof(char)) != sizeof(char))
		return (-51);
	if (read(fd, &dtmp, sizeof(double)) != sizeof(double))
		return (-52);
	if (read(fd, &dtmp, sizeof(double)) != sizeof(double))
		return (-53);
	if (((read(fd, &itmp, sizeof(int)) != sizeof(int)) || itmp >= len->nb_txtrs))
		return (-54);
	if (((read(fd, &itmp, sizeof(int)) != sizeof(int)) || itmp >= len->nb_txtrs))
		return (-55);
	if ((itmp = check_sec_walls(fd, len)))
		return (itmp);
	return (check_sec_props(fd));
}

int	check_sectors(int fd, t_slen *len)
{
	int x;
	int rtn;

	if (check_balise(fd, "🚧", -5))
		return (-5);
	if ((read(fd, &len->nb_sects, sizeof(int)) != sizeof(int)) || len->nb_sects < 0)
		return (-51);
	x = 0;
	while (x < len->nb_sects)
	{
		if ((rtn = check_one_sector(fd, len)))
			return (rtn);
		x++;
	}
	if (check_balise(fd, "🏠", 5))
		return (5);
	return (0);
}

int	check_player(int fd, t_slen *len)
{
	int tmp;
	double dtmp;

	if (check_balise(fd, "🍆", -9))
		return (-9);
	if ((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_sects)
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

int	check_one_enemy(int fd)
{
	int tmp;
	double dtmp;

	if ((read(fd, &tmp, sizeof(int)) != sizeof(int)) || !(ISENEMY(tmp)))
		return (-101);
	if ((read(fd, &tmp, sizeof(int)) != sizeof(int)))
		return (-102);
	if ((read(fd, &dtmp, sizeof(double)) != sizeof(double)))
		return (-103);
	if ((read(fd, &dtmp, sizeof(double)) != sizeof(double)))
		return (-104);
	if ((read(fd, &dtmp, sizeof(double)) != sizeof(double)))
		return (-105);
	return (0);
}

int	check_enemies(int fd)
{
	int	x;
	int	rtn;
	int	nbe;

	if (check_balise(fd, "🔪", -10))
		return (-10);
	if ((read(fd, &nbe, sizeof(int)) != sizeof(int)))
		return (-11);
	x = 0;
	while (x < nbe)
	{
		if ((rtn = check_one_enemy(fd)))
			return (rtn);
		x++;
	}
	if (check_balise(fd, "🍹", 10))
		return (10);
	return (0);
}

int check_map(int fd, t_slen *len)
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
