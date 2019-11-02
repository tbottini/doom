/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodeclean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 20:47:16 by magrab            #+#    #+#             */
/*   Updated: 2019/07/27 20:47:19 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_nodeclean(t_tab *start)
{
	t_tab tmp;

	if (!start || !(*start))
		return ;
	tmp = *start;
	if (tmp->next)
		ft_nodeclean(&tmp->next);
	free(tmp);
	*start = NULL;
}
