/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:23:25 by magrab            #+#    #+#             */
/*   Updated: 2018/11/15 15:38:28 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	mapi_strlen(const char *s)
{
	if (*s != '\0')
		return (1 + mapi_strlen(s + 1));
	return (1);
}

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*tmp;
	size_t	x;
	size_t	y;

	tmp = NULL;
	if (s)
	{
		x = mapi_strlen(s);
		if (!(tmp = (char *)malloc(x * sizeof(char))))
			return (NULL);
		tmp[--x] = '\0';
		y = 0;
		while (x > y)
		{
			tmp[y] = (*f)(y, s[y]);
			y++;
		}
	}
	return (tmp);
}
