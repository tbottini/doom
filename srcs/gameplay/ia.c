/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 11:46:33 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 03:33:58 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool			is_passed(t_sector *sector, t_sector **passed, int index)
{
	int i;

	i = 0;
	while (i < index)
	{
		if (sector == passed[i])
			return (true);
		i++;
	}
	return (false);
}

void			armandtificial_intelligence(t_doom *doom)
{
	int			index;
	t_sector	*passed[doom->game.len.nb_sects];

	index = 0;
	is_around(doom, doom->game.player.stat.sector, passed, &index);
}
