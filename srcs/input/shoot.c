/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:51:14 by akrache           #+#    #+#             */
/*   Updated: 2019/06/27 16:55:33 by akrache          ###   ########.fr       */
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
	if (player->weapons[player->hand].clip == 0)
		reload(&(player->weapons[player->hand]));
	else
	{
		//bullet(&player->stat);
		player->weapons[player->hand].clip--;
	}
}

t_enemy		*possible_enemys(t_stat *stat, t_fvct3 d)
{
	(void)stat;
	(void)d;
	return (NULL);
}

void		apply_enemy(t_enemy *enemy, t_stat *stat, t_fvct3 mo)
{
	(void)enemy;
	(void)stat;
	(void)mo;
}

void		supa_shoota(t_stat *stat, t_fvct3 d, t_fvct3 mo)
{
	t_wall	*walls[50];
	t_enemy	*enemys[50];
	t_wall *wall;
	t_enemy *enemy;

	wall = possible_walls(walls, stat, d);
	enemy = possible_enemys(stat, d);
	if (wall && (!enemy || wall->dist <= enemy->dist))
		apply_wall(wall, stat, mo);
	else if (enemy)
		apply_enemy(enemy, stat, mo);

}

//d.x = sin(stat->rot.y * PI180)
//d.y = cos(stat->rot.y * PI180)

//npos.x = stat->pos.x + sin(stat->rot.y * PI180) * stat->vel.y + cos(stat->rot.y * PI180) * stat->vel.x
//npos.y = stat->pos.y - sin(stat->rot.y * PI180) * -stat->vel.x - cos(stat->rot.y * PI180) * stat->vel.y
void		bullet(t_stat *stat)
{
	t_fvct3	d;
	t_fvct3	mo;

	mo.x = (RADIUS * sin(stat->rot.x * PI180) * cos(stat->rot.y * PI180));
	mo.y = (RADIUS * sin(stat->rot.x * PI180) * sin(stat->rot.y * PI180));
	mo.z = (-(RADIUS * cos(stat->rot.x * PI180)) + (stat->height / 2));
	d.x = mo.x + stat->pos.x;
	d.y = mo.y + stat->pos.y;
	d.z = mo.z + stat->pos.z;
	printf("\rRot : %f\t%f\n", stat->rot.x, stat->rot.y);
	printf("d : x = %f | y = %f | z = %f\n", d.x, d.y, d.z);
	printf("mo : x = %f | y = %f | z = %f\n", mo.x, mo.y, mo.z);
	supa_shoota(stat, d, mo);
}
