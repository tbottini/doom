/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 15:25:22 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 15:25:42 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "calcul.h"

double					door_open_percent(t_arch *arch, int flag)
{
	double				percent_open;

	percent_open = (arch->timestamp - arch->wall->ots)
		/ ((double)DOOR_OPEN_TIME);
	if (flag == OPEN_DOOR)
		percent_open = 1 - percent_open;
	if (percent_open > 1)
		percent_open = 1;
	if (percent_open < 0)
		percent_open = 0;
	return (percent_open);
}

t_fvct2					door_get_inter_pos(t_arch *arch
	, t_pil_render *render_stuff)
{
	double	percent_local;
	t_fvct2	inter;

	percent_local = (arch->shift_txtr.x - (1 - render_stuff->perc_open))
		/ (arch->shift_txtr.x - arch->shift_txtr.y);
	if (percent_local > 1)
		inter = arch->next;
	else if (percent_local < 0)
		inter = arch->pillar;
	else
	{
		inter.x = arch->pillar.x + percent_local
			* (arch->next.x - arch->pillar.x);
		inter.y = arch->pillar.y + percent_local
			* (arch->next.y - arch->pillar.y);
	}
	return (inter);
}

int						door_get_px_inter(t_arch *arch
	, t_pil_render *render_stuff)
{
	return (arch->sdl->size.x / 2 - arch->sdl->size.x / 2
		* (render_stuff->inter.y / render_stuff->inter.x));
}

/*
**	door_split determine les info pour le rendu avec pillar_to_pillar
**	on determine :
**	-le taux d'ouverture de la porte
**	-la position du bout de la porte
**	-son px, les nouveau shift_txtr de la texture pour la porte
*/

void					door_split_info(t_arch *arch, t_pil_render *render_stuff
	, int flag)
{
	render_stuff->open_invert = (arch->px.x > arch->px.y);
	render_stuff->perc_open = door_open_percent(arch, flag);
	render_stuff->inter = door_get_inter_pos(arch, render_stuff);
	if (render_stuff->inter.x < 0)
	{
		render_stuff->px_inter = arch->px.x;
		return ;
	}
	render_stuff->px_inter = door_get_px_inter(arch, render_stuff);
	render_stuff->st_door.x = 1 - render_stuff->perc_open
		+ (1 - arch->shift_txtr.x);
	if (arch->shift_txtr.y > 1 - render_stuff->perc_open)
	{
		render_stuff->st_door.y = 1 - (arch->shift_txtr.y
			- (1 - render_stuff->perc_open));
	}
	else
	{
		render_stuff->st_door.y = 1;
	}
}
