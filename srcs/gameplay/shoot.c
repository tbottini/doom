/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:51:14 by akrache           #+#    #+#             */
/*   Updated: 2019/07/28 18:48:33 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		reload(Uint32 timestamp, t_player *player, t_weapon *weapon)
{
	int	r;

	if (player->occupied < timestamp)
	{
		r = weapon->clip_max - weapon->clip;
		if (weapon->ammo - r < 0)
			r = weapon->ammo;
		weapon->ammo -= r;
		weapon->clip += r;
		player->occupied = timestamp + 1000;//ajuster avec vitesse d'animation
	}
}

void		shoot(Uint32 timestamp, t_sound *sound, t_player *player)
{
	if (player->hand->clip == 0)
		reload(timestamp, player, player->hand);
	else if (player->hand->id == FIST)
		kick(timestamp, sound, player);
	else
	{
		bullet(&player->stat, player->hand->dmg);
		player->hand->clip--;
		if (player->hand->rate)
			player->occupied = timestamp + 150;//ajuster avec vitesse d'animation et vitesse de tir voulue
		else
			player->occupied = timestamp + 500;//ajuster avec vitesse d'animation et temps entre deux tirs souhaite
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

/* 
** Returns 1 if point px is closer from point posx than point qx
** else, founction returns 0

static int is_closer(t_fvct3 posx, t_fvct3 px, t_fvct3 qx)
{
	//t_fvct3 tmp;
	//t_fvct3 tmq;

	//tmp.x = fabs(pos.x - p.x);
	//tmp.y = fabs(pos.y - p.y);
	//tmp.z = fabs(pos.z - p.z);
	//tmq.x = fabs(pos.x - q.x);
	//tmq.y = fabs(pos.y - q.y);
	//tmq.z = fabs(pos.z - q.z);
	return ((fabs(posx - px) < fabs(posx - qx)));
}*/

void		impact_wall(t_wall *wall, t_fvct3 p)
{
	wall->props[wall->nb_props].pos.x = p.x;
	wall->props[wall->nb_props].pos.y = p.y;
	wall->props[wall->nb_props].pos.z = p.z;
}

void		injure_enemy(t_enemy *enemy, int dmg)
{
	enemy->stat.health -= dmg;
	if (enemy->stat.health > 0)
		;//hit texture ?
	else
	{
		enemy->state = -1;//apply dying textures
		del_enemy(enemy->stat.sector, enemy);
	}
}

static void	apply(t_shoot *shoot, t_fvct3 pos, t_fvct3 mo, int dmg)
{
	t_fvct3 waim;
	t_fvct3 eaim;

	waim = real_coord(pos, shoot->wdist, mo);
	eaim = real_coord(pos, shoot->edist, mo);
	//calcul enemy or wall is closer
	//if (is_closer(stat, waim, eaim))
	if (fabs(pos.x - waim.x) < fabs(pos.x - eaim.x))//revoir condition nulle
		impact_wall(shoot->whit, waim);// change bullet hole prop 's position
	else
		injure_enemy(shoot->ehit, dmg);//damages on touched enemy
	printf("SUPER COORD : x = %f | y = %f | z = %f\n", waim.x, waim.y, waim.z);
	printf("distance || %f ||\n\n", shoot->wdist);
}

void		bullet(t_stat *stat, int dmg)
{
	t_fvct3	d;
	t_fvct3	mo;
	t_shoot	shoot;

	mo.x = (RADIUS * sin(stat->rot.x * PI180) * cos(stat->rot.y * PI180));
	mo.y = (RADIUS * sin(stat->rot.x * PI180) * sin(stat->rot.y * PI180));
	mo.z = (-(RADIUS * cos(stat->rot.x * PI180)) + (stat->height / 2));
	d.x = mo.x + stat->pos.x;
	d.y = mo.y + stat->pos.y;
	d.z = mo.z + stat->pos.z;
	shoot.i_e = 0;
	shoot.i_w = 0;
	//printf("\rRot : %f\t%f\n", stat->rot.x, stat->rot.y);
	//printf("d : x = %f | y = %f | z = %f\n", d.x, d.y, d.z);
	//printf("mo : x = %f | y = %f | z = %f\n", mo.x, mo.y, mo.z);
	//supa_shoota(stat, d, mo);
	possible(&shoot, stat, d, stat->sector);
	wall_real_hit(&shoot, stat);
	apply(&shoot, stat->pos, mo, dmg);
}
