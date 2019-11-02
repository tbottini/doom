/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:19:05 by magrab            #+#    #+#             */
/*   Updated: 2018/11/19 14:54:35 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nbrlen(int n)
{
	int x;

	x = (n < 0 ? 1 : 0);
	while (n)
	{
		n /= 10;
		x++;
	}
	return (x);
}

static char		*itoa_str(size_t size)
{
	char	*tmp;

	if (size == 0)
	{
		if (!(tmp = (char *)malloc((2) * sizeof(char))))
			return (NULL);
		tmp[0] = '0';
		tmp[1] = 0;
		return (tmp);
	}
	if (!(tmp = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	*(tmp + size) = 1;
	return (tmp + size);
}

char			*ft_itoa(int n)
{
	char	*p;

	p = itoa_str(nbrlen(n));
	if (p && *p != '0')
	{
		*p = 0;
		if (n >= 0 && p)
			while (n != 0)
			{
				*--p = '0' + (n % 10);
				n /= 10;
			}
		else if (p)
		{
			while (n != 0)
			{
				*--p = '0' - (n % 10);
				n /= 10;
			}
			*--p = '-';
		}
	}
	return (p);
}
