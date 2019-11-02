/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:35:20 by magrab            #+#    #+#             */
/*   Updated: 2019/01/15 14:59:07 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char **s1, char **s2, int d)
{
	char	*res;

	res = ft_strjoin(*((char **)s1), *((char **)s2));
	if (d == 1 || d == 3)
		ft_strdel(s1);
	if (d == 2 || d == 3)
		ft_strdel(s2);
	return (res);
}
