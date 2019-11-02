/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 10:53:43 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 14:27:49 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

double			percent_interpolation2d(t_arch *a)
{
	t_affine	px_affine;
	t_affine	wall_affine;
	t_fvct2		inter;
	double		percent;

	px_affine.a = ((a->sdl->size.x / 2) - a->px.x) / a->cam->d_screen;
	px_affine.b = 0;
	if (a->pillar.y == a->next.y)
	{
		inter.x = a->next.x;
		inter.y = px_affine.a * inter.x;
		percent = (inter.y - a->pillar.y) / (a->next.y - a->pillar.y);
	}
	else
	{
		wall_affine.a = (a->next.y - a->pillar.y) / (a->next.x - a->pillar.x);
		wall_affine.b = a->pillar.y - wall_affine.a * a->pillar.x;
		inter = interpolation_linear(wall_affine, px_affine);
		percent = (inter.x - a->pillar.x) / (a->next.x - a->pillar.x);
	}
	percent = percent * (a->shift_txtr.y - a->shift_txtr.x) + a->shift_txtr.x;
	if (percent < 0 || percent > 1)
		return ((percent < 0) ? 0 : 1);
	return (percent);
}

/*
**	renvoie l'index de la texture associee au pixel de l'ecran
**	l'affine du mur est le decal(y) selon depth(x)
**	pblm on peut avoir un mur face au joueur formant
**	une affine constante verticalement
*/

uint32_t		texture_interpolation2d(t_arch *arch, t_txtr *txtr)
{
	double		percent;

	percent = percent_interpolation2d(arch);
	return (percent * txtr->w);
}

uint32_t		texture_prop_interpolation2d(t_arch *arch, t_txtr *txtr
	, t_prop *prop)
{
	double		percent;

	percent = percent_interpolation2d(arch);
	percent = 1 - (percent - prop->percent.x)
		/ (prop->percent.y - prop->percent.x);
	if (percent < 0)
		return (0);
	return (percent * txtr->w);
}

/*
**	redefinit le pourcentage de textures (en donnant le pourcentage actuel)
**	les deux distance et le nouveau point d'intersection
**	-flag definit quel pillier doit changer
*/

void			pillar_virtual_move(t_arch *arch, t_fvct2 inter, int flag)
{
	double		percent_tmp;
	double		*percent;
	t_fvct2		*pillar;

	if (flag == PILLAR)
	{
		percent = &arch->shift_txtr.x;
		pillar = &arch->pillar;
	}
	else
	{
		percent = &arch->shift_txtr.y;
		pillar = &arch->next;
	}
	if (arch->pillar.x == arch->next.x)
		percent_tmp = (inter.y - arch->pillar.y)
		/ (arch->next.y - arch->pillar.y);
	else
		percent_tmp = (inter.x - arch->pillar.x)
		/ (arch->next.x - arch->pillar.x);
	*percent = percent_tmp * (arch->shift_txtr.y
		- arch->shift_txtr.x) + arch->shift_txtr.x;
	*pillar = inter;
}
