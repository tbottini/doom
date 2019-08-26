/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 16:39:33 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 17:12:56 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "architect.h"
# include "player.h"
# include "SDL_ttf.h"
# include "calcul.h"

/*
**	Color
*/

# define BLUE_SKY 		0x4559a8ff
# define RED_WALL 		0xb30000ff
# define PINK_FLOOR 	0xdcc8c8ff
# define ORANGE 		0xf5c738ff

# define PILLAR 		1
# define NEXT 			2

# define DEBUG_VISUAL 	1

# define PORTAL_MAX		50

# define RASTERIZE		0
# define ENGINE			1
# define RENDER			ENGINE

typedef struct s_doom	t_doom;

typedef struct			s_needle
{
	int					numcol;
	t_vct2				surface;
	t_txtr				*txtr;
	uint32_t			txtr_col;
	double				coef;
	double				buff;
}						t_needle;

typedef struct			s_sprite
{
	t_fvct2				pos;
	t_vct2				width;
	t_vct2				heigth;
	t_txtr				texture;
	struct s_sprite		*next;
}						t_sprite;

/*
**	pillar
*/

void					pillar_virtual_move(t_arch *arch, t_fvct2 inter
	, int flag);

/*
**	bunch
*/

void					wall_frustum(t_arch *arch, t_player *player
	, t_wall *wall);
int						buncherisation(t_arch *arch, t_sector *sector
	, t_wall **bunch);
void					bunch_comsuption(t_arch *arch, t_player *player
	, t_wall **bunch, t_sector *sector);
int						borne_in_wall_angle(t_arch *arch, t_wall *wall);
int						equal_pillar(t_wall *wall1, t_wall *wall2);

/*
**	info function
*/

t_fvct2					surface_pillar(t_arch *arch, t_player *player
	, t_fvct2 len_sector, double depth);
double					wall_clipping(t_arch *arch, t_player *p
	, t_fvct2 *inter_local, double angle);
int						wall_screen_info(t_arch *arch, t_player *p);
double					local_angle(double borne, double angle);
void					reorder(t_arch *arch);
t_fvct2					get_floor_pos(t_arch *arch, t_fvct2 len
	, t_fvct2 surface, t_fvct2 *pillar);
t_fvct2					frustum_floor_intersection(t_fvct2 *pillar_pos
	, t_camera *camera, t_fvct2 *len_sector, t_stat *stat);
t_fvct2					frustum_depth_intersection(t_camera *camera
	, t_stat *stat, double floor_diff);
void					pillar_screen_info(t_arch *arch, t_player *p);
int						wall_behind_portal(t_arch *arch);
int						point_behind_portal(t_arch *arch, t_player *player
	, t_fvct2 pos);
t_fvct2					surface_portal(t_fvct2 surface, t_sector *parent
	, t_sector *child);
void					door_split_info(t_arch *arch
	, t_pil_render *render_stuff, int flag);
void					save_pixels_portal(t_arch *arch
	, t_pil_render *render_stuff, t_vct2 *pixels);
t_fvct2					length_sector(t_player *player, t_sector *sector);
void					pil_screen_info(t_arch *a, t_player *p);
void					next_screen_info(t_arch *a, t_player *p);

/*
**	render
*/

void					sector_render(t_arch *arch, t_player *player
	, t_sector *sector);
int						fish_bowl_px(t_arch *arch, t_pillar pillar);
void					fish_eyes(double *dist, double angle);
double					percent_interpolation2d(t_arch *arch);
uint32_t				texture_interpolation2d(t_arch *arch, t_txtr *txtr);
uint32_t				texture_prop_interpolation2d(t_arch *arch, t_txtr *txtr
	, t_prop *prop);
void					render_wall(t_arch *arch, t_player *player);
void					render_recursivite(t_arch *arch, t_player *player
	, t_vct2 pixel_portal);

/*
**	draw_part
*/

void					draw_door(t_arch *arch, t_pil_render *render_stuff
	, int flag);
