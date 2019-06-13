/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secteur_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:36:28 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/27 13:13:03 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_lstsec ft_newsector(t_lstpil root)
{
	t_lstsec t;

	if (!(t = malloc(sizeof(t_secteur))))
		return (NULL);
	t->root = root;
	t->prvs = NULL;
	t->next = NULL;
	return (t);
}

t_lstsec init_secteur(void)
{
	t_lstsec sec;
	t_lstpil map;

	if (!(map = ft_newpillar((t_vct2){0, 0})))
		return (NULL);
	if (!(sec = ft_newsector(map)))
	{
		free(map);
		return (NULL);
	}
	sec->prvs = NULL;
	sec->next = NULL;
	return (sec);
}

t_lstsec push_init_secteur(t_lstsec *node)
{
	t_lstsec tmp;
	if (!node || !(*node))
		return (NULL);
	tmp = (*node);
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = init_secteur()))
		return (NULL);
	tmp->next->prvs = tmp;
	return tmp->next;
}

void ft_clear_secteur_list(t_lstsec *start)
{
	t_lstsec tmp;

	if (!start || !(*start))
		return;
	tmp = *start;
	while (tmp->next && tmp->next != *start)
		tmp = tmp->next;
	while (tmp->prvs)
	{
		ft_clear_pillar_list(&tmp->root);
		tmp = tmp->prvs;
		free(tmp->next);
	}
	ft_clear_pillar_list(&tmp->root);
	free(tmp);
	*start = NULL;
}

void ft_nodeprint_secteur(t_lstsec node)
{
	t_lstsec curr;
	int x;

	if (!node)
	{
		ft_printf("xxx\n");
		return;
	}
	curr = node;
	x = 0;
	while (curr)
	{
		ft_printf("%d : ", x);
		ft_nodeprint_pillar(curr->root);
		ft_printf("\n");
		curr = curr->next;
		x++;
	}
}
