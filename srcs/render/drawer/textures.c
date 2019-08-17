/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 10:53:43 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/17 12:35:38 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "debug.h"

double			percent_interpolation2d(t_arch *arch)
{
	t_affine	px_affine;
	t_affine	wall_affine;
	t_fvct2		inter;
	double		percent;

	px_affine.a = ((arch->sdl->size.x / 2) - arch->px.x) / arch->cam->d_screen;
	px_affine.b = 0;
	if (arch->pillar.y == arch->next.y)
	{
		inter.x = arch->next.x;
		inter.y = px_affine.a * inter.x;
		percent = (inter.y - arch->pillar.y) / (arch->next.y - arch->pillar.y);
	}
	else
	{
		wall_affine.a = (arch->next.y - arch->pillar.y) / (arch->next.x - arch->pillar.x);
		wall_affine.b = arch->pillar.y - wall_affine.a * arch->pillar.x;
		inter = interpolation_linear(wall_affine, px_affine);
		percent = (inter.x - arch->pillar.x) / (arch->next.x - arch->pillar.x);
	}
	percent = percent * (arch->shift_txtr.y -  arch->shift_txtr.x) + arch->shift_txtr.x;
	if (percent < 0)
		return (0);
	else if (percent > 1)
		return (1);
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

uint32_t		texture_prop_interpolation2d(t_arch *arch, t_txtr *txtr, t_prop *prop)
{
	double		percent;

	percent = percent_interpolation2d(arch);
	percent = 1 - (percent - prop->percent.x) / (prop->percent.y - prop->percent.x);
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
		percent_tmp = (inter.y - arch->pillar.y) / (arch->next.y - arch->pillar.y);
	else
		percent_tmp = (inter.x - arch->pillar.x) / (arch->next.x - arch->pillar.x);
	*percent = percent_tmp * (arch->shift_txtr.y - arch->shift_txtr.x) + arch->shift_txtr.x;
	*pillar = inter;
}
