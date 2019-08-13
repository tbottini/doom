/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:51:14 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 04:33:02 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		injure_enemy(t_enemy *enemy, int dmg, t_fvct3 hit)
{
	if (hit.z < enemy->stat.sector->h_floor)
		return ;
	if (hit.z > enemy->stat.sector->h_floor + enemy->stat.height)
		return ;
	if (enemy->state != 4)
	{
		if (hit.z > enemy->stat.sector->h_floor + enemy->stat.height - 0.25)
			enemy->stat.health -= dmg * 3;
		else
			enemy->stat.health -= dmg;
		if (enemy->stat.health < 0)
			enemy->state = 3;
	}
}

t_fvct3		real_coord(t_fvct3 pos, double dist, t_fvct3 mo, t_stat *stat)
{
	t_fvct3 res;

	res.x = pos.x + dist * (mo.x / RADIUS);
	res.y = pos.y + dist * (mo.y / RADIUS);
	res.z = pos.z + stat->height + dist * sin((stat->rot.x - 90.0) * PI180);
	return (res);
}

static void	impact_wall(t_wall *wall, t_fvct3 p)
{
	wall->props[wall->nb_props].pos.x = p.x;
	wall->props[wall->nb_props].pos.y = p.y;
	wall->props[wall->nb_props].pos.z = p.z;
	prop_init(&wall->props[wall->nb_props], wall);
}

static void	apply(t_shoot *shoot, t_stat *stat, t_fvct3 mo, int dmg)
{
	t_fvct3 waim;
	t_fvct3 eaim;

	waim = real_coord(stat->pos, shoot->wdist, mo, stat);
	eaim = real_coord(stat->pos, shoot->edist, mo, stat);
	if (shoot->whit && distance((t_fvct2){stat->pos.x,
	stat->pos.y}, (t_fvct2){waim.x, waim.y})
	< distance((t_fvct2){stat->pos.x, stat->pos.y}, (t_fvct2){eaim.x, eaim.y}))
		impact_wall(shoot->whit, waim);
	else if (shoot->ehit)
		injure_enemy(shoot->ehit, dmg, eaim);
}

void		bullet(t_stat *stat, int dmg, int nbsect)
{
	t_fvct3		d;
	t_fvct3		mo;
	t_shoot		shoot;
	t_sector	passed[nbsect];

	mo.x = (RADIUS * sin(stat->rot.x * PI180) * cos(stat->rot.y * PI180));
	mo.y = (RADIUS * sin(stat->rot.x * PI180) * sin(stat->rot.y * PI180));
	mo.z = (-(RADIUS * cos(stat->rot.x * PI180)) + (stat->height / 2));
	d.x = mo.x + stat->pos.x;
	d.y = mo.y + stat->pos.y;
	d.z = mo.z + stat->pos.z;
	shoot.i_e = 0;
	shoot.i_w = 0;
	shoot.ehit = NULL;
	shoot.whit = NULL;
	shoot.passed = (t_sector **)&passed;
	shoot.index = 0;
	possible(&shoot, stat, d, stat->sector);
	shoot.walls[shoot.i_w] = NULL;
	shoot.enemys[shoot.i_e] = NULL;
	wall_real_hit(&shoot, stat, mo);
	apply(&shoot, stat, mo, dmg);
}
