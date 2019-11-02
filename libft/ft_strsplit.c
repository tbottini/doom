/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:23:35 by magrab            #+#    #+#             */
/*   Updated: 2018/11/15 15:24:38 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	split_strlen(const char *s, char c)
{
	if (*s != '\0' && *s != c)
		return (1 + split_strlen(s + 1, c));
	return (1);
}

static size_t	countword(char const *s, char c)
{
	size_t	x;
	size_t	w;

	x = 0;
	w = 0;
	while (s[x] == c)
		x++;
	while (s[x])
	{
		if (s[x] == c)
			while (s[x] == c)
				x++;
		else if (s[x] != c)
		{
			w++;
			while (s[x] != c && s[x])
				x++;
		}
	}
	return (w);
}

static char		*find_word(char const *s, char c)
{
	char	*word;
	int		x;

	x = split_strlen(s, c);
	if (x == 1 || !(word = (char *)malloc(x * sizeof(char))))
		return (NULL);
	word[--x] = 0;
	while (--x >= 0)
		word[x] = s[x];
	return (word);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	w;
	size_t	x;

	tab = NULL;
	if (s)
	{
		w = countword(s, c);
		if (!(tab = (char **)malloc((w + 1) * sizeof(char *))))
			return (NULL);
		tab[w] = NULL;
		x = 0;
		w = 0;
		while (s[x])
		{
			while (s[x] == c)
				x++;
			tab[w++] = find_word(s + x, c);
			while (s[x] != c && s[x])
				x++;
		}
	}
	return (tab);
}
