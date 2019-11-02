/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_checkfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 21:25:11 by magrab            #+#    #+#             */
/*   Updated: 2019/08/15 21:25:12 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int			check_one_prop(int fd)
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
	else if ((read(fd, &var_a, sizeof(int)) != sizeof(int)) || var_a < -1)
		return (-75);
	if ((read(fd, &dtmp, sizeof(double)) != sizeof(double)))
		return (-76);
	if ((read(fd, &dtmp, sizeof(double)) != sizeof(double)))
		return (-77);
	return (0);
}

int			check_wall_props(int fd)
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

static int	check_one_wall(int fd, t_slen *len)
{
	int			tmp;
	t_portal_id	ptmp;

	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_pills))
		return (-61);
	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_pills))
		return (-62);
	if (((read(fd, &tmp, sizeof(int)) != sizeof(int)) || tmp >= len->nb_txtrs))
		return (-63);
	if (((read(fd, &ptmp, sizeof(t_portal_id)) != sizeof(t_portal_id))))
		return (-64);
	if (((read(fd, &tmp, sizeof(int)) != sizeof(int))))
		return (-64);
	if (((read(fd, &tmp, sizeof(int)) != sizeof(int))
			|| tmp >= len->nb_sects || tmp < -1))
		return (-65);
	return (check_wall_props(fd));
}

int			check_sec_walls(int fd, t_slen *len)
{
	int		x;
	int		nbw;
	int		rtn;

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

int			check_sec_props(int fd)
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
