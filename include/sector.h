#ifndef SECTOR_H
# define SECTOR_H

#include <stdlib.h>
#include "vector.h"

typedef struct		s_pillar
{
	t_fvct2			p;
	char			frust;
	double			angle;
}					t_pillar;

//definir une structure pillar avec un attribu frust plutot que dans le wall

//typedef struct		s_pillar
//{
//
//}					t_pillar;


/*
**	rajouter un pointeur sur le prochain pillier ? pour le mur
*/
typedef struct		s_wall
{
	t_pillar		pillar;
	t_pillar		*next;
	//texture
	//enum wall, portal
	//t_sector *portal sector
	//heigth?
}					t_wall;

typedef struct		s_sector
{
	t_fvct3			gravity;
	t_wall			*wall;
	struct s_sector	*ssector;
	int				len_sub;
	double			h_floor;
	double			h_ceil;
	int				len;
	//sector effector *fonction
	//list things (shapes, objets, deco, enemis)
}					t_sector;

/*
**	wall : draw, manipulation
*/
double			wall_clipping(t_wall wall, t_fvct2 pos, double angle);
void			describe_sector_recursif(t_sector sector);
void			describe_bunch(t_wall **bunch);
void			describe_sector(t_sector sector);
void			describe_wall(t_wall wall);

#endif
