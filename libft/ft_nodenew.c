/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 17:30:36 by magrab            #+#    #+#             */
/*   Updated: 2018/12/19 17:31:19 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tab		ft_nodenew(t_type data)
{
	t_tab	t;

	if (!(t = malloc(sizeof(t_node))))
		return (NULL);
	t->data = data;
	t->prvs = NULL;
	t->next = NULL;
	return (t);
}
