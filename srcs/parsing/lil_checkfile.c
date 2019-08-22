/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lil_checkfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 21:24:22 by magrab            #+#    #+#             */
/*   Updated: 2019/08/15 21:24:23 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int			check_balise(int fd, char *balise, int ret)
{
	int *x;
	int y;

	x = (int *)balise;
	read(fd, &y, sizeof(y));
	if (*x != y)
		return (ret);
	return (0);
}

static int	check_one_pillar(int fd)
{
	t_fvct2 p;

	if ((read(fd, &p.x, sizeof(double))) != sizeof(double))
		return (-32);
	if (read(fd, &p.y, sizeof(double)) != sizeof(double))
		return (-33);
	return (0);
}

int			check_pillars(int fd, t_slen *len)
{
	int x;
	int rtn;

	if (check_balise(fd, "⛩", -3))
		return (-3);
	if ((read(fd, &len->nb_pills, sizeof(int)) != sizeof(int))
			|| len->nb_pills < 0)
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
