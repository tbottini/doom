/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:23:17 by magrab            #+#    #+#             */
/*   Updated: 2018/11/15 15:24:38 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	join_strlen(const char *s)
{
	if (*s != '\0')
		return (1 + join_strlen(s + 1));
	return (0);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		x;
	int		y;

	str = NULL;
	if (s1 && s2)
	{
		if (!(str = (char *)malloc((join_strlen(s1) + join_strlen(s2) + 1)
		* sizeof(char))))
			return (NULL);
		x = -1;
		while (s1[++x])
			str[x] = s1[x];
		y = -1;
		while (s2[++y])
			str[x + y] = s2[y];
		str[x + y] = '\0';
	}
	return (str);
}
