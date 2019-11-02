/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 17:48:15 by magrab            #+#    #+#             */
/*   Updated: 2019/01/15 16:22:15 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew_set(char c, size_t size)
{
	char	*tmp;

	if (!(tmp = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	tmp[size] = '\0';
	while (size-- > 0)
		tmp[size] = c;
	return (tmp);
}
