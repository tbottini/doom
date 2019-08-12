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
	t_fvct2				pillar_world;
	t_fvct2				next_world;
	t_vct2				px;
	t_fvct2				shift_txtr;
	t_borne				portal;
	t_list				portal_list;
	Uint32				sc_debug[WIDTH * HEIGHT];
	uint32_t			zoom;
	uint32_t			timestamp;
}						t_arch;

int						designer_init(t_arch *designer, t_sdl *sdl, t_camera *cam);
int						arch_init(t_arch *arch, t_sdl *sdl, t_camera *cam);


/*
**	backface
*/
void					zline_cut(t_arch *arch, double *zline_cut, int start);
int						zline_portal(t_arch *arch, double *zline_tmp, double len_pillar, int start);
int						z_line_buffer(t_arch *arch, double len_pillar, int px);
int						zline_compare(t_arch *arch, double len_pillar, int px);
int						clean_zline(t_arch *arch, double len_pillar, int px);


/*
**	manager
*/
void					architect_reset(t_arch *arch);

/*
**	borne
*/
t_borne					*borne_init(t_borne *borne, int len);
t_borne					*borne_svg(t_arch *arch, t_borne *borne);
void					borne_free(t_borne *borne);
void					borne_load(t_arch *arch, t_borne *borne, t_vct2 px_draw);
void					borne_reset(t_arch *arch);
void					set_borne_vertical(t_arch *arch, t_vct2 surface, int i);
void					set_borne_horizontal(t_arch *arch);

#endif
