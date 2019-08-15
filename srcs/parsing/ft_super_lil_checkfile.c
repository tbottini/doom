/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_super_lil_checkfile.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 21:26:15 by magrab            #+#    #+#             */
/*   Updated: 2019/08/15 21:26:17 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int	check_one_sector(int fd, t_slen *len)
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
	if (((read(fd, &itmp, sizeof(int)) != sizeof(int))
			|| itmp >= len->nb_txtrs))
		return (-54);
	if (((read(fd, &itmp, sizeof(int)) != sizeof(int))
			|| itmp >= len->nb_txtrs))
		return (-55);
	if ((itmp = check_sec_walls(fd, len)))
		return (itmp);
	return (check_sec_props(fd));
}

int			check_sectors(int fd, t_slen *len)
{
	int x;
	int rtn;

	if (check_balise(fd, "🚧", -5))
		return (-5);
	if ((read(fd, &len->nb_sects, sizeof(int)) != sizeof(int))
			|| len->nb_sects < 0)
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

static int	check_one_enemy(int fd)
{
	int		tmp;
	double	dtmp;

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

int			check_enemies(int fd)
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
