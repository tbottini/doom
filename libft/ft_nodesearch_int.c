/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodesearch_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:24:37 by magrab            #+#    #+#             */
/*   Updated: 2019/02/16 13:08:16 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tab	ft_nodesearch_int(t_tab node, t_type elem)
{
	t_tab pos;

	if (!node)
		return (NULL);
	pos = node;
	while (pos)
	{
		if (pos->data == elem)
			return (pos);
		pos = pos->next;
	}
	return (NULL);
}
