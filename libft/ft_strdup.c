/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:23:11 by magrab            #+#    #+#             */
/*   Updated: 2018/11/15 15:24:38 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	x;
	char	*new;

	x = 0;
	while (s[x])
		x++;
	if (!(new = (char *)malloc((x + 1) * sizeof(char))))
		return (NULL);
	x = 0;
	while (s[x])
	{
		new[x] = s[x];
		x++;
	}
	new[x] = '\0';
	return (new);
}
