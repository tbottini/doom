#ifndef RENDER_H
# define RENDER_H

# include "architect.h"
# include "player.h"
# include <SDL_ttf.h>
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

typedef					struct s_editor		t_editor;
typedef					struct s_mur		t_mur;
typedef 				t_mur				*t_lstmur;
typedef					struct s_secteur	t_secteur;
typedef					t_secteur			*t_lstsec;
typedef					struct s_entity		t_entity;
typedef					t_entity			*t_lstent;

typedef struct 			s_sprite
{
	t_fvct2				pos;
	t_vct2				width;
	t_vct2				heigth;
	t_txtr				texture;
	struct s_sprite		*next;
}						t_sprite;

typedef	struct		s_cursor
{
	t_fvct2			c_surface;
	double			c_neutre;
	double			c_dist;
	t_fvct2			*surface;
	double			dist_px;
	double			neutre;
}					t_cursor;

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
void					pillar_screen_info(t_arch *arch, t_player *p);
int						wall_behind_portal(t_arch *arch);
t_fvct2					surface_portal(t_fvct2 surface, t_sector *parent, t_sector *child);
/*
**	render
*/
void					sdl_multirendercopy(t_sdl *sdl);
void					sector_render(t_arch *arch, t_player *player, t_sector *sector);
int						fish_bowl_px(t_arch *arch, t_pillar pillar);
void					fish_eyes(double *dist, double angle);
uint32_t				texture_interpolation2d(t_arch *arch, t_txtr *txtr);
uint32_t				texture_prop_interpolation2d(t_arch *arch, t_txtr *txtr, t_prop *prop);
int						px_point(t_arch *arch, t_player *player, double h_diff, double depth);
t_fvct2					length_sector(t_player *player, t_sector *sector);
void					pillar_to_pillar(t_arch *arch, t_fvct2 *pillar, t_fvct2 *next, t_borne *borne_tmp);
void					render_wall(t_arch *arch, t_player *player);
void					render_recursive(t_arch *arch, t_player *player);
void					draw_column(t_arch *arch, t_fvct2 surface);
void					draw_portal(t_arch *arch, t_fvct2 surface, t_borne *parent_borne, int start);
int						draw_part_prop(t_arch *arch, int numcol, t_vct2 surface, t_prop *prop);
void					render_surface(t_arch *arch, t_player *player);

/*
** Editor render
*/
void					map_draw_line(t_editor *editor, t_vct2 pos0, t_vct2 pos1, SDL_Color c);
void					draw_grid(t_editor *editor, t_vct2 center, int dist, int master);
void					draw_player(t_editor *editor);
void					draw_props(t_editor *editor, t_entity *curr, SDL_Texture **sprites, int proppos);
void					draw_enemies(t_editor *editor, t_entity *curr);
void					draw_objs(t_editor *editor, t_entity *start);
void					draw_one_wall(t_editor *editor, t_lstmur currwall);
void					norm_draw_walls(t_editor *editor, t_lstsec currsec);

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
void					big_pixel(Uint32 *screen, t_vct2 size, t_vct2 pos, Uint32 color);
int						fill_pixel(Uint32 *screen, t_vct2 size, t_vct2 pos, Uint32 color);
void					render_sector_enemy(t_arch *arch, t_sector *sector, t_player *player);
int						draw_part_texture(t_arch *arch, int numcol, t_vct2 surface, t_txtr *txtr);
void					props_draw_column(t_prop *props, t_arch *arch, t_fvct2 surface);

/*
**	sprites
*/
void					sprite_render_list(t_sprite *sprite, t_arch *arch);
t_sprite				*sprite_from_enemy(t_sprite **sprite_list, t_enemy *enemy, t_player *player, t_arch *arch);
t_sprite				*sprite_from_props(t_sprite **sprite_list, t_prop *props, t_player *player, int len, t_arch *arch);
void					sprite_free(t_sprite *sprite);
void					sprite_iter(t_sprite *sprite, void(*effector)(t_sprite*));
void					sprite_render(t_sprite *sprite, t_arch *arch);
t_vct2					player_prop_heigth_surface(t_arch *arch, t_player *player
						, t_prop *prop, double depth);
t_vct2					cam_get_enemy_surface(t_arch *arch
						, t_enemy *enemy, t_player *player, double depth);
int						camera_proj_heigth(t_arch *arch, t_player *player
	, double h_diff, double depth);
/*
**	render enemy
*/
t_fvct2					player_enemy_diff_heigth(t_player *player, t_enemy *enemy);
t_vct2					txtr_width(t_txtr *texture, t_vct2 surface, int posx);
void					prop_init_render(t_prop *prop, void *arch);
void					prop_iter_v(t_prop *prop, int len, void(*prop_iter)(t_prop*, void*), void *sup);
t_vct2					prop_get_screen_pixel(t_prop *prop, t_arch *arch);

/*
**	sector viewing manipulation
*/
void				door_split(t_arch *arch, t_player *player, int flag);

#endif
