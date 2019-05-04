
#ifndef DOOM_NUKEM
# define DOOM_NUKEM

# include "doom.h"

//portal engine

typedef	uint32_t* t_texture;

//le bunch permet de faire des groupe de mur visible
//pour organiser l'affichage
//over : indique si le mur depasse la vision mais et relier a un
//mur dans la vision

typedef struct 		s_wl
{
	t_fvct2			pos;
	struct s_wl		*next;
	t_texture		*t_wall;
	float			angle;
	char			frust;
}					t_wl;

typedef	struct 		s_ssector
{
	t_fvct2			*root_wall;
	int				len;
	t_texture		t_ceil;
	t_texture		t_floor;
	float			h_ceil;
	float			h_floor;
}					t_ssector;

typedef	struct 		s_sector
{
	t_wl			*root_wall;
	int				len;
	t_texture		t_floor;
	t_texture		t_ceil;
	float			h_ceil;
	float			h_floor;
}					t_sector;

typedef struct 		s_player
{
	t_fvct2			pos;
	t_fvct2			rot;
	int				fov;
	float			d_scrn;
}					t_player;

float		ft_atof(char *str);
float		ft_catof(char *str, char c);
t_sector	*parsing(char *av);
void		fvct2_print(t_fvct2 vct);
void		sector_describe(t_sector sector);
//struct game_manager, player, sprite
void		portal_engine(t_player player, t_sector *sector);
void		fvct2_msg(char *msg, t_fvct2 vct);
void		describe_bunch(t_wl **bunch);
t_fvct2		wall_clipping(t_wl wall, t_fvct2 origin, float ang);
#endif