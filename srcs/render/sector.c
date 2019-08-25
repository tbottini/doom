/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 16:39:00 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/25 21:08:34 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sector.h"

t_sector		*sector_new(void)
{
	t_sector	*new;

	new = (t_sector *)malloc(sizeof(t_sector));
	if (!new)
		return (NULL);
	new->gravity.x = 0;
	new->gravity.y = 0;
	new->gravity.z = G_MOON;
	new->enemys = NULL;
	return (new);
}

void			sector_props_init(t_sector *sector)
{
	(void)sector;
}

void			sector_wall_props_init(t_sector *sector)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < sector->len)
	{
		while (j <= sector->wall[i].nb_props)
		{
			prop_init(&sector->wall[i].props[j], &sector->wall[i]);
			j++;
		}
		j = 0;
		i++;
	}
}

void			sector_iter(t_sector *sector, int len
	, void (sector_effector)(t_sector*))
{
	int			i;

	i = 0;
	while (i < len)
	{
		sector_effector(&sector[i]);
		i++;
	}
}
