/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:16:50 by akrache           #+#    #+#             */
/*   Updated: 2019/08/26 17:26:11 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SECTOR_H
# define SECTOR_H

# include "vector.h"
# include "libft.h"
# include <SDL.h>
# include <stdlib.h>

# define G_EARTH -9.80665
# define G_MOON -1.62200

# define DOOR_OPEN_TIME 300

typedef struct s_enemy	t_enemy;
typedef struct s_sector	t_sector;
typedef struct s_wall	t_portal;
typedef struct s_prop	t_prop;

typedef enum			e_portal_id
{
	WALL,
	CLOSE_DOOR,
	WINDOW,
	OPEN_DOOR,
	PORTAL
}						t_portal_id;

typedef struct			s_txtr
{
	uint32_t			*pixels;
	uint32_t			w;
	uint32_t			h;
	int					id;
}						t_txtr;

typedef struct			s_pillar
{
	t_fvct2				p;
	char				frust;
	double				angle;
}						t_pillar;

/*
**	rajouter un pointeur sur le prochain pillier ? pour le mur
**	si le mur est un portail defini dans status
**	link donne le lien du portail si il est distant
*/

typedef struct			s_wall
{
	t_pillar			*pillar;
	t_pillar			*next;
	t_txtr				txtr;
	t_portal_id			status;
	t_sector			*link;
	t_prop				*props;
	double				percent;
	Uint32				ots;
	int					nb_props;
	int					level;
}						t_wall;

typedef struct			s_hitbox
{
	double				x;
	double				y;
	double				z;
	double				w;
	double				l;
	double				h;
}						t_hitbox;

struct					s_prop
{
	t_txtr				tex;
	void				(*func)();
	t_fvct3				pos;
	t_hitbox			hitbox;
	t_wall				*wall;
	t_sector			*sector;
	int					type;
	t_fvct2				percent;
	t_vct2				px;
};

typedef struct			s_box_txtr
{
	t_fvct2				start;
	t_fvct2				length;
}						t_box_txtr;

struct					s_sector
{
	t_fvct3				gravity;
	t_wall				*wall;
	t_prop				*props;
	t_enemy				*enemys;
	int					len_prop;
	double				h_floor;
	double				h_ceil;
	int					len;
	t_txtr				txtrtop;
	t_txtr				txtrsol;
	t_box_txtr			box;
};

t_sector				*sector_new();

/*
**	wall : draw, manipulation
*/

void					describe_sector_recursif(t_sector sector);
void					describe_bunch(t_wall **bunch);
void					describe_sector(t_sector sector);
void					describe_wall(t_wall wall);
t_vct2					sector_get_floor_texel(t_sector *sector, t_fvct2 pos);
void					init_prop(t_prop *prop, double height);
int						in_hitbox(t_hitbox *hitbox, t_fvct3 pos
	, double hheight);

void					sector_init_prop(t_sector *sector);
void					sector_iter(t_sector *sector, int len
	, void (sector_effector)(t_sector*));
void					sector_wall_props_init(t_sector *sector);

/*
**	prop
*/

void					prop_init(t_prop *prop, t_wall *wall);
void					prop_iter(t_prop *prop, int len
	, void(*prop_iter)(t_prop*));

#endif
