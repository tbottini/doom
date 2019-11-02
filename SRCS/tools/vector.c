/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 11:30:57 by magrab            #+#    #+#             */
/*   Updated: 2019/08/26 14:19:31 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

double			fvct2_angle(t_fvct2 origin, t_fvct2 pos, double rot_origin)
{
	t_fvct2		dist;
	double		angle;

	dist.x = pos.x - origin.x;
	dist.y = pos.y - origin.y;
	angle = atan2(dist.y, dist.x) * TOANGLE;
	if (angle < 0)
		angle = 360 + angle;
	angle = double_modulo(angle - rot_origin);
	if (angle < -180)
		angle += 360;
	else if (angle > 180)
		angle -= 360;
	return (angle);
}

t_fvct2			fvct2_sub(t_fvct2 vct1, t_fvct2 vct2)
{
	return ((t_fvct2)
	{
		vct1.x - vct2.x,
		vct1.y - vct2.y
	});
}

t_fvct2			fvct2_angle_dist(double dist, double angle)
{
	t_fvct2		new_pos;

	new_pos.x = cos((angle) * PI180) * dist;
	new_pos.y = sin((angle) * PI180) * dist;
	return (new_pos);
}
