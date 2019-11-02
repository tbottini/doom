/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:23:34 by magrab            #+#    #+#             */
/*   Updated: 2018/11/15 15:24:38 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	if (*s == (char)c && c == 0)
		return ((char *)s);
	if (*s)
	{
		if ((tmp = ft_strrchr(s + 1, c)) == NULL)
		{
			if ((char)*s == (char)c)
			{
				return ((char *)s);
			}
		}
		else
			return (tmp);
	}
	return (NULL);
}
