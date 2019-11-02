/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:22:41 by magrab            #+#    #+#             */
/*   Updated: 2018/11/15 15:35:39 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	x;

	if (dst < src)
	{
		x = -1;
		while (++x < n)
			*(char *)(dst + x) = *(char *)(src + x);
	}
	else
	{
		while (n--)
			*(char *)(dst + n) = *(char *)(src + n);
	}
	return (dst);
}
