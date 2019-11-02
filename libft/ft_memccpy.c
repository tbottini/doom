/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:19:23 by magrab            #+#    #+#             */
/*   Updated: 2018/11/15 15:32:41 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	x;

	x = 0;
	while (x < n)
	{
		if (*(char *)(src + x) == (char)c)
		{
			*(char *)(dst + x) = *(char *)(src + x);
			return (dst + x + 1);
		}
		*(char *)(dst + x) = *(char *)(src + x);
		x++;
	}
	return (NULL);
}
