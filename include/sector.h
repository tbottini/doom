#ifndef SECTOR_H
# define SECTOR_H

#include <stdlib.h>
#include "vector.h"

typedef struct		s_pillar
{
	float			x;
	float			y;
	char			frust;
}					t_pillar;

typedef struct		s_wall
{
	t_pillar		pillar;
	t_pillar		*next;
	float			angle;
	char			frust;
	//texture
	//enum wall, portal
	//t_sector *portal sector
	//heigth?
}					t_wall;

typedef struct		s_sector
{
	t_wall			*wall;
	float			h_floor;
	float			h_ceil;
	int				len;
	//sector effector *fonction
	//list things (shapes, objets, deco, enemis)
}					t_sector;

/*
**	wall : draw, manipulation
*/

float			wall_clipping(t_wall wall1, t_wall wall2, t_fvct2 origin, float ang);

#endif
