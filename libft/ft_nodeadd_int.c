/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodeadd_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 13:34:30 by magrab            #+#    #+#             */
/*   Updated: 2019/02/16 13:34:37 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tab		ft_nodeadd_int(t_tab *start, t_type data)
{
	t_tab t;

	if (!start)
		return (NULL);
	if (!(*start))
		return (*start = ft_nodenew(data));
	t = *start;
	while (t->next && t->data != data)
		t = t->next;
	if (t->data == data || !(t->next = ft_nodenew(data)))
		return (NULL);
	t->next->prvs = t;
	return (t->next);
}
