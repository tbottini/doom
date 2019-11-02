/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:23:37 by magrab            #+#    #+#             */
/*   Updated: 2018/11/15 15:39:01 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		strnstr_strcmp(const char *s1, const char *s2, size_t len)
{
	if (*s2 == 0)
		return (1);
	if (*s1 != *s2 || *s1 == 0 || len == 0)
		return (0);
	return (strnstr_strcmp(s1 + 1, s2 + 1, len - 1));
}

char			*ft_strnstr(const char *big, const char *little, size_t len)
{
	if (*big == *little && *big == 0)
		return ((char *)big);
	if (*big == 0 || len == 0)
		return (NULL);
	if (strnstr_strcmp(big, little, len))
		return ((char *)big);
	return (ft_strnstr(big + 1, little, len - 1));
}
