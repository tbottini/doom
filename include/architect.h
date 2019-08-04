#ifndef ARCHITECT_H
# define ARCHITECT_H

#include "sector.h"
#include "screen.h"

/*
**	structure principale pour la recursivite
*/
typedef struct 			s_borne
{
	double				*zline;
	uint32_t			*b_down;
	uint32_t			*b_up;
	double				b_left;
	double				b_right;
	t_fvct2				pillar;
	t_fvct2				next;
}						t_borne;

typedef struct 			s_arch
{
	t_sector			*sector;
	t_wall				*wall;
	t_camera			*cam;
	t_sdl				*sdl;
	SDL_Surface			**texture;
	uint16_t			depth_portal;
	t_fvct2				pillar;
	t_fvct2				next;
	t_vct2				px;
	t_fvct2				shift_txtr;
	t_borne				portal;
	t_list				portal_list;

	Uint32				sc_debug[WIDTH * HEIGHT];
	uint32_t			zoom;
}						t_arch;

int						designer_init(t_arch *designer, t_sdl *sdl, t_camera *cam);
int						arch_init(t_arch *arch, t_sdl *sdl, t_camera *cam);

#endif