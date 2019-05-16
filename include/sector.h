#ifndef SECTOR_H
# define SECTOR_H

#include <stdlib.h>
#include "vector.h"

typedef struct		s_pillar
{
	t_fvct2			p;
	char			frust;
	float			angle;
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
	t_wall			*wall;
	struct s_sector	*ssector;
	int				len_sub;
	float			h_floor;
	float			h_ceil;
	int				len;
	//sector effector *fonction
	//list things (shapes, objets, deco, enemis)
}					t_sector;

/*
**	wall : draw, manipulation
*/
float			wall_clipping(t_wall wall, t_fvct2 pos, float angle);
void			describe_sector_recursif(t_sector sector);

#endif
