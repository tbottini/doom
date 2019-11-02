/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 19:29:06 by magrab            #+#    #+#             */
/*   Updated: 2018/08/05 23:00:26 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isprime(int nb)
{
	unsigned long	x;

	if (nb <= 1)
		return (0);
	x = 1;
	while (x++)
	{
		if ((unsigned long)nb < x * x)
			return (1);
		if ((unsigned long)nb % x == 0)
			return (0);
	}
	return (0);
}
