
#ifndef DEBUG_H
# define DEBUG_H


# include "architect.h"
# include "color.h"
# include "calcul.h"

/*
**	define FLAG for debug print
*/
# define FULL		0
# define MID		1
# define SCREEN_ON	1<<1
# define FOV_HORI	1<<2

/*
**	flag debug wall
*/
# define P_PILLAR 	1<<0
# define P_NEXT		1<<1
# define TRACE		1<<2
# define POINT		1<<3

/*
**	debug screen, visual
*/
void		bold_point(t_vct2 v, Uint32 color, t_doom *doom);

void		b_point_debug(t_arch *arch, t_fvct2 v, Uint32 color);
void		draw_borne(t_arch *arch, uint32_t color);
void		draw_wall(t_arch *arch, uint32_t color);

void		p_debug(t_fvct2 a, Uint32 color, t_arch *arch);
void		draw_affine(t_arch *arch, t_affine affine, uint32_t color, int flag);
void		debug_screen_copy(t_arch *arch);
void		fill_line_debug(t_arch *arch, t_sdl *sdl, t_vct2 pos0, t_vct2 pos1, Uint32 color);

void		bold_point_debug(t_vct2 v, Uint32 color, t_screen *screen);

void		draw_frustum(t_arch *arch, int flag);
void		debug_pillar(t_arch *arch, int flag);
void		debug_pillar_ver(t_arch *arch, t_fvct2 surface_pillar);

/*
**	debug txt
*/
void		d_wall(t_wall *wall);
void		sector_recursif(t_sector sector, int sub);
void		borne_print(t_borne *borne);

#endif
