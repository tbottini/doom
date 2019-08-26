/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   borne_method.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:11:00 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 14:11:19 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
**	sauvegarde toute les configuration de borne dans une structure
**	dans une zone (la zone est les limite de px)
**	la sauvegarde de la profondeur avec le zline se fera au
**	fur et a mesure dans le pillar_to_pillar
*/

t_borne				*borne_svg(t_arch *arch, t_borne *borne, t_vct2 px)
{
	int		len;

	len = px.y - px.x;
	borne->b_left = arch->portal.b_left;
	borne->b_right = arch->portal.b_right;
	borne->pillar = arch->portal.pillar;
	borne->next = arch->portal.next;
	borne->sector_svg = arch->sector;
	if (len > 0)
		borne_init(borne, len);
	return (borne);
}

/*
**	recharge une borne dans la borne arch
**	(une borne anciennement sauvegarde...)
*/

void				borne_load(t_arch *arch, t_borne *borne, t_vct2 px_draw)
{
	int				i;

	i = 0;
	arch->portal.b_left = borne->b_left;
	arch->portal.b_right = borne->b_right;
	while (px_draw.x < px_draw.y)
	{
		arch->portal.b_up[px_draw.x] = borne->b_up[i];
		arch->portal.b_down[px_draw.x] = borne->b_down[i];
		arch->portal.zline[px_draw.x] = borne->zline[i];
		px_draw.x++;
		i++;
	}
	arch->portal.pillar = borne->pillar;
	arch->portal.next = borne->next;
	arch->sector = borne->sector_svg;
	borne_free(borne);
}
