/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_noderm_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:26:52 by magrab            #+#    #+#             */
/*   Updated: 2019/02/16 16:07:06 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_noderm_int(t_tab *start, t_type elem)
{
	t_tab pos;

	if (!start || !(*start))
		return (-1);
	if ((*start)->data == elem)
	{
		ft_noderm(start);
		return (1);
	}
	pos = (*start)->next;
	while (pos)
	{
		if (pos->data == elem)
		{
			ft_noderm(&pos);
			return (1);
		}
		pos = pos->next;
	}
	return (0);
}
