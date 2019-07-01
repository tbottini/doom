/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 20:45:43 by akrache           #+#    #+#             */
/*   Updated: 2019/07/01 21:50:12 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_enemy		*ft_newenemy(t_vct2 loc, int type, t_secteur *sctr)
{
	t_enemy *t;

	if (!(t = malloc(sizeof(t_enemy))))
		return (NULL);
	t->stat.pos.x = loc.x;
	t->stat.pos.y = loc.y;
	t->stat.rot.y = 0;
	t->stat.sector = (t_sector *)sctr;
	t->type = type;
	t->prev = NULL;
	t->next = NULL;
	return (t);
}

void		ft_removeenemy(t_lstenn *start, t_enemy **pil)
{
	if (!pil || !(*pil))
		return ;
	if (*pil == *start)
		*start = (*start)->next;
	if ((*pil)->next)
		(*pil)->next->prev = (*pil)->prev;
	if ((*pil)->prev)
		(*pil)->prev->next = (*pil)->next;
	free(*pil);
	*pil = NULL;
}

t_enemy		*ft_enemypushend(t_lstenn *start, t_vct2 loc, int type, t_secteur *sctr)
{
	t_enemy *t;

	if (!start)
		return (NULL);
	if (!(*start))
		return (*start = ft_newenemy(loc, type, sctr));
	t = *start;
	while (t->next)
		t = t->next;
	if (!(t->next = ft_newenemy(loc, type, sctr)))
		return (NULL);
	t->next->prev = t;
	return (t->next);
}

static int	check_diff(t_lstenn un, t_lstenn deux)
{
	if (un->stat.pos.x != deux->stat.pos.x || un->stat.pos.y != deux->stat.pos.y)
		return (0);
	return (1);
}

void		ft_nodeprint_enemy(t_lstenn node)
{
	t_enemy *curr;

	if (!node)
	{
		ft_printf("xxx\n");
		return;
	}
	curr = node;
	while (curr)
	{
		ft_printf("%d %d", curr->stat.pos.x, curr->stat.pos.y);
		if (curr->next)
			ft_printf("%c-> ", check_diff(curr->next->prev, curr) ? ' ' : '!');
		if (curr->next != node)
			curr = curr->next;
		else
		{
			ft_printf("Loop");
			curr = NULL;
		}
	}
	ft_printf("\n");
}

void		ft_clear_enemy_list(t_lstenn *start)
{
	t_enemy *tmp;

	if (!start || !(*start))
		return;
	tmp = *start;
	while (tmp->next && tmp->next != *start)
		tmp = tmp->next;
	while (tmp->prev && tmp->prev != *start)
	{
		tmp = tmp->prev;
		free(tmp->next);
	}
	if (tmp != *start)
		free(tmp);
	free(*start);
	*start = NULL;
}
