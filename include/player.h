
#ifndef PLAYER_H
# define PLAYER_H

# include "vector.h"

# define WEAPON_MAX 5

typedef	struct			s_weapon
{
	int					clip_max;
	int					ammo;
	int					clip;
	int					rate;
	int					dmg;
	void				*sprites;
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
	int					nb_weapons;
	t_weapon			*weapons;
}						t_player;

/*
**	Gestion
*/
int						player_init(t_player *player);
void					player_free(t_player *player);

/*
**	Gameplay
*/

void					sprint_release(t_player *player);
void					sprint(t_player *player);
void					gravity(t_player *player);
void					inertie(t_player *player);
void					jump(t_player *player);
void					shoot(t_player *player);
void					reload(t_weapon *weapon);
void					crouch_release(t_player *player);
void					crouch(t_player *player);
void					next_weapon(t_player *player);
void					prev_weapon(t_player *player);

/*
**	Debug
*/

void					describe_player(t_player player);

#endif
