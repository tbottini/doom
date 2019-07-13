#ifndef RENDER_H
# define RENDER_H

#include "doom_struct.h"

/*
**	Color
*/
# define BLUE_SKY 0x4559a8ff
# define RED_WALL 0xb30000ff
# define PINK_FLOOR 0xdcc8c8ff
# define ORANGE 0xf5c738ff


/*
**	disfonctionnement si l'ordre n'est pas respecte
**	pour un carre a(up left) b(bottom left) c(up right) d(bot right)
*/
typedef struct 		s_shape
{
	t_fvct2			up;
	t_fvct2			left;
	t_fvct2			right;
	t_fvct2			bot;
}					t_shape;


/*
**	info function
*/
t_fvct2					surface_pillar(t_arch *arch, t_player *player, double depth);
double					wall_clipping(t_arch *arch, t_player *p, t_fvct2 *inter_local, double angle);
void					wall_screen_info(t_arch *arch, t_player *p);
double					local_angle(double borne, double angle);

void					set_borne_vertical(t_arch *arch, t_vct2 surface, int i);
void					set_borne_horizontal(t_arch *arch);
void					borne_reset(t_arch *arch);

void					reorder(t_arch *arch);
int						zline_portal(t_arch *arch, double *zline_tmp, double len_pillar);
/*
**	render
*/
int						z_line_buffer(t_arch *arch, double len_pillar, int px);
int						clean_zline(t_arch *arch, double len_pillar, int px);
void					architect_reset(t_arch *arch);
int						doom_render(t_doom *doom);
int						fish_bowl_px(t_arch *arch, t_pillar pillar);
void					fish_eyes(double *dist, double angle);
uint32_t				texture_interpolation2D(t_arch *arch);
void					render_wall(t_arch *arch, t_player *player);
void					draw_column(t_arch *arch, t_fvct2 surface);
void					draw_portal(t_arch *arch, t_player *player, t_fvct2 surface);

/*
**	bunch
*/
void					sector_frustum(t_arch *arch, t_sector *sector, t_player *player);
int						buncherisation(t_arch *arch, t_sector sector, t_wall **bunch);
void					bunch_comsuption(t_game *game, t_wall **bunch, t_sector *sector);

/*
** Drawer functions
*/
int						sdl_string_put(SDL_Renderer *rend, TTF_Font *font, t_vct2 loc, const char *text, SDL_Color fg);
int						sdl_int_put(SDL_Renderer *rend, TTF_Font *font, t_vct2 loc, const char *label, const int value, SDL_Color fg);
void					sdl_cleartexture(Uint32 *screen, t_vct2 size);
void					big_pixel(Uint32 *screen, t_vct2 size, t_vct2 pos, Uint32 color);
int						fill_pixel(Uint32 *screen, t_vct2 size, t_vct2 pos, Uint32 color);
//void					editor_fill_line(t_editor *ed, t_vct2 pos0, t_vct2 pos1, Uint32 color);
void					fill_line(t_sdl *sdl, t_vct2 pos0, t_vct2 pos1, Uint32 color);

/*
**	shape
*/
void					draw_part_line(t_sdl *sdl, t_shape *shape, uint32_t color);
t_shape					shape_reajust(t_shape shape);
#endif
