/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 19:17:11 by magrab            #+#    #+#             */
/*   Updated: 2019/07/29 19:17:12 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void scroll_limits(int *value, int addition, int smin, int smax)
{
	if (!value)
		return ;
	if (*value + addition < smin)
		*value = smin;
	else if (*value + addition > smax)
		*value = smax;
	else
		*value += addition;
}
