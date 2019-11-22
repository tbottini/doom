/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 03:29:40 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 03:34:55 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	move_toward(t_enemy *enemy, t_player *player, Uint32 timestamp)
{
	t_fvct3		npos;
	t_wall		*hit;
	t_sector	*old;
	int			tmp;

	npos.x = enemy->stat.pos.x + (sin(enemy->stat.rot.y) / 10.0)
	* (enemy->stat.speed / 30000.0);
	npos.y = enemy->stat.pos.y + (cos(enemy->stat.rot.y) / 10.0)
	* (enemy->stat.speed / 30000.0);
	tmp = -7000;
	old = enemy->stat.sector;
	if (enemy->stat.sector == player->stat.sector
	|| (tmp = colli_port(&enemy->stat, enemy->stat.sector, npos, &hit)) != -1)
	{
		if (tmp == 1)
		{
			if (old->enemys == enemy)
				old->enemys = enemy->next;
			pushfront_enemy(enemy->stat.sector, enemy);
		}
		enemy->state = 1;
		enemy->stat.pos.x = npos.x;
		enemy->stat.pos.y = npos.y;
		enemy->rts = timestamp + 1;
	}
}

static void	update_enemy_sprite(t_ui *ui, t_enemy *enemy, Uint32 timestamp)
{
	int anim;

	if (enemy->state == 0)
		set_txtr(&enemy->sprites, ui->enemy[(enemy->type - 1) * 6], 0);
	else if (enemy->state == 1)
	{
		anim = (timestamp % 1000) / 250;
		if (anim < DEATHLEN)
			set_txtr(&enemy->sprites,
			ui->enemy[(enemy->type - 1) * 6 + anim + 2], 0);
	}
	else if (enemy->state == 2)
		set_txtr(&enemy->sprites, ui->enemy[(enemy->type - 1) * 6 + 1], 0);
	else if (enemy->state == 4)
	{
		anim = (double)(timestamp - (enemy->rts + 1000.0)) / 1000.0 * 9 + 9;
		if (!(anim < DEATHLEN))
			return ;
		if (enemy->type != 4)
			set_txtr(&enemy->sprites, ui->enemy[ENEMYDEATHSTART + anim], 0);
		else
			set_txtr(&enemy->sprites, ui->enemy[BOSSDEATHSTART + anim], 0);
	}
}

static void	ai_action(Uint32 timestamp, t_enemy *enemy, t_player *player)
{
	double dist;

	update_enemy_rotation(enemy, &enemy->stat, player->stat.pos);
	dist = distance((t_fvct2){enemy->stat.pos.x, enemy->stat.pos.y},
	(t_fvct2){player->stat.pos.x, player->stat.pos.y});
	if (dist <= 7.0)
	{
		enemy->state = 0;
		if (enemy->rts < timestamp)
		{
			player->stat.health -= enemy->dmg;
			enemy->state = 2;
			enemy->rts = timestamp + 1000;
		}
		return ;
	}
	move_toward(enemy, player, timestamp);
}

static void	ai_playing(t_doom *d, t_enemy *t)
{
	double		nposz;

	t->state == 2 ? t->state = 0 : 0;
	if (t->stat.pos.z > t->stat.sector->h_floor
	&& t->stat.sector->gravity.z < 0)
		t->stat.vel.z += t->stat.sector->gravity.z * 450.0;
	if ((nposz = t->stat.pos.z + t->stat.vel.z / 35000.0)
	<= t->stat.sector->h_floor)
	{
		t->stat.pos.z = t->stat.sector->h_floor;
		t->stat.vel.z = 0;
	}
	else
		t->stat.pos.z = nposz;
	if (t->rts <= d->timestamp && d->game.player.power != FREEZE
		&& is_visible(&t->stat, &d->game.player.stat,
		t->stat.sector, 0))
		ai_action(d->timestamp, t, &d->game.player);
	update_enemy_sprite(&d->ui, t, d->timestamp);
}

void		ai_active(t_doom *d, t_enemy *t, t_sector *s)
{
	if (t->state == 3)
	{
		t->rts = d->timestamp;
		t->state = 4;
	}
	else if (t->state == 4)
		t->rts + 1000 < d->timestamp ? del_enemy(s, t)
		: update_enemy_sprite(&d->ui, t, d->timestamp);
	else if (t->state != 4)
		ai_playing(d, t);
}
