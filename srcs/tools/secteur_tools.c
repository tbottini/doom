/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secteur_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:36:28 by tbottini          #+#    #+#             */
/*   Updated: 2019/07/10 16:48:35 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_lstsec	ft_newsector(SDL_Texture *top, SDL_Texture *sol)
{
	t_lstsec t;

	if (!(t = malloc(sizeof(t_secteur))))
		return (NULL);
	t->murs = NULL;
	t->prvs = NULL;
	t->top = top;
	t->sol = sol;
	t->htop = 500;
	t->hsol = 0;
	t->gravity = 0;
	t->next = NULL;
	return (t);
}

t_lstsec	push_secteur(t_lstsec *node, SDL_Texture *top, SDL_Texture *sol)
{
	t_lstsec tmp;

	if (!node)
		return (NULL);
	else if (!(*node))
		return (*node = ft_newsector(top, sol));
	tmp = (*node);
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = ft_newsector(top, sol)))
		return (NULL);
	tmp->next->prvs = tmp;
	return (tmp->next);
}

void		ft_remove_pillar_from_sector(t_editor *edit, t_lstsec sectors,
	t_lstpil *start, t_pilier **pil)
{
	while (sectors)
	{
		ft_remove_walls_with_pillar(edit, &sectors->murs, *pil);
		sectors = sectors->next;
	}
	ft_removepillar(start, pil);
}

void		ft_clear_secteur(t_lstsec *sec)
{
	t_lstsec tmp;

	if (!sec || !(*sec))
		return ;
	tmp = *sec;
	ft_clear_wall_list(&tmp->murs);
	if (tmp->next)
		tmp->next->prvs = tmp->prvs;
	if (tmp->prvs)
		tmp->prvs->next = tmp->next;
	free(tmp);
	*sec = NULL;
}

void		ft_clear_secteur_list(t_lstsec *start)
{
	t_lstsec tmp;

	if (!start || !(*start))
		return ;
	tmp = *start;
	while (tmp->next && tmp->next != *start)
		tmp = tmp->next;
	while (tmp->prvs)
	{
		ft_clear_wall_list(&tmp->murs);
		tmp = tmp->prvs;
		free(tmp->next);
	}
	ft_clear_wall_list(&tmp->murs);
	free(tmp);
	*start = NULL;
}

/*
** void ft_nodeprint_secteur(t_lstsec node)
** {
** 	t_lstsec curr;
** 	int x;
**
** 	if (!node)
** 	{
** 		ft_printf("xxx\n");
** 		return;
** 	}
** 	curr = node;
** 	x = 0;
** 	while (curr)
** 	{
** 		ft_printf("%d : ", x);
** 		//ft_nodeprint_pillar(*curr->pil1);
** 		//ft_printf("\t");
** 		//ft_nodeprint_pillar(*curr->pil2);
** 		ft_printf("\n");
** 		curr = curr->next;
** 		x++;
** 	}
** }
*/
