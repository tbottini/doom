
#ifndef PLAYER_H
# define PLAYER_H

# include "vector.h"

# define WEAPON_MAX 5
# define CROUCH 16350.0
# define WALK 32700.0
# define SPRINT 49050.0
# define G_EPSILON 0.01


typedef	struct			s_weapon
{
	int					clip_max;
	int					ammo;
	int					clip;
	int					rate;
	int					dmg;
	t_txtr				*sprites;
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
	int					crouch;
	int					fov;
	int					hand;
	t_weapon			weapons[WEAPON_MAX];
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
}						t_enemy;

/*
**	Gestion
*/
int						player_init(t_player *player);
void					player_free(t_player *player);

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
