/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 20:45:19 by magrab            #+#    #+#             */
/*   Updated: 2019/05/08 19:22:14 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
void move(t_doom *doom, int x, int y)
{
	t_fvct2 d;
	t_fvct2 npos;

	// Update Rotation
	doom->player.rot.y += 5.0;
	if (doom->player.rot.y < 0.0)
		doom->player.rot.y += 360.0;
	else if (doom->player.rot.y > 360)
		doom->player.rot.y -= 360.0;
	// Update Position
	d.x = sin(doom->player.rot.y * PI180) / 10.0;
	d.y = cos(doom->player.rot.y * PI180) / 10.0;
	npos.x = doom->player.pos.x + d.x * -y / 35000.0 + d.y * 1 * -x / 35000.0;
	npos.y = doom->player.pos.y + d.x * -x / 35000.0 + d.y * y / 35000.0;
	// Check new pos
	doom->player.pos = npos;
}
*/