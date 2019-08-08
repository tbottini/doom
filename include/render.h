#ifndef RENDER_H
# define RENDER_H

#include "architect.h"
#include "player.h"
#include "SDL_ttf.h"
# include "calcul.h"
//borne arch player vector sector

/*
**	Color
*/
# define BLUE_SKY 0x4559a8ff
# define RED_WALL 0xb30000ff
# define PINK_FLOOR 0xdcc8c8ff
# define ORANGE 0xf5c738ff

# define PILLAR 1
# define NEXT 2

# define DEBUG_VISUAL 1

# define RASTERIZE		0
# define ENGINE			1
# define RENDER			ENGINE

/*
**	disfonctionnement si l'ordre n'est pas respecte
**	pour un carre a(up left) b(bottom left) c(up right) d(bot right)
*/
typedef struct 			s_shape
{
	t_fvct2				up;
	t_fvct2				left;
	t_fvct2				right;
	t_fvct2				bot;
}						t_shape;

typedef struct 			s_shap
{
	t_fvct2				ul;
	t_fvct2				ur;
	t_fvct2				bl;
	t_fvct2				br;
}						t_shap;

/*
**	pillar
*/
void					pillar_virtual_move(t_arch *arch, t_fvct2 inter, int flag);

/*
**	info function
*/
t_fvct2					surface_pillar(t_arch *arch, t_player *player, t_fvct2 len_sector, double depth);
double					wall_clipping(t_arch *arch, t_player *p, t_fvct2 *inter_local, double angle);
int						wall_screen_info(t_arch *arch, t_player *p);
double					local_angle(double borne, double angle);
void					reorder(t_arch *arch);
t_fvct2					get_floor_pos(t_arch *arch, t_fvct2 len, t_fvct2 surface, t_fvct2 *pillar);
t_fvct2					frustum_floor_intersection(t_fvct2 *pillar_pos, t_camera *camera, t_fvct2 *len_sector, t_stat *stat);
t_fvct2					frustum_depth_intersection(t_camera *camera, t_stat *stat, double floor_diff);

/*
**	render
*/
void					sector_render(t_arch *arch, t_player *player, t_sector *sector);
int						fish_bowl_px(t_arch *arch, t_pillar pillar);
void					fish_eyes(double *dist, double angle);
uint32_t				texture_interpolation2D(t_arch *arch);
void					render_wall(t_arch *arch, t_player *player);
void					draw_column(t_arch *arch, t_fvct2 surface);
void					draw_portal(t_arch *arch, t_fvct2 surface, t_borne *parent_borne, int start);

/*
**	bunch
*/
int						on_frustum(t_arch *arch, t_player *player, t_pillar *pillar);
void					sector_frustum(t_arch *arch, t_sector *sector, t_player *player);
int						buncherisation(t_arch *arch, t_sector *sector, t_wall **bunch);
void					bunch_comsuption(t_arch *arch, t_player *player, t_wall **bunch, t_sector *sector);
int						borne_in_wall_angle(t_arch *arch, t_wall *wall);
int						equal_pillar(t_wall *wall1, t_wall *wall2);

/*
** drawer functions
*/
void					sdl_cleartexture(Uint32 *screen, t_vct2 size);
void					big_pixel(Uint32 *screen, t_vct2 size, t_vct2 pos, Uint32 color);
int						fill_pixel(Uint32 *screen, t_vct2 size, t_vct2 pos, Uint32 color);
void					render_sector_enemy(t_sdl *sdl, t_camera *camera, t_sector *sector, t_player *player);

/*
**	shape
*/
void					draw_part_line(t_sdl *sdl, t_shape *shape, uint32_t color);
t_shape					shape_reajust(t_shape shape);


#endif
