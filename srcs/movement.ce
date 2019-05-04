/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 20:45:19 by magrab            #+#    #+#             */
/*   Updated: 2019/04/28 15:16:10 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void move(t_doom *doom, int x, int y)
{
	t_fvct2 d;
	t_fvct2 npos;

	// Update Rotation
	doom->rot += doom->nrot;
	if (doom->rot < 0.0)
		doom->rot += 360.0;
	else if (doom->rot > 360)
		doom->rot -= 360.0;
	// Update Position
	d.x = sin(doom->rot * PI180) / 10.0;
	d.y = cos(doom->rot * PI180) / 10.0;
	npos.x = doom->pos.x + d.x * -y / 35000.0 + d.y * 1 * -x / 35000.0;
	npos.y = doom->pos.y + d.x * -x / 35000.0 + d.y * y / 35000.0;
	// Check new pos
	if (0 < npos.x && npos.x < doom->map_size.x && 0 < npos.y && npos.y < doom->map_size.y)
		if (doom->map[(int)npos.y][(int)npos.x] != '#')
			doom->pos = npos;
}
