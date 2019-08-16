/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 12:57:58 by akrache           #+#    #+#             */
/*   Updated: 2019/07/30 12:58:26 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int	orientation(t_fvct3 p, t_fvct3 q, t_fvct3 r)
{
	double val;

	val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0)
		return (0);
	return (val > 0) ? 1 : 2;
}

/*
** Returns 1 if the segments [p1, q1] and [p2, q2] intersect, 0 Otherwise
*/

int			vector_intersect(t_fvct3 p1, t_fvct3 q1, t_fvct3 p2, t_fvct3 q2)
{
	if (orientation(p1, q1, p2) != orientation(p1, q1, q2)
		&& orientation(p2, q2, p1) != orientation(p2, q2, q1))
		return (1);
	return (0);
}
