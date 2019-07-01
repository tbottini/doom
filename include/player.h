/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:16:50 by akrache           #+#    #+#             */
/*   Updated: 2019/07/01 17:18:27 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <stdbool.h>
# include "vector.h"

# define CROUCH 16350.0
# define WALK 32700.0
# define SPRINT 49050.0
# define G_EPSILON 0.01
# define NB_WEAPON 4

typedef	struct			s_weapon
{
	t_txtr				*sprites;
	int					clip_max;
	int					ammo;
	int					clip;
	int					rate;
	int					dmg;
	int					id;
	bool				on;
}						t_weapon;

typedef struct 			s_stat
{
	t_fvct3 			pos;
	t_fvct2				rot;
	double				height;
	int					weight;
	double				speed;
	int					health;
	t_fvct3				vel;
	t_fvct3				rotvel;
	t_sector			*sector;
}						t_stat;

typedef struct 			s_player
{
	t_stat				stat;
	bool				crouch;
	int					fov;
	t_weapon			hand;
	t_weapon			weapons[NB_WEAPON];
}						t_player;

/*
** Enemy states:
**
** 0 : idle, not moving (not to be considered in calculations)
** 1 : moving towards player
** 2 : shooting at player
** 3 : dying / dead
*/

typedef struct 			s_enemy
{
	t_txtr				*sprites;
	t_stat				stat;
	double				dist;
	int					dmg;
	int					state;
	struct s_enemy		*next;
}						t_enemy;

/*
**	Gestion
*/

int						player_init(t_player *player);
void					player_free(t_player *player);
t_enemy					*enemy_init(int type);

/*
**	Gameplay
*/

void					fly(t_stat *stat);
void					unfly(t_stat *stat);
void					sprint_release(t_stat *stat);
void					sprint(t_stat *stat);
void					gravity(t_stat *stat);
void					inertie(t_stat *stat);
void					jump(t_player *player);
void					crouch_release(t_player *player);
void					crouch(t_player *player);
void					next_weapon(t_player *player);
void					prev_weapon(t_player *player);
void					change_weapon(t_player *player, int new_w);

/*
** Weapon system
*/

t_weapon				hand_init(void);
t_weapon				gun_init(void);
t_weapon				shotgun_init(void);
t_weapon				rifle_init(void);
void					shoot(t_player *player);
void					reload(t_weapon *weapon);
t_wall					*possible_walls(t_wall **walls, t_stat *stat, t_fvct3 d);
void					apply_wall(t_wall *wall, t_stat *stat, t_fvct3 mo);
t_enemy					*possible_enemys(t_stat *stat, t_fvct3 d);

/*
**	Debug
*/

void					describe_player(t_player player);

#endif
