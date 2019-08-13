/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lil_savefile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 05:12:23 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 05:12:24 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	write_balise(int fd, char *balise)
{
	int	*x;

	x = (int *)balise;
	write(fd, x, sizeof(int));
}

void	write_one_wall(int fd, t_lstmur wall)
{
	write(fd, &wall->pil1->id, sizeof(int));
	write(fd, &wall->pil2->id, sizeof(int));
	write(fd, &wall->idtxtr, sizeof(int));
	write(fd, &wall->portal_id, sizeof(t_portal_id));
	write(fd, &wall->level, sizeof(int));
	if (wall->portal_ptr)
		write(fd, &wall->portal_ptr->id, sizeof(int));
	else
		write(fd, "\xff\xff\xff\xff", sizeof(int));
	write_wall_props(fd, wall->wproplist);
}

void	write_sec_walls(int fd, t_lstmur wall)
{
	t_lstmur	tmp;
	int			nbwalls;

	write_balise(fd, "💦");
	tmp = wall;
	nbwalls = 0;
	while (tmp)
	{
		tmp->id = nbwalls;
		nbwalls++;
		tmp = tmp->next;
	}
	write(fd, &nbwalls, sizeof(int));
	tmp = wall;
	while (tmp)
	{
		write_one_wall(fd, tmp);
		tmp = tmp->next;
	}
	write_balise(fd, "⛱");
}

void	write_sec_props(int fd, t_secteur *sect, t_lstent props)
{
	int			c;
	t_lstent	tmp;

	write_balise(fd, "🚽");
	c = 0;
	tmp = props;
	while (tmp)
	{
		if (tmp->stat.sector == sect && !(ISENEMY(tmp->stat.type)))
			c++;
		tmp = tmp->next;
	}
	write(fd, &c, sizeof(int));
	tmp = props;
	while (tmp)
	{
		if (tmp->stat.sector == sect && !(ISENEMY(tmp->stat.type)))
			write_one_prop(fd, tmp);
		tmp = tmp->next;
	}
	write_balise(fd, "💩");
}

void	write_sectors(int fd, t_editor *edit)
{
	t_secteur	*sec;
	int			nbsectors;

	write_balise(fd, "🚧");
	nbsectors = 0;
	sec = edit->sectors;
	while (sec)
	{
		sec->id = nbsectors;
		nbsectors++;
		sec = sec->next;
	}
	write(fd, &nbsectors, sizeof(int));
	sec = edit->sectors;
	while (sec)
	{
		write_one_sector(fd, sec, edit->ennlist);
		sec = sec->next;
	}
	write_balise(fd, "🏠");
}
