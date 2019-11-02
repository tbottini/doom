/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodeprint_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:19:48 by magrab            #+#    #+#             */
/*   Updated: 2019/02/16 14:38:45 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_nodeprint_int(t_tab node)
{
	t_tab pos;

	if (!node)
	{
		ft_printf("xxx");
		return ;
	}
	pos = node;
	while (pos)
	{
		ft_printf("%d", pos->data);
		if (pos->next)
			ft_printf("%c-> ", pos->next->prvs->data == pos->data ? ' ' : '!');
		pos = pos->next;
	}
}
