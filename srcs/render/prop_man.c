/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prop_man.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:02:07 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 15:44:07 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
**	on determine la position gauche et droite du props sur le mur
**	et puis on le convertie en pourcentage
*/

void				prop_init(t_prop *prop, t_wall *wall)
{
	double			hyp;
	double			hyp_pos;
	t_fvct2			diff;

	diff.x = wall->next->p.x - wall->pillar->p.x;
	diff.y = wall->next->p.y - wall->pillar->p.y;
	hyp = sqrt(diff.x * diff.x + diff.y * diff.y);
	diff.x = prop->pos.x - wall->pillar->p.x;
	diff.y = prop->pos.y - wall->pillar->p.y;
	hyp_pos = sqrt(diff.x * diff.x + diff.y * diff.y);
	prop->percent.x = 1 - (hyp_pos - 0.5) / (hyp);
	prop->percent.y = 1 - (hyp_pos + 0.5) / (hyp);
}

/*
**	va iterer sur tout les props d'un tableau
*/

void				prop_iter(t_prop *prop, int len
	, void (*prop_iter)(t_prop*))
{
	int				i;

	i = 0;
	while (i <= len)
	{
		prop_iter(&prop[i]);
		i++;
	}
}

/*
**	va iterer sur tous les props d'un tableau avec
**		une fonction acceptant une structure quelconque
*/

void				prop_iter_v(t_prop *prop, int len
	, void (*prop_iter)(t_prop*, void*), void *sup)
{
	int				i;

	i = 0;
	while (i <= len)
	{
		prop_iter(&prop[i], sup);
		i++;
	}
}

void				prop_init_render(t_prop *prop, void *arch)
{
	t_arch			*arc;
	t_vct2			px;

	arc = (t_arch*)arch;
	px = prop_get_screen_pixel(prop, arc);
}
