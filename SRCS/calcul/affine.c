/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 20:45:30 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 16:15:06 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
**	renvoie l'intersection des deux droite affine
**	si .a == -1 alors la fonction verticale
*/

t_fvct2			interpolation_linear(t_affine fct1, t_affine fct2)
{
	t_fvct2		inter;

	if (fct1.b == fct2.b)
		return ((t_fvct2){0, fct1.b});
	else if (fct1.a == fct2.a)
		return ((t_fvct2){0, 0});
	inter.x = (fct2.b - fct1.b) / (fct1.a - fct2.a);
	inter.y = affine_val(fct2, inter.x);
	return (inter);
}

t_affine		affine_points_secur(t_fvct2 point1, t_fvct2 point2)
{
	t_affine	fct;

	if (point1.x == point2.x)
	{
		fct.lock = 1;
		fct.b = point1.x;
	}
	else
	{
		fct.lock = 0;
		fct.a = (point2.y - point1.y) / (point2.x - point1.x);
		fct.b = point1.y - fct.a * point1.x;
	}
	return (fct);
}

/*
**	interpolation lineaire avec gestion des affine lock
*/

int				interpolation_linear_secur(t_affine affine1, t_affine affine2
	, t_fvct2 *inter)
{
	if (affine1.lock && affine2.lock)
		return (0);
	if (affine1.a == affine2.a)
		return (0);
	if (affine1.lock)
		*inter = (t_fvct2){affine1.b, affine_val(affine2, affine1.b)};
	else if (affine2.lock)
		*inter = (t_fvct2){affine2.b, affine_val(affine1, affine2.b)};
	else
	{
		inter->x = (affine2.b - affine1.b) / (affine1.a - affine2.a);
		inter->y = affine_val(affine2, inter->x);
	}
	return (0);
}

t_fvct2			inter(t_fvct2 p1, t_fvct2 p2, t_fvct2 p3, t_fvct2 p4)
{
	t_affine	a;
	t_affine	b;
	t_fvct2		inter;

	a = affine_points_secur(p1, p2);
	b = affine_points_secur(p3, p4);
	interpolation_linear_secur(a, b, &inter);
	return (inter);
}
