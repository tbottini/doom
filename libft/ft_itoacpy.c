/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoacpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:19:05 by magrab            #+#    #+#             */
/*   Updated: 2018/11/19 14:54:35 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** char* must be of enough size
*/

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

static char		*if_zero(char *p)
{
	p[0] = '0';
	p[1] = 0;
	return (p);
}

char			*ft_itoacpy(char *p, int n)
{
	if (n == 0)
		return (if_zero(p));
	p += nbrlen(n);
	if (p)
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
