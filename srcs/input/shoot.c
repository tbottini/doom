/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:51:14 by akrache           #+#    #+#             */
/*   Updated: 2019/07/02 20:05:54 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		reload(t_weapon *weapon)
{
	int	r;

	r = weapon->clip_max - weapon->clip;
	(weapon->ammo - r < 0 ? r += weapon->ammo - r : 0);
	weapon->ammo -= r;
	weapon->clip = r;
}

void		shoot(t_player *player)
{
	if (player->hand.clip == 0)
		reload(&player->hand);
	else
	{
		bullet(&player->stat);
		player->hand.clip--;
	}
}

t_fvct3		real_coord(t_fvct3 pos, double dist, t_fvct3 mo)
{
	t_fvct3 res;

	res.x = pos.x + dist * (mo.x / RADIUS);
	res.y = pos.y + dist * (mo.y / RADIUS);
	res.z = pos.z + dist * (mo.z / RADIUS);
	return (res);
}

static void	apply(t_super *super, t_stat *stat, t_fvct3 mo)
{
	t_fvct3 waim;
	t_fvct3 eaim;

	waim = real_coord(stat->pos, super->wdist, mo);
	eaim = real_coord(stat->pos, super->edist, mo);
	//calcul enemy or wall is closer
	printf("SUPER COORD : x = %f | y = %f | z = %f\n", waim.x, waim.y, waim.z);
	printf("distance || %f ||\n\n", super->wdist);
}

void		bullet(t_stat *stat)
{
	t_fvct3	d;
	t_fvct3	mo;
	t_super	super;

	mo.x = (RADIUS * sin(stat->rot.x * PI180) * cos(stat->rot.y * PI180));
	mo.y = (RADIUS * sin(stat->rot.x * PI180) * sin(stat->rot.y * PI180));
	mo.z = (-(RADIUS * cos(stat->rot.x * PI180)) + (stat->height / 2));
	d.x = mo.x + stat->pos.x;
	d.y = mo.y + stat->pos.y;
	d.z = mo.z + stat->pos.z;
	super.i_e = 0;
	super.i_w = 0;
	//printf("\rRot : %f\t%f\n", stat->rot.x, stat->rot.y);
	//printf("d : x = %f | y = %f | z = %f\n", d.x, d.y, d.z);
	//printf("mo : x = %f | y = %f | z = %f\n", mo.x, mo.y, mo.z);
	//supa_shoota(stat, d, mo);
	possible(&super, stat, d, stat->sector);
	super_real_hit(&super, stat);
	apply(&super, stat, mo);
}