void					draw_wall(t_arch *arch, t_pil_render *render_stuff);
void					draw_portal(t_arch *arch, t_pil_render *render_stuff);
void					draw_window(t_arch *arch, t_pil_render *rendr);
int						draw_part_prop(t_arch *arch, t_needle *needle
	, t_vct2 limit, t_prop *prop);
void					render_surface(t_arch *arch, t_player *player);
double					draw_part(t_arch *arch, int start, int end
	, uint32_t color);
int						draw_part_texture(t_arch *arch, int numcol
	, t_vct2 surface);
int						draw_part_decal(t_arch *arch, int numcol
	, t_vct2 surface, t_pil_render *render_stuff);
int						draw_part_opacity(t_arch *arch, int cursor
	, t_vct2 surface, t_txtr *txtr);
void					props_draw_column(t_prop *props, t_arch *arch
	, t_fvct2 surface);

/*
** drawer functions
*/

void					sdl_cleartexture(Uint32 *screen, t_vct2 size);
void					big_pixel(Uint32 *screen, t_vct2 size, t_vct2 pos
	, Uint32 color);
int						fill_pixel(Uint32 *screen, t_vct2 size, t_vct2 pos
	, Uint32 color);
void					render_sector_enemy(t_arch *arch, t_sector *sector
	, t_player *player);
void					weapon_render(t_doom *d);
int						opacity_from_color(Uint32 add, Uint32 basique);

/*
**	sprites
*/

void					sprite_render_sector(t_arch *arch, t_sector *sector
	, t_player *player);
void					sprite_render_list(t_sprite *sprite, t_arch *arch);
t_sprite				*sprite_from_enemy(t_sprite **sprite_list
	, t_enemy *enemy, t_player *player, t_arch *arch);
t_sprite				*sprite_from_props(t_sprite **sprite_list, t_sector *s
	, t_player *player, t_arch *arch);
void					sprite_print(t_sprite *sprite);
void					sprite_print(t_sprite *sprite);
void					sprite_draw(t_sprite *sprite, t_arch *arch);
t_sprite				*sprite_new(t_txtr texture, t_fvct3 origin
	, t_fvct3 dist, double angle);
void					sprite_free(t_sprite *sprite);
void					sprite_iter(t_sprite *sprite
	, void (*effector)(t_sprite*));
t_sprite				*sprite_list_free(t_sprite **sprite_list);
void					sprite_insert(t_sprite **sprite_list
	, t_sprite *sprite_node);
t_vct2					player_prop_heigth_surface(t_arch *arch
	, t_player *player, t_prop *prop, double depth);
t_vct2					cam_get_enemy_surface(t_arch *arch, t_enemy *enemy
	, t_player *player, double depth);

/*
**	render enemy
*/

t_fvct2					player_enemy_diff_heigth(t_player *player
	, t_enemy *enemy);
int						camera_proj_heigth(t_arch *arch, t_player *player
	, double h_diff, double depth);
t_vct2					txtr_width(t_txtr *texture, t_vct2 surface, int posx);
void					prop_init_render(t_prop *prop, void *arch);
void					prop_iter_v(t_prop *prop, int len
	, void(*prop_iter)(t_prop*, void*), void *sup);
t_vct2					prop_get_screen_pixel(t_prop *prop, t_arch *arch);

/*
**	needle function
*/

void					needle_buff_affect(t_needle *needle);
t_needle				needle_prepare(int numcol, t_txtr *txtr
	, uint32_t txtr_col, t_vct2 surface);
void					needle_reajust2(t_needle *needle, int limit);
uint32_t				pixel_opacity(t_arch *arch, t_needle *needle);
uint32_t				pixel_txtr(t_arch *arch, t_needle *needle);
void					needle_reajust(t_arch *arch, t_needle *needle
	, int limit);
void					needle_indent_down(t_needle *needle, t_arch *arch);

int						draw_txtr_column(t_arch *a, t_needle *ne
	, uint32_t (*pixel_effector)(t_arch*, t_needle*));
int						draw_txtr_column_prop(t_arch *a, t_needle *n
	, t_vct2 limit);

#endif
