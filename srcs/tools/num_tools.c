/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:36:06 by tbottini          #+#    #+#             */
/*   Updated: 2019/05/09 16:51:06 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

double		double_modulo(double num)
{
	num = (int)num % 360 + num - (int)num;
	return (num);
}

double		angle_adaptater(double angle)
{
	if (angle < 0.0)
		angle += 360.0;
	else if (angle > 360.0)
		angle = double_modulo(angle);
	return (angle);
}

float		ft_atof(char *str)
{
	float	nb;
	int		i;
	int		sign;
	float	j;

	j = 10.0;
	sign = (str[0] == '-') ? -1 : 1;
	nb = 0.0;
	i = 0;
	while (str[i] && str[i] != '.')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	i++;
	while (str[i])
	{
		nb = nb + (str[i] - '0') / j;
		j *= 10.0;
		i++;
	}
	return (nb);
}

float		ft_catof(char *str, char c)
{
	float	nb;
	int		i;
	int		sign;
	float	j;

	j = 10.0;
	sign = (str[0] == '-') ? -1 : 1;
	nb = 0.0;
	i = 0;
	while (str[i] && str[i] != '.' && str[i] != c)
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	if (str[i] != ' ')
		i++;
	while (str[i] && str[i] != c)
	{
		nb = nb + (str[i] - '0') / j;
		j *= 10.0;
		i++;
	}
	return (nb);
}

float		distance(t_fvct2 vct1, t_fvct2 vct2)
{
	t_fvct2	dist;

	dist.x = vct2.x - vct1.x;
	dist.y = vct2.y - vct1.y;
	return (sqrt((dist.x * dist.x) + (dist.y * dist.y)));
}
