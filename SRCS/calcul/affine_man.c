/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine_man.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:00:07 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 16:13:02 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_affine		affine_def(double a, double b)
{
	return ((t_affine){a, b, 0});
}

double			affine_val(t_affine affine, double x)
{
	return (affine.a * x + affine.b);
}

double			affine_val_index(t_affine affine, double y)
{
	return ((y - affine.b) / affine.a);
}

t_affine		affine_points(t_fvct2 point1, t_fvct2 point2)
{
	t_affine	fct;

	fct.a = (point2.y - point1.y) / (point2.x - point1.x);
	fct.b = point1.y - fct.a * point1.x;
	return (fct);
}
