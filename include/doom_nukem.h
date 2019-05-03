
#ifndef DOOM_NUKEM
# define DOOM_NUKEM

# include "doom.h"

//portal engine

typedef	uint32_t* t_texture;

typedef struct 		s_wl
{
	t_fvct2			pos;
	struct s_wl		*next;
	t_texture		*t_wall;
}					t_wl;

typedef	struct 		s_ssector
{
	t_fvct2			*root_wall;
	t_texture		t_ceil;
	t_texture		t_floor;
	float			h_ceil;
	float			h_floor;
}					t_ssector;

typedef	struct 		s_sector
{
	t_wl			*root_wall;
	t_texture		t_floor;
	t_texture		t_ceil;
	float			h_ceil;
	float			h_floor;
}					t_sector;

//struct game_manager, player, sprite

#endif