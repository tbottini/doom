/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 20:45:43 by akrache           #+#    #+#             */
/*   Updated: 2019/07/09 21:21:43 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_entity	*ft_newenemy(t_vct2 loc, int type, t_secteur *sctr)
{
	t_entity *t;

	if (!(t = malloc(sizeof(t_entity))))
		return (NULL);
	t->stat.mursec = NULL;
	t->stat.mur = NULL;
	t->stat.pos.x = loc.x;
	t->stat.pos.y = loc.y;
	if (ISWALLPROP(type))
		t->stat.roty = 50;
	else
		t->stat.roty = 0;
	t->stat.sector = sctr;
	t->stat.type = type;
	t->prev = NULL;
	t->next = NULL;
	return (t);
}

void		ft_removeenemy(t_lstent *start, t_entity **pil)
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

void		ft_removeenemywithstat(t_lstent *start, t_ecoord **pil)
{
	t_lstent curr;

	if (!pil || !(*pil))
		return ;
	curr = *start;
	while (curr)
	{
		if (&curr->stat == *pil)
		{
			ft_removeenemy(start, &curr);
			*pil = NULL;
			return ;
		}
		curr = curr->next;
	}
}

t_entity	*ft_enemypushend(t_lstent *s, t_vct2 loc, int type, t_secteur *sctr)
{
	t_entity *t;

	if (!s)
		return (NULL);
	if (!(*s))
		return (*s = ft_newenemy(loc, type, sctr));
	t = *s;
	while (t->next)
		t = t->next;
	if (!(t->next = ft_newenemy(loc, type, sctr)))
		return (NULL);
	t->next->prev = t;
	return (t->next);
}

void		ft_clear_entity_list(t_lstent *start)
{
	t_entity *tmp;

	if (!start || !(*start))
		return ;
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

/*
** static int	check_diff(t_lstent un, t_lstent deux)
** {
** 	if (un->stat.pos.x != deux->stat.pos.x
** 		|| un->stat.pos.y != deux->stat.pos.y)
** 		return (0);
** 	return (1);
** }
**
** void		ft_nodeprint_enemy(t_lstent node)
** {
** 	t_entity *curr;
**
** 	if (!node)
** 	{
** 		ft_printf("xxx\n");
** 		return ;
** 	}
** 	curr = node;
** 	while (curr)
** 	{
** 		ft_printf("%d %d", curr->stat.pos.x, curr->stat.pos.y);
** 		if (curr->next)
** 			ft_printf("%c-> ", check_diff(curr->next->prev, curr) ? ' ' : '!');
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
