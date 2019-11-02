/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:23:01 by magrab            #+#    #+#             */
/*   Updated: 2018/11/15 15:37:43 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	size_t x;
	size_t y;

	x = 0;
	while (dst[x])
		x++;
	y = 0;
	while (src[y])
	{
		dst[x + y] = src[y];
		y++;
	}
	dst[x + y] = '\0';
	return (dst);
}
