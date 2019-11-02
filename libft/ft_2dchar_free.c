/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dchar_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 17:48:25 by magrab            #+#    #+#             */
/*   Updated: 2019/01/08 20:41:55 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_2dchar_free(char ***map)
{
	int x;

	if (!map || !(map[0]))
		return (0);
	x = 0;
	while (map[0][x])
	{
		free(map[0][x]);
		x++;
	}
	free(map[0]);
	map[0] = NULL;
	return (0);
}
