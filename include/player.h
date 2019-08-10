/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:16:50 by akrache           #+#    #+#             */
/*   Updated: 2019/08/10 13:55:16 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <stdbool.h>
# include "vector.h"

# define H_NORMAL 1.80
# define H_CROUCH 0.90
# define H_SMOL 0.36
# define CROUCH 16350.0
# define WALK 32700.0
# define SPRINT 49050.0
# define G_EPSILON 0.01
# define NB_WEAPON 4

# define HANDHOLLOWPATH "ressources/props/fist_hollow.png"
# define GUNHOLLOWPATH "ressources/props/handgun_hollow.png"
# define SHOTGUNHOLLOWPATH "ressources/props/shotgun_hollow.png"
# define RIFLEHOLLOWPATH "ressources/props/rifle_hollow.png"

typedef	struct 			s_sound t_sound;

typedef enum			e_power
{
	NONE,
	FREEZE,
	PUNCH,
	SMOL
}						t_power;

typedef enum			e_id_weapon
{
	FIST,
	GUN,
	SHOTGUN,
	RIFLE
}						t_id_weapon;

/* Jetpack
** -1 : pas ramasse
** 0 : actif
** 1 : inactif
*/
typedef struct			s_inv
{
	int		jetpack;
	bool	key1;
	bool	key2;
	bool	key3;
	bool	last_key;
}						t_inv;

typedef	struct			s_weapon
{
	t_txtr				*sprites[22];
	int					nb_ts;
	int					nb_tr;
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
	t_fvct3				vel;
	t_fvct3				rotvel;
	t_sector			*sector;
	double				height;
	double				speed;
	int					width;
	int					health;
	bool				crouch;
}						t_stat;

typedef struct 			s_player
{
	t_stat				stat;
	t_inv				inv;
	t_weapon			*hand;
	t_weapon			weapons[NB_WEAPON];
	Uint32				boost;
	Uint32				occupied;
	t_power				power;
	int					fov;
}						t_player;

/*
** Enemy states:
** -1 : never seen before
** 0 : idle, not moving
** 1 : moving towards player
** 2 : shooting at player
** 3 : dying / dead
*/

typedef struct 			s_enemy
{
	t_txtr				*sprites;
	t_stat				stat;
	t_fvct3				e1;
	t_fvct3				e2;
	Uint32				rts;//reload timestamp
	int					dmg;
	int					type;
	int					state;
	struct s_enemy		*next;
	struct s_enemy		*prev;
}						t_enemy;

typedef struct			s_shoot
{
	t_wall				*walls[50];
	t_enemy				*enemys[50];
	t_wall				*whit;
	t_enemy				*ehit;
	double				wdist;
	double				edist;
	int					i_w;
	int					i_e;
	int					dmg;
}						t_shoot;

/*
**	Gestion
*/

void					armandtificial_intelligence(t_doom *doom);
void					check_boost(Uint32 timestamp, t_player *player);
int						player_init(t_player *player);
void					player_free(t_player *player);
t_enemy					*pushfront_enemy(t_sector *sector, t_enemy *enemy);
t_enemy					*enemy_init(int type, int difficulty, t_sector *sector);
void					free_enemys(t_enemy *enemy);
void					del_enemy(t_sector *sector, t_enemy *enemy);

/*
**	Gameplay
*/

void					jetpack_on_off(t_player *player);
void					fly_down(t_stat *stat);
void					sprint_release(t_stat *stat);
void					sprint(t_stat *stat);
//void					gravity(t_stat *stat);
//void					inertie(t_stat *stat);
void					jump(t_stat *stat, t_inv *inv);
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
void					reload(Uint32 timestamp, t_player *player, t_weapon *weapon);
void					shoot(Uint32 timestamp, t_sound *sound, t_player *player);
void					bullet(t_stat *stat, int dmg);
void					injure_enemy(t_enemy *enemy, int dmg, t_fvct3 hit);
void					wall_real_hit(t_shoot *shoot, t_stat *stat);
void					possible(t_shoot *shoot, t_stat *stat, t_fvct3 ori, t_sector *sector);
t_fvct3					real_coord(t_fvct3 pos, double dist, t_fvct3 mo, double height, double angle);
//t_wall				*possible_walls(t_wall **walls, t_stat *stat, t_fvct3 d, int *index);
//void					apply_wall(t_wall *wall, t_stat *stat, t_fvct3 mo);
//t_enemy				*possible_enemys(t_enemy **enemys, t_stat *stat, t_fvct3 d, int *index);

/*
**	Debug
*/

void					describe_player(t_player player);

#endif
