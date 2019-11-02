/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodepushat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 17:32:23 by magrab            #+#    #+#             */
/*   Updated: 2018/12/19 17:32:47 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tab		ft_nodepushat(t_tab *start, t_type data, size_t pos)
{
	t_tab t;
	t_tab tmp;

	if (!start)
		return (NULL);
	t = *start;
	while (t && t->next && pos--)
		t = t->next;
	if (pos != 0)
		return (NULL);
	if (!t)
		return (*start = ft_nodenew(data));
	tmp = t->prvs;
	if (tmp)
	{
		if (!(tmp->next = ft_nodenew(data)))
			return (NULL);
		tmp->next->next = t;
		return (tmp->next);
	}
	if (!(*start = ft_nodenew(data)))
		return (NULL);
	(*start)->next = t;
	t->prvs = (*start);
	return (*start);
}
