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

t_lstpil ft_pillarpushnext(t_lstpil *pos, t_vct2 loc)
{
	t_lstpil t;

	if (!pos)
		return (0);
	if (!(*pos) || (*pos)->next)
		return (0);
	t = *pos;
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
	(*start)->next = NULL;
	(*start)->prvs = NULL;
	(*start)->pos.x = 0;
	(*start)->pos.y = 0;
	free(*start);
	*start = NULL;
}

int add_pillar(t_editor *edit, int x, int y)
{
	t_vct2 relpos;
	t_lstpil tmp;

	tmp = find_pilier(edit, edit->map, x, y);
	relpos = get_rel_mappos(edit, x, y);
	if (tmp && !tmp->prvs && edit->currpilier != tmp && edit->currpilier->next != tmp && edit->currpilier->prvs != tmp)
	{
		edit->currpilier->next = tmp;
		edit->currpilier->next->prvs = edit->currpilier;
		return (2);
	}
	else if (!(edit->currpilier = ft_pillarpushnext(&edit->currpilier, relpos)))
		return (0);
	return (1);
}
