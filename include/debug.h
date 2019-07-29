
#ifndef DEBUG_H
# define DEBUG_H


# include "doom_struct.h"

# define WEND		"\e[0m"

# define WRED		"\e[31m\e[1m"
# define WGREEN		"\e[32m\e[1m"
# define WYELLOW 	"\e[33m\e[1m"
# define WBLUE 		"\e[34m\e[1m"
# define WMAGENTA 	"\e[35m\e[1m"
# define WCYAN 		"\e[36m\e[1m"
# define WGREY		"\e[38;5;250;250;250m"

# define WBRED		"\e[41m"
# define WBGREEN	"\e[42m"
# define WBYELLOW 	"\e[43m"
# define WBBLUE 	"\e[44m"
# define WBMAGENTA 	"\e[45m"
# define WBCYAN 	"\e[46m"

# define RED		0xff0000ff
# define BLUE		0x0000ffff
# define GREEN		0x00ff00ff
# define BROWN		0xff00ffff
# define YELLOW		0xffff00ff
# define PURPLE		0xff00ffff


# define BLUE_SOFT	0x138fa2ff
# define RED_SOFT	0x831a1aff
# define GREEN_SOFT	0x548528ff

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
void		bold_point_debug(t_vct2 v, Uint32 color, t_arch *arch);

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
