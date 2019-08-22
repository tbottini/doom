/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 11:30:57 by magrab            #+#    #+#             */
/*   Updated: 2019/08/16 11:30:57 by magrab           ###   ########.fr       */
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
