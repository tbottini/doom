/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:23:37 by magrab            #+#    #+#             */
/*   Updated: 2018/11/15 15:39:01 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		strstr_strcmp(const char *s1, const char *s2)
{
	if (*s2 == 0)
		return (1);
	if (*s1 != *s2 || *s1 == 0)
		return (0);
	return (strstr_strcmp(s1 + 1, s2 + 1));
}

char			*ft_strstr(const char *big, const char *little)
{
	if (*big == *little && *big == 0)
		return ((char *)big);
	if (*big == 0)
		return (NULL);
	if (strstr_strcmp(big, little))
		return ((char *)big);
	return (ft_strstr(big + 1, little));
}
