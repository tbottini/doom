/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:23:23 by magrab            #+#    #+#             */
/*   Updated: 2018/11/15 15:38:18 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	map_strlen(const char *s)
{
	if (*s != '\0')
		return (1 + map_strlen(s + 1));
	return (1);
}

char			*ft_strmap(char const *s, char (*f)(char))
{
	char	*tmp;
	size_t	x;

	tmp = NULL;
	if (s)
	{
		x = map_strlen(s);
		if (!(tmp = (char *)malloc(x * sizeof(char))))
			return (NULL);
		tmp[--x] = '\0';
		while (x-- > 0)
		{
			tmp[x] = (*f)(s[x]);
		}
	}
	return (tmp);
}
