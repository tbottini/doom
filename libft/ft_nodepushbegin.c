/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodepushbegin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 17:31:31 by magrab            #+#    #+#             */
/*   Updated: 2018/12/19 17:31:57 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tab		ft_nodepushbegin(t_tab *start, t_type data)
{
	t_tab t;

	if (!start)
		return (NULL);
	if (!(*start))
		return (*start = ft_nodenew(data));
	t = *start;
	if (!(*start = ft_nodenew(data)))
		return (NULL);
	(*start)->next = t;
	t->prvs = (*start);
	return (*start);
}
