/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_noderm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:05:03 by magrab            #+#    #+#             */
/*   Updated: 2019/02/16 14:35:29 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_noderm(t_tab *start)
{
	t_tab	prev;
	t_tab	next;
	t_tab	node;

	prev = NULL;
	next = NULL;
	if (!start || !(*start))
		return ;
	node = *start;
	*start = NULL;
	if (node->next)
		next = node->next;
	if (node->prvs)
		prev = node->prvs;
	else
		*start = node->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prvs = prev;
	free(node);
}
