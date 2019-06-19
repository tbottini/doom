#ifndef SECTOR_H
# define SECTOR_H

#include <stdlib.h>
#include "vector.h"
#include <SDL.h>

typedef struct s_doom t_doom;

typedef struct 			s_txtr
{
	uint32_t			*pixels;
	uint32_t			w;
	uint32_t			h;
}						t_txtr;

typedef struct		s_pillar
{
	t_fvct2			p;
	char			frust;
	double			angle;
}					t_pillar;

typedef struct			s_prop
{
	double				x1;
	double				x2;
	double				y1;
	double				y2;
	double				z;
	t_txtr				*tex;
	void				(*func)(t_doom *doom);
}						t_prop;

/*
**	rajouter un pointeur sur le prochain pillier ? pour le mur
*/
typedef struct		s_wall
{
	t_pillar		pillar;
	t_pillar		*next;
	t_txtr			txtr;
	//texture
	//enum wall, portal
	//t_sector *portal sector
	//heigth?
}					t_wall;

typedef struct		s_sector
{
	t_fvct3			gravity;
	t_wall			*wall;
	t_prop			*prop;
	int				len_prop;
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
