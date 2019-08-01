/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:51:14 by akrache           #+#    #+#             */
/*   Updated: 2019/07/30 15:04:10 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		shoot(Uint32 timestamp, t_sound *sound, t_player *player)
{
	printf("shoooooooot || weapon id = %d | FIST = %d\n", player->hand->id, FIST);
	if (player->hand->id == FIST)
		kick(timestamp, sound, player);
	else if (player->hand->clip == 0)
		reload(timestamp, player, player->hand);
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

t_fvct3		real_coord(t_fvct3 pos, double dist, t_fvct3 mo, double height)
{
	t_fvct3 res;

	res.x = pos.x + dist * (mo.x / RADIUS);
	res.y = pos.y + dist * (mo.y / RADIUS);
	res.z = pos.z + height + dist * (mo.z / RADIUS);
	return (res);
}

void		impact_wall(t_wall *wall, t_fvct3 p)
{
	wall->props[wall->nb_props].pos.x = p.x;
	wall->props[wall->nb_props].pos.y = p.y;
	wall->props[wall->nb_props].pos.z = p.z;
	printf("WALL HIT: x = %f | y = %f | z = %f\n", p.x, p.y, p.z);
}

void		injure_enemy(t_enemy *enemy, int dmg, t_fvct3 hit)
{
	if (hit.z < enemy->stat.sector->h_floor)
		{printf("TRO O LOL\n");return ;}//
	if (hit.z > enemy->stat.sector->h_floor + enemy->stat.height)
		{printf("TRO BA MDR || %f\n", enemy->stat.sector->h_floor + enemy->stat.height);return ;}//
	if (hit.z > enemy->stat.sector->h_floor + enemy->stat.height - 0.25)
		{enemy->stat.health -= dmg * 3;printf("HEADSHOT !\n");}//
	else
		{enemy->stat.health -= dmg;printf("BODYSHOT !\n");}//
	if (enemy->stat.health > 0)
		;//hit texture ?
	else
	{
		enemy->state = 4;//apply dying textures ou pas
		del_enemy(enemy->stat.sector, enemy);
	}
	printf("ENEMY HIT: x = %f | y = %f | z = %f\n", hit.x, hit.y, hit.z);
}

static void	apply(t_shoot *shoot, t_stat *stat, t_fvct3 mo, int dmg)
{
	t_fvct3 waim;
	t_fvct3 eaim;

	waim = real_coord(stat->pos, shoot->wdist, mo, 0);
	eaim = real_coord(stat->pos, shoot->edist, mo, 0);
	//calcul enemy or wall is closer
	//if (is_closer(stat, waim, eaim))
	if (shoot->whit && distance((t_fvct2){stat->pos.x, stat->pos.y}, (t_fvct2){waim.x, waim.y})
		< distance((t_fvct2){stat->pos.x, stat->pos.y}, (t_fvct2){eaim.x, eaim.y}))
		impact_wall(shoot->whit, waim);// change bullet hole prop 's position
	else if (shoot->ehit)
		injure_enemy(shoot->ehit, dmg, eaim);//damages on touched enemy
	//printf("distance || %f ||\n\n", shoot->wdist);
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
	shoot.ehit = NULL;
	shoot.whit = NULL;
	possible(&shoot, stat, d, stat->sector);
	wall_real_hit(&shoot, stat);
	apply(&shoot, stat, mo, dmg);
}

