/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:03:15 by magrab            #+#    #+#             */
/*   Updated: 2018/11/19 13:11:33 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		var;
	int		neg;

	if (!*str)
		return (0);
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	var = 0;
	neg = (*str == '-' ? -1 : 1);
	if (*str == '+' || *str == '-')
		str++;
	while (*str && ft_isdigit(*str))
	{
		var = var * 10 + *str - 48;
		str++;
	}
	return (neg * var);
}
