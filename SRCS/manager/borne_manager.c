/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   borne_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 08:01:26 by akrache           #+#    #+#             */
/*   Updated: 2019/08/26 20:52:52 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_borne		*borne_init(t_borne *borne, int len)
{
	borne->b_down = (uint32_t*)malloc(sizeof(uint32_t) * len);
	if (!borne->b_down)
		return (NULL);
	borne->b_up = (uint32_t*)malloc(sizeof(uint32_t) * len);
	if (!borne->b_up)
	{
		free(borne->b_down);
		return (NULL);
	}
	borne->zline = (double*)malloc(sizeof(double) * len);
	if (!borne->zline)
	{
		free(borne->b_down);
		free(borne->b_up);
		return (NULL);
	}
	return (borne);
}

void		borne_free(t_borne *borne)
{
	if (borne)
	{
		if (borne->b_down)
			free(borne->b_down);
		if (borne->b_up)
			free(borne->b_up);
		if (borne->zline)
			free(borne->zline);
		borne->b_down = NULL;
		borne->b_up = NULL;
		borne->zline = NULL;
	}
}
