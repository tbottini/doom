/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_readfileeditor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 07:21:30 by magrab            #+#    #+#             */
/*   Updated: 2019/08/13 07:21:30 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_pilier	*find_pillar_from_game(t_pillar *pillars, t_pillar *to_find,
	t_lstpil pillst)
{
	int x;

	x = 0;
	while (&(pillars[x]) != to_find)
	{
		pillst = pillst->next;
		x++;
	}
	return (pillst);
}

void		add_walls(t_game *g, t_editor *e, t_sector *gsec, t_secteur *sec)
{
	int		y;
	t_mur	*mur;

	y = 0;
	while (y < gsec->len)
	{
		mur = ft_wallpushend(&sec->murs,
			find_pillar_from_game(g->pillars, gsec->wall[y].pillar, e->pillist),
			find_pillar_from_game(g->pillars, gsec->wall[y].next, e->pillist),
			find_texture(e->txtrgame, e->txtrname,
				g->surfpath[gsec->wall[y].txtr.id]));
		add_wall_prop(g, e, &gsec->wall[y], mur);
		mur->level = gsec->wall[y].level;
		mur->portal_id = gsec->wall[y].status;
		y++;
	}
}
