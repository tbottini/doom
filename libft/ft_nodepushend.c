/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodepushend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 17:32:58 by magrab            #+#    #+#             */
/*   Updated: 2018/12/19 17:33:16 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tab		ft_nodepushend(t_tab *start, t_type data)
{
	t_tab t;

	if (!start)
		return (NULL);
	if (!(*start))
		return (*start = ft_nodenew(data));
	t = *start;
	while (t->next)
		t = t->next;
	if (!(t->next = ft_nodenew(data)))
		return (NULL);
	t->next->prvs = t;
	return (t->next);
}
