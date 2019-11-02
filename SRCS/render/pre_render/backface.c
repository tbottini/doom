/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backface.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 01:52:58 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/23 05:28:35 by tbottini         ###   ########.fr       */
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

int			zline_wall(t_arch *arch, t_pil_render *render_stuff
	, double len_pillar)
{
	(void)render_stuff;
	if (len_pillar > arch->portal.zline[arch->px.x])
	{
		arch->portal.zline[arch->px.x] = len_pillar;
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

int			zline_portal(t_arch *arch, t_pil_render *render_stuff
	, double len_pillar)
{
	int		px_portal;

	px_portal = arch->px.x - render_stuff->px_start;
	if (len_pillar > arch->portal.zline[arch->px.x])
	{
		render_stuff->borne_tmp.zline[px_portal] = len_pillar;
		arch->portal.zline[arch->px.x] = 0;
		return (1);
	}
	render_stuff->borne_tmp.zline[px_portal] = arch->portal.zline[arch->px.x];
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

int			zline_compare(t_arch *arch, double len_pillar, int px)
{
	return (len_pillar >= arch->portal.zline[px]);
}
