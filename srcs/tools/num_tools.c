/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:36:06 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/16 11:25:31 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

double		double_modulo(double num)
{
	if (num > 360.0)
		num -= 360.0;
	else if (num < 0.0)
		num += 360.0;
	return (num);
}

double		distance(t_fvct2 vct1, t_fvct2 vct2)
{
	t_fvct2	dist;

	dist.x = vct2.x - vct1.x;
	dist.y = vct2.y - vct1.y;
	return (sqrt((dist.x * dist.x) + (dist.y * dist.y)));
}

double		hypothenuse(t_fvct2 vct)
{
	return (sqrt(vct.x * vct.x + vct.y * vct.y));
}
