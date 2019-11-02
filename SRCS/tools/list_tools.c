/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:36:28 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/27 13:13:03 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_pilier	*ft_newpillar(t_vct2 loc)
{
	t_pilier *t;

	if (!(t = malloc(sizeof(t_pilier))))
		return (NULL);
	t->pos = loc;
	t->prvs = NULL;
	t->next = NULL;
	return (t);
}

void		ft_removepillar(t_lstpil *start, t_pilier **pil)
{
	if (!pil || !(*pil))
		return ;
	if (*pil == *start)
		*start = (*start)->next;
	if ((*pil)->next)
		(*pil)->next->prvs = (*pil)->prvs;
	if ((*pil)->prvs)
		(*pil)->prvs->next = (*pil)->next;
	free(*pil);
	*pil = NULL;
}

void		ft_movepillar(t_lstsec sectors, t_pilier *pil, t_vct2 add, int zoom)
{
	t_lstent wprops;
	t_lstmur murs;

	pil->pos.x += add.x * (EDITPREC) / zoom;
	pil->pos.y += add.y * (EDITPREC) / zoom;
	while (sectors)
	{
		murs = sectors->murs;
		while (murs)
		{
			if (murs->pil1 == pil || murs->pil2 == pil)
			{
				wprops = murs->wproplist;
				while (wprops)
				{
					wprops->stat.pos = line_percent(murs->pil1->pos,
						murs->pil2->pos, wprops->stat.roty / 100);
					wprops = wprops->next;
				}
			}
			murs = murs->next;
		}
		sectors = sectors->next;
	}
}

t_pilier	*ft_pillarpushend(t_lstpil *start, t_vct2 loc)
{
	t_pilier *t;

	if (!start)
		return (NULL);
	if (!(*start))
		return (*start = ft_newpillar(loc));
	t = *start;
	while (t->next)
		t = t->next;
	if (!(t->next = ft_newpillar(loc)))
		return (NULL);
	t->next->prvs = t;
	return (t->next);
}

void		ft_clear_pillar_list(t_lstpil *start)
{
	t_pilier *tmp;

	if (!start || !(*start))
		return ;
	tmp = *start;
	while (tmp->next && tmp->next != *start)
		tmp = tmp->next;
	while (tmp->prvs && tmp->prvs != *start)
	{
		tmp = tmp->prvs;
		free(tmp->next);
	}
	if (tmp != *start)
		free(tmp);
	free(*start);
	*start = NULL;
}

/*
** static int check_diff(t_lstpil un, t_lstpil deux)
** {
** 	if (un->pos.x != deux->pos.x || un->pos.y != deux->pos.y)
** 		return (0);
** 	return (1);
** }
**
** void ft_nodeprint_pillar(t_lstpil node)
** {
** 	t_pilier *curr;
**
** 	if (!node)
** 	{
** 		ft_printf("xxx\n");
** 		return;
** 	}
** 	curr = node;
** 	while (curr)
** 	{
** 		ft_printf("%d %d", curr->pos.x, curr->pos.y);
** 		if (curr->next)
** 			ft_printf("%c-> ", check_diff(curr->next->prvs, curr) ? ' ' : '!');
** 		if (curr->next != node)
** 			curr = curr->next;
** 		else
** 		{
** 			ft_printf("Loop");
** 			curr = NULL;
** 		}
** 	}
** 	ft_printf("\n");
** }
*/
