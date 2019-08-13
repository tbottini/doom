/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backface.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 17:28:11 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/13 04:44:25 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
**	on recupere la distance brut
**	on la convertit en profondeur
**	on la compare a celle actuelle via l'index
**		si elle est plus proche on renvoie 1 pour qu'on puisse
**		calculer et afficher la colomne
**	tout est inverse car on ne recoit pas la distance mais la taille du pillier
*/

int			z_line_buffer(t_arch *arch, double len_pillar, int px)
{
	if (len_pillar > arch->portal.zline[px])
	{
		arch->portal.zline[px] = len_pillar;
		return (1);
	}
	return (0);
}

int			clean_zline(t_arch *arch, double len_pillar, int px)
{
	if (len_pillar > arch->portal.zline[px])
	{
		arch->portal.zline[px] = 0;
		return (1);
	}
	return (0);
}

/*
**	prepare le zline buffer pour une recursivite
**		met toute les colonnes de portail a 0
**	stocke la plus grande valeur dans le zline tmp qui sera reaffecter
**		apres la recursivite
*/

int			zline_portal(t_arch *arch, double *zline_tmp, double len_pillar,
	int start)
{
	if (len_pillar > arch->portal.zline[arch->px.x])
	{
		zline_tmp[arch->px.x - start] = len_pillar;
		arch->portal.zline[arch->px.x] = 0;
		return (1);
	}
	zline_tmp[arch->px.x - start] = arch->portal.zline[arch->px.x];
	return (0);
}

/*
**	recupere l'index de depart (ancien px perdu avec le parcours)
**	copy et delete le zline_tmp dans le zline_buffer
*/

void		zline_cut(t_arch *arch, double *zline_cut, int start)
{
	int		i;

	i = 0;
	if (!zline_cut)
		return ;
	while (start < arch->px.y)
	{
		arch->portal.zline[start] = zline_cut[i];
		i++;
		start++;
	}
}

int			zline_compare(t_arch *arch, double len_pillar, int px)
{
	return (len_pillar > arch->portal.zline[px]);
}
