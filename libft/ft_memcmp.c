/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:19:29 by magrab            #+#    #+#             */
/*   Updated: 2018/11/15 15:35:02 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	x;

	x = -1;
	while (++x < n)
		if (*(unsigned char *)(s1 + x) != *(unsigned char *)(s2 + x))
			return (*(unsigned char *)(s1 + x) - *(unsigned char *)(s2 + x));
	return (0);
}
