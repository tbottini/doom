/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 11:46:33 by akrache           #+#    #+#             */
/*   Updated: 2019/07/25 14:02:35 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		is_around(t_stat *stat, t_stat *target)
{
	if (stat->sector == target->sector)
		return (1);//
	return (0);
}

void	update_enemy_rotation(t_enemy *enemy, t_fvct3 pos)
{
	enemy->stat.rot.y = atan2(pos.x - enemy->stat.pos.x, pos.y - enemy->stat.pos.y);
}