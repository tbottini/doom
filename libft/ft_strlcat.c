/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:23:19 by magrab            #+#    #+#             */
/*   Updated: 2018/11/21 16:26:10 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	x;
	size_t	y;

	if (!size)
		return (ft_strlen(src));
	x = 0;
	while (x < size && dst[x])
		x++;
	y = 0;
	while (x + y < size - 1 && src[y])
	{
		if (y + x < size)
			dst[x + y] = src[y];
		y++;
	}
	if (x + y < size)
		dst[x + y] = 0;
	if (size < x)
		return (size + y);
	return (ft_strlen(src) + x);
}
