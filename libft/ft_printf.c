/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Max <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:16:40 by Max               #+#    #+#             */
/*   Updated: 2019/01/22 16:40:46 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf(const char *str, ...)
{
	va_list		ap;
	int			x;

	va_start(ap, str);
	x = -1;
	while (str[++x])
	{
		if (str[x] == '%' && ++x)
		{
			if (str[x] == 'd')
				ft_putnbr(va_arg(ap, int));
			else if (str[x] == 'c')
				ft_putchar(va_arg(ap, int));
			else if (str[x] == 's' || str[x] == 'p')
				ft_putstr(va_arg(ap, char *));
		}
		else
			ft_putchar(str[x]);
	}
	va_end(ap);
	return (0);
}
