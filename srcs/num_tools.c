/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:36:06 by tbottini          #+#    #+#             */
/*   Updated: 2019/05/03 12:59:54 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

double		double_modulo(double num)
{
	num = (int)num % 360 + num - (int)num;
	return (num);
}

double		angle_adaptater(double angle)
{
	if (angle < 0.0)
		angle += 360.0;
	else if (angle > 360.0)
		angle = double_modulo(angle);
	return (angle);
}
