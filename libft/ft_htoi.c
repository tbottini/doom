/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 18:06:39 by magrab            #+#    #+#             */
/*   Updated: 2019/01/22 16:39:30 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_htoi(char *hex)
{
	int		val;
	int		nb;
	int		i;

	if (!hex || !hex[0] || !hex[1] || ft_strlen(hex) > 10
				|| (hex[1] != 'x' && hex[1] != 'X') || hex[0] != '0'
				|| (ft_strlen(hex) == 10 && hex[2] > '7'))
		return (0);
	nb = 0;
	i = 2;
	while (hex[i])
	{
		if (hex[i] >= '0' && hex[i] <= '9')
			val = hex[i] - '0';
		else if (hex[i] >= 'a' && hex[i] < 'g')
			val = hex[i] - 'a' + 10;
		else if (hex[i] >= 'A' && hex[i] < 'G')
			val = hex[i] - 'A' + 10;
		else
			break ;
		nb = nb * 16 + val;
		i++;
	}
	return (nb);
}
