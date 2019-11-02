/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:23:40 by magrab            #+#    #+#             */
/*   Updated: 2018/11/15 15:39:57 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	trim_strlen(const char *s)
{
	size_t		x;
	size_t		c;
	size_t		t;

	c = -1;
	if (s)
	{
		x = 0;
		while (s[x] && (s[x] == ' ' || s[x] == '\n' || s[x] == '\t'))
			x++;
		while (s[x + ++c])
			if (s[x + c] == ' ' || s[x + c] == '\n' || s[x + c] == '\t')
			{
				t = 0;
				while (s[x + c + t] == ' ' || s[x + c + t] == '\n'
						|| s[x + c + t] == '\t' || s[x + c + t] == '\0')
				{
					if (s[x + c + t] == '\0')
						return (c);
					t++;
				}
				c = c + t;
			}
	}
	return (c);
}

char			*ft_strtrim(char const *s)
{
	size_t	x;
	size_t	c;
	size_t	len;
	char	*str;

	str = NULL;
	len = trim_strlen(s);
	if (s)
	{
		if (!(str = (char *)malloc((len + 1) * sizeof(char))))
			return (NULL);
		str[len] = '\0';
		x = 0;
		while (x < len && (s[x] == ' ' || s[x] == '\n' || s[x] == '\t'))
			x++;
		c = 0;
		while (c < len)
		{
			str[c] = s[x + c];
			c++;
		}
	}
	return (str);
}
