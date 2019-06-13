/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mur_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:36:28 by tbottini          #+#    #+#             */
/*   Updated: 2019/04/27 13:13:03 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_lstmur ft_newwall(t_pilier *pil1, t_pilier *pil2)
{
	t_lstmur t;

	if (!(t = malloc(sizeof(t_mur))))
		return (NULL);
	t->pil1 = pil1;
	t->pil2 = pil2;
	t->prvs = NULL;
	t->next = NULL;
	return (t);
}

t_lstmur ft_wallpushend(t_lstmur *start, t_pilier *pil1, t_pilier *pil2)
{
	t_lstmur t;

	ft_printf("New Wall\n");
	if (!start)
		return (NULL);
	if (!(*start))
		return (*start = ft_newwall(pil1, pil2));
	t = *start;
	while (t->next)
		t = t->next;
	if (!(t->next = ft_newwall(pil1, pil2)))
		return (NULL);
	t->next->prvs = t;
	return (t->next);
}

void ft_clear_wall_list(t_lstmur *start)
{
	t_lstmur tmp;

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
