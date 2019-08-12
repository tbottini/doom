/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 11:46:33 by akrache           #+#    #+#             */
/*   Updated: 2019/08/12 13:11:43 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		update_enemy_rotation(t_enemy *enemy, t_fvct3 pos)
{
	enemy->stat.rot.y = atan2(pos.x - enemy->stat.pos.x, pos.y - enemy->stat.pos.y);
	enemy->e1.x = enemy->stat.pos.x + sin(enemy->stat.rot.y - (90.0 * PI180)) * enemy->stat.height / 4;
	enemy->e1.y = enemy->stat.pos.y + cos(enemy->stat.rot.y - (90.0 * PI180)) * enemy->stat.height / 4;
	enemy->e2.x = enemy->stat.pos.x + sin(enemy->stat.rot.y + (90.0 * PI180)) * enemy->stat.height / 4;
	enemy->e2.y = enemy->stat.pos.y + cos(enemy->stat.rot.y + (90.0 * PI180)) * enemy->stat.height / 4;	
}

/*
** returns true if point pos is between point target and both points m1 and m2, false otherwise
**/
bool		is_between(t_fvct3 pos, t_fvct3 target, t_fvct3 m1, t_fvct3 m2)
{
	double dist;

	dist = distance((t_fvct2){target.x, target.y}, (t_fvct2){pos.x, pos.y});
	if (dist < distance((t_fvct2){target.x, target.y}, (t_fvct2){m1.x, m1.y})
		&& dist < distance((t_fvct2){target.x, target.y}, (t_fvct2){m2.x, m2.y}))
		return (false);
	return (true);
}

/*
** returns 1 if target is visible from stat's point of view
*/
int			is_visible(t_stat *stat, t_stat *target, t_sector *sector, int passed)
{
	int res;
	int i;

	i = 0;
	res = 0;
	if (passed > 10)
		return (1);
	while (i < sector->len)
	{
		if (vector_intersect(stat->pos, target->pos, *(t_fvct3*)&sector->wall[i].pillar->p, *(t_fvct3*)&sector->wall[i].next->p))
		{
			if (sector->wall[i].status >= OPEN_DOOR && sector->wall[i].link != sector
				&& is_between(stat->pos, target->pos, *(t_fvct3*)&sector->wall[i].pillar->p, *(t_fvct3*)&sector->wall[i].next->p))
				return (is_visible(stat, target, sector->wall[i].link, passed + 1));
			else
				return (0);
		}
		i++;
	}
	return (1);
}

void		move_toward(t_enemy *enemy, t_player *player, Uint32 timestamp)
{
	t_fvct3		npos;
	t_wall		*hit;
	t_sector	*old;
	int			tmp;

	npos.x = enemy->stat.pos.x + (sin(enemy->stat.rot.y) / 10.0) * (enemy->stat.speed / 30000.0);
	npos.y = enemy->stat.pos.y + (cos(enemy->stat.rot.y) / 10.0) * (enemy->stat.speed / 30000.0);
	tmp = -7000;
	old = enemy->stat.sector;
	if (enemy->stat.sector == player->stat.sector || (tmp = colli_port(&enemy->stat, enemy->stat.sector, npos, &hit)) != -1)
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

void		ai_action(Uint32 timestamp, t_enemy *enemy, t_player *player)
{
	double dist;

	update_enemy_rotation(enemy, player->stat.pos);
	dist = distance((t_fvct2){enemy->stat.pos.x, enemy->stat.pos.y}, (t_fvct2){player->stat.pos.x, player->stat.pos.y});
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

bool	is_passed(t_sector *sector, t_sector **passed, int index)
{
	int i;

	i = 0;
	while (i < index)
	{
		if (sector == passed[i])
			return (true);
		i++;
	}
	return (false);
}

void	update_enemy_sprite(t_ui *ui, t_enemy *enemy, Uint32 timestamp)
{
	int anim;

	if (enemy->state == 0)
		set_txtr(&enemy->sprites, ui->enemy[(enemy->type - 1) * 6], 0);
	else if (enemy->state == 1)
	{
		anim = (timestamp % 1000) / 250;
		if (anim < DEATHLEN)
			set_txtr(&enemy->sprites, ui->enemy[(enemy->type - 1) * 6 + anim + 2], 0);
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

int		is_around(t_doom *doom, t_sector *sector, t_sector **passed, int *index)
{
	t_enemy		*tmp;
	t_enemy		*tmp2;
	double		nposz;
	int			i;

	tmp = sector->enemys;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->state == -1 && is_visible(&tmp->stat, &doom->game.player.stat, tmp->stat.sector, 0))
			tmp->state = 0;
		else if (tmp->state != -1)
		{
			if (tmp->state == 3)
			{
				tmp->rts = doom->timestamp;
				tmp->state = 4;
			}
			else if (tmp->state == 4)
			{
				tmp->rts + 1000 < doom->timestamp ? del_enemy(sector, tmp) : update_enemy_sprite(&doom->ui, tmp, doom->timestamp);
			}
			else if (tmp->state != 4)
			{
				tmp->state == 2 ? tmp->state = 0 : 0;
				if (tmp->stat.pos.z > tmp->stat.sector->h_floor && tmp->stat.sector->gravity.z < 0)
				tmp->stat.vel.z += tmp->stat.sector->gravity.z * 450.0;
				if ((nposz = tmp->stat.pos.z + tmp->stat.vel.z / 35000.0) <= tmp->stat.sector->h_floor)
				{
					tmp->stat.pos.z = tmp->stat.sector->h_floor;
					tmp->stat.vel.z = 0;
				}
				else
					tmp->stat.pos.z = nposz;
				if (tmp->rts <= doom->timestamp && doom->game.player.power != FREEZE
					&& is_visible(&tmp->stat, &doom->game.player.stat, tmp->stat.sector, 0))
				{
					ai_action(doom->timestamp, tmp, &doom->game.player);
				}
				update_enemy_sprite(&doom->ui, tmp, doom->timestamp);
			}
		}
		tmp = tmp2;
	}
	if (*index == doom->game.len.nb_sects - 1)
		return (0);
	passed[*index] = sector;
	(*index)++;
	i = 0;
	while (i < sector->len)
	{
		if (sector->wall[i].status >= OPEN_DOOR && sector->wall[i].link && !is_passed(sector->wall[i].link, passed, *index))
			is_around(doom, sector->wall[i].link, passed, index);
		i++;
	}
	return (0);
}

void	armandtificial_intelligence(t_doom *doom)
{
	int			index;
	t_sector	*passed[doom->game.len.nb_sects];

	index = 0;
	is_around(doom, doom->game.player.stat.sector, passed, &index);
}
