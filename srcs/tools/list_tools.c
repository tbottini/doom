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

t_lstpil ft_newpillar(t_vct2 loc)
{
	t_lstpil t;

	if (!(t = malloc(sizeof(t_pilier))))
		return (NULL);
	t->pos = loc;
	t->prvs = NULL;
	t->next = NULL;
	return (t);
}

void ft_removepillar(t_lstpil *start, t_lstpil *pil)
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

t_lstpil ft_pillarpushend(t_lstpil *start, t_vct2 loc)
{
	t_lstpil t;

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

static int check_diff(t_lstpil un, t_lstpil deux)
{
	if (un->pos.x != deux->pos.x || un->pos.y != deux->pos.y)
		return (0);
	return (1);
}

void ft_nodeprint_pillar(t_lstpil node)
{
	t_lstpil curr;

	if (!node)
	{
		ft_printf("xxx\n");
		return;
	}
	curr = node;
	while (curr)
	{
		ft_printf("%d %d", curr->pos.x, curr->pos.y);
		if (curr->next)
			ft_printf("%c-> ", check_diff(curr->next->prvs, curr) ? ' ' : '!');
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

void ft_clear_pillar_list(t_lstpil *start)
{
	t_lstpil tmp;

	if (!start || !(*start))
		return;
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
